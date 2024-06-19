/*
    Author: Sumeet Singh
    Dated: 17/04/2024
    Minimum C++ Standard: C++11
    Purpose: Tests
    License: MIT License
    Description: Tests
*/

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include "../headers/globals.hpp"
#include "../headers/game_engine_initialise.hpp"
#include "../headers/game_engine_logic.hpp"

class mainTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        logger.clear_log_file();
        logger.log_critical("Starting Software");
        start_SDL(); // will play 10 second cinematic
        run_SDL();
    }

    void TearDown() override
    {
        exit_SDL();
        logger.write_log_buffer_to_file();
    }
};

/**
 * @brief Simulated Google test default test
 * 
 * To test that Google Test framework/Library is working and integrated correctly
 * this simple testcase can be placed anywhere. when the test is run you can observe the
 * results of the pass. This helps you understand what to look for and how to design a test case.
 */
TEST_F(mainTest, adds_two_numbers_correctly)
{
    std::cout << "Running test adds_two_numbers_correctly" << std::endl;
    int a = 1;
    int b = 2;
    EXPECT_EQ(a + b, 3);
}

/**
 * @brief test - check logs for any errors
 * 
 * Excludes audio errors as test can run on headless/driverless platforms without these features
 * 
 */
TEST_F(mainTest, check_logs_for_errors)
{
    std::cout << "Running test check_logs_for_errors" << std::endl;
    int returnCode{};
    std::ifstream file("game_log.txt");
    if (!file)
    {
        returnCode = 1; // Unable to open log file
    }
    else
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find("Error") != std::string::npos)
            {
                returnCode = 1; // Error found in log
                break;
            }
        }
    }
    EXPECT_EQ(returnCode, 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}