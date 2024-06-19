/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/


#pragma once

#include "Item.hpp"

/**
 * @brief Item subclass boots increases max acceleration
 *
 */
class Boots : public Item
{
public:
    /**
     * @brief default constructor
     */
    Boots(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
};
