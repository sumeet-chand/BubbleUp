/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Class Declaration file
    License: MIT License
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief debug logging solution class to output traditional cout debug logs to
 * terminal, buffer and file depending on severity.
 *
 * To enable a software to have a better logging solution then simply
 * couting messages to terminal, or outputting all cout's to a save file
 * you can use this class to implement a complete logging solution.
 *
 * @param logFileName name of the file to send logs to
 * @param logBugger holds buffer of all non critical logs to print to file during quit
 *
 *
 * EXAMPLE
 *
 * 1. Include this header
 * include "DebugLogging.hpp"
 *
 * 2. Create object instance e.g. in your globals.hpp as an extern variable: extern DebugLogging logger;
 * then in your globals.cpp as below
 * DebugLogging logger("game_log.txt");
 *
 * 3. Clear and reset logs
 * logger.clear_log_file();
 *
 * 4. Add critical messages
 * logger.log_critical("Starting Software");
 *
 * 5. Add non critical messages
 * logger.log_non_critical("Hello world");
 *
 * 6. Write to bugger
 * logger.write_log_buffer_to_file();
 */
class DebugLogging
{
private:
    std::string logFileName{}; /**< Name of the file to send logs to */
    std::vector<std::string> logBuffer{}; /**< Buffer of all non-critical logs to write to file during game quit with write_log_buffer_to_file() */

public:
    /**
     * @brief DebugLogging class constructor
     *
     * DebugLogging class constructor, making explicit to prevent implicit conversions
     * from string to DebugLogging object. This ensures that the class is only constructed
     * when explicitly intended, preventing accidental conversions that could lead to bugs.
     * e.g. DebugLogging logger = "game_log.txt"; // This would not compile
     */
    explicit DebugLogging(const std::string &fileName);
    /**
     * @brief DebugLogging class Deconstructor
     *
     * DebugLogging class Deconstructor
     */
    ~DebugLogging();
    /**
     * @brief log critical software messages to cout and file
     *
     * Accepts a message then writes it out with timestamp to file
     *
     * EXAMPLE
     *
     * log_critical("Error: SDL Window creation failed");
     *
     * @param message the string of text to cout and write to file
     */
    void log_critical(const std::string &message);

    /**
     * @brief log non critical software messages to cout and buffer
     *
     * Accespts a message then writes it out with timestamp to cout then buffer
     * on game exit another function write_log_buffer_to_file() will trigger buffer to
     * write to log file
     *
     * EXAMPLE
     *
     * log_non_critical("You pressed: UP");
     *
     * @param message the string of text to cout and write to buffer/file
     */
    void log_non_critical(const std::string &message);

    /**
     * @brief write logBuffer contents to file
     *
     * Writes all log messages called by log_non_critical() to file
     *
     * EXAMPLE
     *
     * write_log_buffer_to_file();
     */
    void write_log_buffer_to_file();

    /**
     * @brief clear game log file on software startup
     *
     * Clears all contents of game log on software startup to prevent file
     * size increasing too large
     *
     * called just after main() entry point
     *
     */
    void clear_log_file();
};