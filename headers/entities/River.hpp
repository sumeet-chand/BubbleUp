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
 * @brief Obstacle subclass Water on collission slows movement, non destroyable
 *
 */
class River : public Obstacle
{
public:
    /**
     * @brief default constructor
     */
    River(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);

    /**
     * @brief handle player collission
     *
     * e.g. play water splash particles
     * @param entities the vector of all entities
     */
    void handle_player_collision(std::vector<Entity *> &entities) override;
};
