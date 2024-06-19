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
 * @brief Enemy subclass villager is a non hostile NPC
 *
 * USE CASES
 *
 * 1 Give out quests (journal entries) with rewards (items)
 * 2. Act as store to sell (items)
 * 3. Can be destroyed to drop (inventory items)
 * 4. Can fight back if logic is met
 *
 */
class Villager : public Enemy
{
private:
public:
    /**
     * @brief default constructor
     */
    Villager(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
    /**
     * @brief move entity in game loop
     * @param acceleration the modifier to move the entity rect a direction
     */
    void move_entity(float acceleration) override;
};
