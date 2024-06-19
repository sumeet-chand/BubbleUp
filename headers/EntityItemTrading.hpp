/*
    Author: Sumeet Singh
    Dated: 23/05/2024
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

#include "entities/Ammo.hpp"
#include "entities/Bird.hpp"
#include "entities/Bomb.hpp"
#include "entities/Boots.hpp"
#include "entities/Boss.hpp"
#include "entities/Bot.hpp"
#include "entities/Enemy.hpp"
#include "entities/Fish.hpp"
#include "entities/Gem.hpp"
#include "entities/Heart.hpp"
#include "entities/Item.hpp"
#include "entities/Key.hpp"
#include "entities/MeeleeWeapon1.hpp"
#include "entities/MeeleeWeapon2.hpp"
#include "entities/MeeleeWeapon3.hpp"
#include "entities/Note.hpp"
#include "entities/RangedWeapon1.hpp"
#include "entities/RangedWeapon2.hpp"
#include "entities/RangedWeapon3.hpp"
#include "entities/Robot.hpp"
#include "entities/Vehicle.hpp"
#include "entities/Villager.hpp"

/**
 * @brief Class for in populating Entities with Item objects and for managing in game buy/sell logic
 *
 */
class EntityItemTrading
{
private:
public:
    /**
     * @brief EntityInGameStore constructor
     *
     */
    EntityItemTrading() {}
    /**
     * @brief EntityManager Deconstructor
     *
     */
    ~EntityItemTrading() {}

    /**
     * @brief buy item in draw_store()
     */
    void buy_store_item()
    {
    }

    /**
     * @brief sell item in draw_store()
     */
    void sell_store_item()
    {
    }

    /**
     * @brief Draw item objects for sale in game
     *
     * If players reputaiton is high enough then enemies with high personality
     * to signify good NPC's will trade with the player, and touching those NPC's
     * will bring up option to trade with them, displaying their std::vector<Item *> inventoryForSale;
     *
     */
    void draw_store() {}

    /**
     * @brief lists of different items used in populate_enemy_inventory() to give different
     * items based on job. E.g.
     * Weapons seller = include all weapons/ammo together and in populate_enemy_inventory() if
     * NPC is an weapons seller then give them this lists items in their own inventory so player can
     * then buy in draw_store()
     */
    void vendor_lists()
    {

        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dis(0, 10);
        int random_choice = dis(gen);

        
    }

    /**
     * @brief populate inventory called after EntityManager.hpp creates entities, to give
     * individual Enemy subclass types their own item objects in their std::vector<Item> inventoryForSale;
     */
    void populate_enemy_inventory(std::vector<Entity *> &entitites)
    {
        for (Entity *e : entitites) {
            if (dynamic_cast<Villager*>(e) != nullptr) {
                // push them an item from above list vendor_list() ^^
            }
        }
    }
};
