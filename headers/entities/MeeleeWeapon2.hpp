/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Class Declaration file
    License: MIT License
*/


#pragma once

#include "Item.hpp"

/**
 * @brief Item subclass meelee weapon is a on contact weapon
 *
 */
class MeeleeWeapon2 : public Item
{
public:
    /**
     * @brief default constructor
     */
    MeeleeWeapon2(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
};
