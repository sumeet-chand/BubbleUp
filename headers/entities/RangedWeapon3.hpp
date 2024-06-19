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
 * @brief Item subclass ranged weapon grants shoot skill if ammo/mana in inventory
 *
 */
class RangedWeapon3 : public Item
{
public:
    /**
     * @brief default constructor
     */
    RangedWeapon3(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
};
