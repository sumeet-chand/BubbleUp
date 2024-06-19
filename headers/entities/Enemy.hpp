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

/**
 * @brief Game Entity.hpp subclass for in game Enemies including non hostile NPC's
 *
 * Defines the hostile and non hostile enemies and npcs behaviour.
 * read the Entity.hpp comment block for more details
 */
class Enemy : public Entity
{
private:
    int personality{}; /**< Used to determine response for being hurt. If this value is low it means the enemy has no reprecussion
    to hurt and players reputation will not drop. However if this value is high and the entity is beloved by many, if hurt by player
    players reputation score decreases so less entities will trade/chat/help with player. For immersive gameplay. */

public:
    /**
     * @brief enemy class default constructor
     */
    Enemy(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
    /**
     * @brief handle enemy collission with another player
     *
     * e.g. play attack noise e.g. bear growls, damage enemy health
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_player_collision(std::vector<Entity *> &entities) override;
    /**
     * @brief handle enemy collission with another item
     *
     * e.g. some enemies will pickup item, add to inventory, delete from entities vector
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_item_collision(std::vector<Entity *> &entities) override;
    /**
     * @brief handle enemy collission with enemy
     *
     * e.g. wave and say hi, output a text bubble conversation
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_enemy_collision(std::vector<Entity *> &entities) override;
};
