/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Class Definition file
    License: MIT License
*/

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include "../headers/DebugLogging.hpp"

DebugLogging::DebugLogging(const std::string &logFileName) : logFileName(logFileName)
{
    std::cout << "Constructed: DebugLogging" << std::endl;
}

DebugLogging::~DebugLogging()
{
    std::cout << "Deconstructed: DebugLogging" << std::endl;
}

void DebugLogging::log_critical(const std::string &message)
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S %d/%m/%y", std::localtime(&time));
    std::string timestamp(buffer); // Assigning the formatted timestamp to a string variable

    // Print to terminal with timestamp
    std::cout << timestamp << " [CRITICAL] " << message << std::endl;

    // Write to log file immediately with timestamp
    std::ofstream logFile(logFileName, std::ios_base::app);
    if (logFile.is_open())
    {
        logFile << timestamp << " [CRITICAL] " << message << std::endl;
        logFile.close();
    }
    else
    {
        std::cerr << "Error: Couldn't open log file for writing!" << std::endl;
    }
}

void DebugLogging::log_non_critical(const std::string &message)
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S %d/%m/%y", std::localtime(&time));
    std::string timestamp(buffer); // Assigning the formatted timestamp to a string variable

    // Print to terminal with timestamp
    std::cout << message << std::endl;

    // Function to log a message to buffer with timestamp
    logBuffer.push_back(timestamp + " [INFO] " + message);
}

void DebugLogging::write_log_buffer_to_file()
{
    std::ofstream logFile(logFileName, std::ios_base::app);
    if (logFile.is_open())
    {
        for (const auto &message : logBuffer)
        {
            logFile << message << std::endl;
        }
        logFile.close();
    }
    else
    {
        std::cerr << "Error: Couldn't open log file for writing!" << std::endl;
    }
}

void DebugLogging::clear_log_file()
{
    std::ofstream logFile(logFileName, std::ios_base::trunc);
    if (logFile.is_open())
    {
        logFile.close();
    }
    else
    {
        std::cerr << "Error: Couldn't open log file for clearing!" << std::endl;
    }
}