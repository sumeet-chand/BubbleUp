/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/


#pragma once

#include "Enemy.hpp"

/**
 * @brief Enemy subclass Fish is part of scenery with swimming animation
 *
 */
class Fish : public Enemy
{
private:
public:
    /**
     * @brief default constructor
     */
    Fish(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
    /**
     * @brief move entity in game loop
     * @param acceleration the modifier to move the entity rect a direction
     */
    void move_entity(float acceleration) override;
};
