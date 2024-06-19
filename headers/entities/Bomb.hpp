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
 * @brief Enemy subclass Bomb blows up on player collission
 *
 * reduces health on collission of entity
 */
class Bomb : public Enemy
{
private:
public:
    /**
     * @brief default constructor
     */
    Bomb(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
    /**
     * @brief handle player collission
     *
     * e.g. damage player
     * @param entities the vector of all entities
     */
    void handle_player_collision(std::vector<Entity *> &entities) override;
    /**
     * @brief move entity in game loop
     * @param acceleration the modifier to move the entity rect a direction
     */
    void move_entity(float acceleration) override;
};