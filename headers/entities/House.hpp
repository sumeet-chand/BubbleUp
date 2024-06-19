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
 * @brief Obstacle subclass house on collission blocks movement, non destroyable
 *
 */
class House : public Obstacle
{
public:
    /**
     * @brief default constructor
     */
    House(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
};