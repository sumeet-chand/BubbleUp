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

/**
 * @brief Game Entity.hpp subclass for in game Items
 *
 * Game Entity subclass, Item base class for defining common features related to
 * various Item elements in a game e.g, being picked up on player collission to add to
 * inventory and destroying itself. read the Entity.hpp comment block for more details
 */
class Item : public Entity
{
public:
    /**
     * @brief default constructor
     */
    Item(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
    /**
     * @brief handle item collission with player
     *
     * e.g. play item specific noise e.g. money jingle, or paper crunch
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_player_collision(std::vector<Entity *> &entities) override;
    /**
     * @brief handle item collission with another item
     *
     * e.g play noise?
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_item_collision(std::vector<Entity *> &entities) override;
};
