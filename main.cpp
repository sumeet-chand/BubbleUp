/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++17
    Purpose: Program main entry point
    License: MIT License
*/

#include "headers/globals.hpp"
#include "headers/game_engine_initialise.hpp"
#include "headers/game_engine_logic.hpp"

/**
 * @brief Software main entry point
 *
 * Calls functions to initialise SDL, the SDL event loop and SDL destructors on exit.
 * Uses C style `int argc, char *argv[]` parameters for SDL backwards compatibility.
 *
 * @param argc The number of command line arguments for SDL C language backwards compatability.
 * @param argv The array of command line arguments for SDL C language backwards compatability.
 * @return int The exit status of the program.
 */
int main(int argc, char *argv[])
{
    logger.clear_log_file();

    logger.log_critical("Starting Software");

    start_SDL();
    run_SDL();
    exit_SDL();

    logger.write_log_buffer_to_file();

    return 0;
}