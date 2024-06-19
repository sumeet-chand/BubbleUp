/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Definition file
    License: MIT License


    _________________________________________________________________________________________________

                                SDL UPDATES FUNCTIONS DEFINITIONS
    _________________________________________________________________________________________________


    DESCRIPTION

    Update functions for each game scene based on an SDL event loop. Triggers one time setups in
    game_enginesetups.hpp for each scene

    Declarations: ./headers/game_engineupdates.hpp
    Definitions: ./src/game_engineupdates.cpp


    EXAMPLE


*/

#include "../headers/game_engine_updates.hpp"
#include "../headers/game_engine_setups.hpp"
#include "../headers/game_engine_logic.hpp"

// Forward declarations
void initialise_score();
struct score;

void update_camera_collissions_logic()
{
    if (cameraRect.x < 0)
    {
        cameraRect.x = 0;
    }
    if (cameraRect.y < 0)
    {
        cameraRect.y = 0;
    }
    if (cameraRect.x > GAME_WORLD_WIDTH - cameraRect.w)
    {
        cameraRect.x = GAME_WORLD_WIDTH - cameraRect.w;
    }
    if (cameraRect.y > GAME_WORLD_HEIGHT - cameraRect.h)
    {
        cameraRect.y = GAME_WORLD_HEIGHT - cameraRect.h;
    }
}
void update_movement()
{
    // Called in every game scene, as well as the one time scene_x_setup()
    for (Entity *e : entities)
    {
        e->update_position_from_velocity();

        if (e->get_xVelocity() != 0.0f || e->get_yVelocity() != 0.0f)
        {
            e->update_deceleration(deceleration);
        }

        e->move_entity(acceleration);
        e->handle_player_collision(entities);
        e->handle_item_collision(entities);
        e->handle_enemy_collision(entities);
        e->handle_obstacle_collision(entities);
        e->collisions_prevent_leaving_game_world_bounds(GAME_WORLD_WIDTH, GAME_WORLD_HEIGHT);
    }
}
void update_scene_1()
{
    // Update scene 1 logic
}
void update_scene_2()
{
    // Update scene 2 logic
}
void update_scene_3()
{
    // Update scene 3 logic
}
void update_scene_4()
{
    if (scene4inputPlayerNameButton.get_clicked())
    {
        if (!scene4submitNameButton.get_clicked())
        {
            initialise_score();
            scene4submitNameButton.set_clicked(true);
        }
    }
}
void update_scene_5()
{
    // Update scene 5 logic
}
void update_scene_6()
{
    // Update scene 6 logic
}
void update_scene_7()
{
    // Update scene 7 logic
}
void update_scene_8()
{
    updateApp.clickedCheckForUpdates = false;
    updateApp.newVersionAvailable = false;
}
void update_scene_9()
{
    // Update scene 9 logic
    if (webserverClientContext.response_success())
    {
        // Create account was successfull
        scene = 11; // multiplayer lobby
    }
}
void update_scene_10()
{
    if (scene10acceptPrivacyPolicyButton.get_clicked() && scene10acceptTermsPolicyButton.get_clicked())
    {
        scene = 9;
    }
}
void update_scene_11()
{
    // Update scene 11 logic
}
void update_scene_12()
{
    // Update scene 12 logic
}
void update_scene_13()
{
    // Update scene 13 logic
}
void update_scene_14()
{
    // Update scene 14 logic
}
void update_scene_15()
{
    // Update scene 14 logic
}
void update_scene_28()
{
    // Update scene 28 logic
}
void update_scene_gameplay() // Sandbox
{
    // START GAME LOOP

    // FIRST - In game_engine_handles.hpp -> player moves -> POST_player_movement()

    // SECOND - Setup game/map/entities
    if (scene == 150 && !sceneMultiplayersetup)
    {
        setup_scene_multiplayer_game();
    }
    else if (scene == 100 && !scene100setup)
    {
        setup_scene_100();
    }
    else if (scene == 101 && !scene101setup)
    {
        setup_scene_101();
    }
    else if (scene == 102 && !scene102setup)
    {
        setup_scene_102();
    }
    else if (scene == 103 && !scene103setup)
    {
        setup_scene_103();
    }
    else if (scene == 104 && !scene104setup)
    {
        setup_scene_104();
    }
    else if (scene == 105 && !scene105setup)
    {
        setup_scene_105();
    }
    else if (scene == 106 && !scene106setup)
    {
        setup_scene_106();
    }
    else if (scene == 107 && !scene107setup)
    {
        setup_scene_107();
    }
    else if (scene == 108 && !scene108setup)
    {
        setup_scene_108();
    }
    else if (scene == 109 && !scene109setup)
    {
        setup_scene_109();
    }
    else if (scene == 110 && !scene110setup)
    {
        setup_scene_110();
    }
    else if (scene == 111 && !scene111setup)
    {
        setup_scene_111();
    }

    // get multiplayer state changes
    if (isMultiplayerGame)
    {
        webserverClientContext.GET_network_messages(entities, webserverHostContext);
    }

    for (Entity *e : entities)
    {
        // handle collisions
        e->handle_player_collision(entities);
        e->handle_item_collision(entities);
        e->handle_enemy_collision(entities);
        e->handle_obstacle_collision(entities);
        e->collisions_prevent_leaving_game_world_bounds(GAME_WORLD_WIDTH, GAME_WORLD_HEIGHT);

        // move entities
        e->update_position_from_velocity();
        if (e->get_xVelocity() != 0.0f || e->get_yVelocity() != 0.0f)
        {
            e->update_deceleration(deceleration);
        }
        e->move_entity(acceleration); // THIS SHOULD POST POSITION TO WEBSERVER OF MULTIPLAYER SAME AS BOT

        // move bots
        if (Bot *bot = dynamic_cast<Bot *>(e))
        {
            if (bot->update_should_bot_move())
            {
                bot->update_bot_movement(isMultiplayerGame, webserverClientContext, webserverHostContext);
                bot->set_last_bot_movement_time();
            }
        }

        if (Player *p = dynamic_cast<Player *>(e))
        {
            int cameraZoom = 1; // can change to global variable to control camera zoom in future
            // camera follows player
            cameraRect.x = p->get_rect().x * cameraZoom;
            cameraRect.y = p->get_rect().y * cameraZoom;
            // collission to ensure camera stays in bounds
            update_camera_collissions_logic();

            if (p->get_player_id() == clientPlayerID)
            {
                if (p->get_health() <= 0) // LOSE logic
                {
                    std::cout << "Game over" << std::endl;
                    delete p; // kick player out
                    setup_reset_game();
                    scene = 4; // post their score locally or to webserver
                }

                else if (p->get_score() == 2) // WIN logic
                {
                    p->set_game_winner(true);
                    std::cout << "Winner: " << p->get_player_id() << std::endl;
                    startTimer = false;
                    SDL_Delay(500);
                    unlockedAchievements[0] = 1;
                    setup_reset_game();
                    scene = 4;
                }
            }
        }
    }
    // LAST - In draw() -> draw entities. Then start loop again from top
}