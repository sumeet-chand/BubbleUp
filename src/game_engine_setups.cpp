/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Definition file
    License: MIT License
    

    _________________________________________________________________________________________________

                                SDL SETUPS FUNCTIONS DEFINITIONS
    _________________________________________________________________________________________________


    DESCRIPTION

    One time setup scene functions for Game, called during update() for specific scene loop e.g.
    update_scene_31(), which triggers a if(!scene102setup) {setup_scene_31(); which flags bool as true}

    Declarations: ./headers/game_engine_setups.hpp
    Definitions: ./src/game_engine_setups.cpp


    EXAMPLE


*/
#include <string>
#include <vector>
#include "../headers/EntityManager.hpp"
#include "../headers/game_engine_setups.hpp"

// Forward declarations
void load_music(const std::string &songTitle);
void toggle_countdown();

void setup_entities_positions(std::vector<Entity *> &entities)
{
    // You can remove this code if you want random world map placement, or duplicate and set a floag for spawning near each other or far away
    int playerCount{};
    for (Entity *e : entities) {
        if (Player *p = dynamic_cast<Player*>(e)) {
            p->set_rect_x_pos((((SCREEN_WIDTH - p->get_rect().w) / 2) + playerCount));
            p->set_rect_y_pos((((SCREEN_HEIGHT - p->get_rect().h) / 2) + playerCount));
            p->set_velocity(0.0, 0.0);
            playerCount += 100; // players will always spawn at least 50 width away from each other towards the centre of the screen
        }
        if (Bot *b = dynamic_cast<Bot*>(e)) {
            b->set_rect_x_pos((((SCREEN_WIDTH - b->get_rect().w) / 2) + playerCount));
            b->set_rect_y_pos((((SCREEN_HEIGHT - b->get_rect().h) / 2) + playerCount));
            b->set_velocity(0.0, 0.0);
            playerCount += 100; // players will always spawn at least 50 width away from each other towards the centre of the screen
        }
    }

    for (Entity *e : entities)
    {
        bool collisionDetected = true;
        while (collisionDetected)
        {
            collisionDetected = false;
            e->set_rect_x_pos(rand() % GAME_WORLD_WIDTH);
            e->set_rect_y_pos(rand() % GAME_WORLD_HEIGHT);

            // Check for collision with other entities
            for (Entity *other : entities)
            {
                if (e == other)
                    continue;

                SDL_Rect eRect = e->get_rect();
                SDL_Rect otherRect = other->get_rect();
                if (SDL_HasIntersection(&eRect, &otherRect))
                {
                    collisionDetected = true;
                    break;
                }
            }
        }
    }
}
void setup_scene_100() // Sandbox
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    EntityManager::create_bot_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    isMultiplayerGame = true;
    if (isMultiplayerGame) {
        webserverClientContext.POST_entity_vector_to_server(webserverHostContext, entities);
    }
    gameStarted = true;
    countdownSeconds = 86400; // 1 hour
    startTimer = true;
    toggle_countdown();
    scene100setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_101() // Tutorial
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene100setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_102() // level 1
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene102setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_103()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene103setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_104()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene104setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_105()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene105setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_106()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene106setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_107()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene107setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_108()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene108setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_109()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene109setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_110()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene110setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_scene_111()
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    clientPlayerID = 1;
    setup_entities_positions(entities);
    gameStarted = true;
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    scene111setup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}
void setup_reset_game()
{
    for (Entity *e : entities)
    {
        if (Player *p = dynamic_cast<Player *>(e))
        {
            if (p->get_player_id() == clientPlayerID)
            {
                e->set_score(0);
                e->set_health(2);
            }
        }
    }
    // For drawing scores reset
    scene4inputPlayerNameButton.clear_text();
    scene4inputPlayerNameButton.set_clicked(false);
    scene4submitNameButton.set_clicked(false);
    startTimer = false;
    gameOver = false; // Needed for toggle_countdown()
    gameStarted = false;
    scene100setup = false;
    scene101setup = false;
    scene102setup = false;
    scene103setup = false;
    scene104setup = false;
    scene105setup = false;
    scene106setup = false;
    scene107setup = false;
    scene108setup = false;
    scene109setup = false;
    scene110setup = false;
    scene110setup = false;
}
void setup_scene_multiplayer_game() 
{
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
    EntityManager::random_procedural_generation(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10, 10);
    EntityManager::create_player_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT, 2);
    setup_entities_positions(entities);
    countdownSeconds = 300;
    startTimer = true;
    toggle_countdown();
    sceneMultiplayersetup = true;
    std::cout << "Success: Setup scene: " << scene << std::endl;
}