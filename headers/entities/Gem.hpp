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
 * @brief Item subclass Gem increases score++
 *
 */
class Gem : public Item
{
public:
    /**
     * @brief default constructor
     */
    Gem(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);

    void handle_player_collision(std::vector<Entity *> &entities) override;
};
