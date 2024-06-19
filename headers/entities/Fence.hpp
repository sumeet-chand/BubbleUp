/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/


#pragma once

#include "Obstacle.hpp"

/**
 * @brief Obstacle subclass Fence on collission blocks movement, can be jumped over
 *
 */
class Fence : public Obstacle
{
public:
    /**
     * @brief default constructor
     */
    Fence(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
};
