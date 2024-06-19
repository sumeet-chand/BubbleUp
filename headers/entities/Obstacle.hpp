/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/

#pragma once

#include "../Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Item.hpp"

/**
 * @brief Game Entity.hpp subclass for in game obstacles
 *
 * Defines the behaviour of in game obstacles such as nature rivers, mountains, trees
 * and furniture, buildings, fences etc.,
 * read the Entity.hpp comment block for more details
 */
class Obstacle : public Entity
{
public:
    /**
     * @brief default constructor
     */
    Obstacle(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
    /**
     * @brief handle obstacle collission with player
     *
     * e.g. if water was treaded on, play particle emmitor animation for water splashing
     * or lower player health if they ran into a cactus
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_player_collision(std::vector<Entity *> &entities) override;
    /**
     * @brief handle obstacle collission with enemy
     *
     * e.g. stop enemy
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_enemy_collision(std::vector<Entity *> &entities) override;
    /**
     * @brief handle obstacle collission with item
     *
     * e.g. stop item if thrown against obstacle, or take damage if destroyable
     * e.g. a player throws a rock at a window item to jump through the window
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_item_collision(std::vector<Entity *> &entities) override;
    /**
     * @brief handle obstacle collission with obstacle
     *
     * e.g. n/a
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_obstacle_collision(std::vector<Entity *> &entities) override;
};
