/*
    Author: Sumeet Singh
    Dated: 28/02/2024
    Minimum C++ Standard: C++11
    Purpose: Class Declaration file
    License: MIT License
*/

#pragma once

#include <iostream>
#include <string>
#include <random>
#include <vector>

#include "entities/Player.hpp"
#include "entities/Item.hpp"
#include "entities/Enemy.hpp"
#include "entities/Obstacle.hpp"
#include "entities/Bot.hpp"
#include "entities/Ammo.hpp"
#include "entities/Bird.hpp"
#include "entities/Bomb.hpp"
#include "entities/Boots.hpp"
#include "entities/Boss.hpp"
#include "entities/Cactus.hpp"
#include "entities/Door.hpp"
#include "entities/Enemy.hpp"
#include "entities/Fence.hpp"
#include "entities/Fish.hpp"
#include "entities/Gem.hpp"
#include "entities/Heal.hpp"
#include "entities/Heart.hpp"
#include "entities/House.hpp"
#include "entities/Item.hpp"
#include "entities/Key.hpp"
#include "entities/MeeleeWeapon1.hpp"
#include "entities/MeeleeWeapon2.hpp"
#include "entities/MeeleeWeapon3.hpp"
#include "entities/Mountain.hpp"
#include "entities/Mushroom.hpp"
#include "entities/Note.hpp"
#include "entities/RangedWeapon1.hpp"
#include "entities/RangedWeapon2.hpp"
#include "entities/RangedWeapon3.hpp"
#include "entities/River.hpp"
#include "entities/Robot.hpp"
#include "entities/Tree.hpp"
#include "entities/Vehicle.hpp"
#include "entities/Villager.hpp"

/**
 * @brief Entity Manager manages the initialisation of entites from Entity.hpp
 * 
 * Utility class that works alongside any entity class to generate entities for your game/project.
 * e.g. procedural generate entities for a level or use with a level editor button select to
 * create custom maps with specific entities.
 *
 * EXAMPLE
 *
 * 1. Include the libs header
 *
 * include "../headers/EntityManager.hpp"
 *
 * 2. You can create new Entitites for your game by defining their characteristics here and adding it to
 * Entity.hpp
 *
 * 3. Then to initialise them randomly in your scene call
 * EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
 *
 * 4. Or to initialise inidividually just call the function to add whichever entity you want to add to
 * window/level editor through handles()
 *
 */
class EntityManager
{
private:
public:
    /**
     * @brief EntityManager constructor
     *
     * EntityManager constructor called during setups() or in level_editor() to create custom maps
     */
    EntityManager();
    /**
     * @brief EntityManager Deconstructor
     *
     * EntityManager Deconstructor
     */
    ~EntityManager();

    /**
     * @brief create a player entity
     *
     * Generate a player object entity
     */
    static void create_player_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT, int playerCount);
    /**
     * @brief create a bot entity
     *
     * Generate a bot object entity
     */
    static void create_bot_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT, int playerCount);

    /**
     * @brief create a item heart entity
     *
     * Generate a item heart object entity
     */
    static void create_item_heart_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT);

    /**
     * @brief Random creation logic for item entities
     *
     * function for randomly generating item entities objects
     */
    static void create_random_item_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    /**
     * @brief Random creation logic for enemy entities
     *
     * function for randomly generating enemy entities objects
     */
    static void create_random_enemy_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    /**
     * @brief Random creation logic for obstacle entities
     *
     * function for randomly generating obstacle entities objects
     */
    static void create_random_obstacle_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    /**
     * @brief random procedurally generate non player entities
     *
     * calls functions for clearing all non player entities
     * Then randomly creating entities with their function calls below
     * create_random_item_entity()
     * create_random_enemy_entity()
     * create_random_obstacle_entity()
     *
     *
     * EXAMPLE
     *
     * 1. To generate 10 random items, enemies and obstacles to scene window
     *
     * EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
     *
     */
    static void random_procedural_generation(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT, int itemsCount, int enemiesCount, int obstaclesCount);
};
