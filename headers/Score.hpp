/*
    Author: Sumeet Singh
    Dated: 14/05/2024
    Minimum C++ Standard: C++17
    Purpose: Class Declaration file
    License: MIT License
*/
#pragma once

#include <iostream>
#include <string>

/**
 * @brief struct for holding player gameplay statistics for scoreboards/leaderboards/Competitive play
*/
struct Score
{
    int playerID; /**< primary ID key for tracking player scores */
    std::string name; /**< player name taken from player entity */
    int score; /**< player score taken from player entity */
    std::string datetime; /**< current date and time in human readable format for gameplay statistics on time achieved */
};