/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

#pragma once

#include "globals.hpp"


/**
 * @brief when game scene/level starts this function sets initial entity spawn positions
 * 
 * This function is called with every new level/game scene to randomly spawn all entities
 * and spawn the player in the middle always, this prevents any collission with collision checks.
*/
void setup_entities_positions(std::vector<Entity *> &entities);
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_100();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_101();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_102();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_103();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_104();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_105();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_106();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_107();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_108();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_109();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_110();
/**
 * @brief when game scene/level starts this function sets all scene/level variables
 * 
 * This function is called with every new level/game scene to set times, toggle timer, call
 * setup_entities_positions() to set entity spawn points, play level music, etc.,
*/
void setup_scene_111();
/**
 * @brief on new game this resets all game variables.
 * 
 * Helpfull for resetting game when a new game was already started, if you go
 * to settings then return to title, then start a new game again, this will ensure
 * all game variables e.g. score, timer, health are reset 
*/
void setup_reset_game();
/**
 * @brief custom multiplayer game scene initialisation logic e.g. player can choose
 * what music, entities to spawn etc.,
 * 
*/
void setup_scene_multiplayer_game();
