/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/

#include "../../headers/entities/Bot.hpp"

Bot::Bot(int playerID, const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) 
: Player(playerID, name, x, y, width, height, health, collisionSoundString, walkingTextures), gen(std::random_device{}()), dis(0, 3) {};

bool Bot::update_should_bot_move()
{
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastBotMovementTime).count();
    return elapsedTime >= 2000; // Adjust this value to change the delay (in milliseconds)
}

std::chrono::steady_clock::time_point Bot::set_last_bot_movement_time()
{
    lastBotMovementTime = std::chrono::steady_clock::now();
    return lastBotMovementTime;
}

void Bot::update_bot_movement(bool isMultiplayerGame, WebserverClient &webserverClientContext, WebserverHost &webserverHostContext)
{
    int random_choice = dis(gen);
    if (isMultiplayerGame)
    {
        switch (random_choice)
        {
        case 0:
            webserverClientContext.POST_player_movement(get_player_id(), 0, -5, "UP", webserverHostContext);
            break;
        case 1:
            webserverClientContext.POST_player_movement(get_player_id(), 0, 5, "DOWN", webserverHostContext);
            break;
        case 2:
            webserverClientContext.POST_player_movement(get_player_id(), -5, 0, "LEFT", webserverHostContext);
            break;
        case 3:
            webserverClientContext.POST_player_movement(get_player_id(), 5, 0, "RIGHT", webserverHostContext);
            break;
        default:
            std::cerr << "Error: Invalid random choice" << std::endl;
            break;
        }
    }
    else
    {
        switch (random_choice)
        {
        case 0:
            set_rect_x_pos(0);
            set_rect_y_pos(-5);
            break;
        case 1:
            set_rect_x_pos(0);
            set_rect_y_pos(5);
            break;
        case 2:
            set_rect_x_pos(-5);
            set_rect_y_pos(0);
            break;
        case 3:
            set_rect_x_pos(5);
            set_rect_y_pos(0);
            break;
        default:
            std::cerr << "Error: Invalid random choice" << std::endl;
            break;
        }
    }
}