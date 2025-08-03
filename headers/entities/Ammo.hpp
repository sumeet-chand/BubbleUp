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
 * @brief Item subclass Ammo/Mana refills ranged weapons/Skills
 *
 */
class Ammo : public Item
{
public:
    /**
     * @brief default constructor
     */
    Ammo(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
};