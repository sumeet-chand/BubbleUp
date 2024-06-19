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
 * @brief Enemy subclass bird is part of scenery with flying animation
 *
 */
class Bird : public Enemy
{
private:
public:
    /**
     * @brief default constructor
     */
    Bird(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
    /**
     * @brief move entity in game loop
     * @param acceleration the modifier to move the entity rect a direction
     */
    void move_entity(float acceleration) override;
};