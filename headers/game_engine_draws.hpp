/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

#pragma once

#include "globals.hpp"

// FORWARD DECLARATIONS
struct score;

/**
 * @brief Draw scores to window
 * 
 * initialise_scores() pushes back a struct score;
 * then to draw in your window/renderer call this function to display scores
 * e.g. player statistics such as name, datetime, highest score
 * 
*/
void draw_scores(const std::vector<score> &scores);
/**
 * @brief Draw timer to window
 * 
 * toggle_countdown() creates threads to start and stop timer controlled
 * by global variables
 * then to draw in your window/renderer call this function to display timer
 * 
 * It is not necessary to draw the timer for toggle_countdown() functionality in your program
 * but if you would like to set a texture to draw it, this function can be used
 * 
*/
void draw_timer();
/**
 * @brief Draw player statistics to main gameplay window
 * 
 * Draw player statistics to main gamplay window e.g. health, score, skills etc.,
*/
void draw_HUD();
/**
 * @brief camera logic
 *
 * When a player moves a direction the camera should stay centred on them. The steps are detailed below on how it's calculated.
 *
 * Step 1. Entities spawned into scene with player centered and all other entities in random rect.x and .y within GAME_WORLD_WIDTH and HEIGHT
 *     EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 20, 20, 20);
 *     initialise_static_entities(entities);
 *     setup_entities_positions();
 *
 * Step 2. SDL event loop contiously calls handle(), update(), draw()
 *
 * step 3. In handle() pressing left key SDLK_LEFT player1.set_velocity(player1.get_xVelocity() - acceleration, player1.get_yVelocity());
 *
 * step 4. In update() update_movement() which calls e->update_position_from_velocity();
 * which sets the rect.x or y to the velocity e.g. player moves from 500x to 400x, while 500y remains the same
 *
 * step 5. In draw() draw_entities() then calculates camera displacement SDL_Point cameraDisplacement = get_camera_displacement(player1);
 * so cameraDisplacement.x = 100x (difference between movement in step 4) and cameraDisplacement.y = 500y remains the same
 *
 * step 6. NOTE the camera doesn't move at all it always remains centered on the player. in reality all entities are drawn moving away from the
 * player by drawing their rect the displacement between the playerand them.
 *
 * in draw() the entities that aren't the player are drawn with a x position - cameraDisplacement.x e.g. 100x
 * and a y position of cameraDisplacement.y which hasn't changed. therefore if an enemy was at rect.x 300 it will be drawn at 300 - 100
 * and drawn at 200x ??????????????
 *
 * step 7. in draw() the player will be drawn in the middle of screen ??????
 */
void draw_entities();
/**
 * @brief Draw main menu to window/renderer
 * 
 * Draw main menu to window/renderer
*/
void draw_scene_1();
/**
 * @brief Draw settings menu to window/renderer
 * 
 * Draw settings menu to window/renderer
*/
void draw_scene_2();
/**
 * @brief Draw unlockables/bonus software features to window/renderer
 * 
 * Draw unlockables/bonus software features to window/renderer
*/
void draw_scene_3();
/**
 * @brief Draw Score menu to window/renderer
 * 
 * Draw Score menu to window/renderer
*/
void draw_scene_4();
/**
 * @brief Draw Help guide menu to window/renderer
 * 
 * Draw Help guide menu to window/renderer
*/
void draw_scene_5();
/**
 * @brief Draw Achievements menu to window/renderer
 * 
 * Draw Achievements menu to window/renderer
*/
void draw_scene_6();
/**
 * @brief Draw Check for updates menu to window/renderer
 * 
 * Draw Check for updates menu to window/renderer
*/
void draw_scene_7();
/**
 * @brief Draw online login menu to window/renderer
 * 
 * Draw online login menu to window/renderer
*/
void draw_scene_8();
/**
 * @brief Draw Create account menu to window/renderer
 * 
 * Draw Create account menu to window/renderer
*/
void draw_scene_9();
/**
 * @brief Draw Display policies menu to window/renderer
 * 
 * Draw Score Display policies menu to window/renderer
*/
void draw_scene_10();
/**
 * @brief Draw Multiplayer lobby menu to window/renderer
 * 
 * Draw Multiplayer lobby menu to window/renderer
*/
void draw_scene_11();
/**
 * @brief Draw Keybindings menu to window/renderer
 * 
 * Draw Keybindings menu to window/renderer
*/
void draw_scene_12();
/**
 * @brief Draw Create game menu to window/renderer
 * 
 * Draw Create game menu to window/renderer
*/
void draw_scene_13();
/**
 * @brief Draw Credits menu to window/renderer
 * 
 * Draw Credits menu to window/renderer
*/
void draw_scene_14();
/**
 * @brief Draw Level editor menu to window/renderer
 * 
 * Draw Level editor menu to window/renderer
*/
void draw_scene_15();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_16();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_17();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_18();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_19();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_20();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_21();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_22();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_23();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_24();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_25();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_26();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_27();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_28();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_29();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_30();
/**
 * @brief Draw Cutscene menu to window/renderer
 * 
 * Draw Cutscene menu to window/renderer
*/
void draw_scene_31();
/**
 * @brief Draw HUD to window/renderer
 * 
 * Draw main gameplay HUD e.g. timer, player statistics, entities, etc.,
*/
void draw_scene_gameplay();
