/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/


#pragma once

#include "Player.hpp"
#include "random"
#include "WebserverClient.hpp"
#include "WebserverHost.hpp"

class Bot : public Player {
private:
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    std::chrono::steady_clock::time_point lastBotMovementTime;

public:
    Bot(int playerID, const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);

    bool update_should_bot_move();

    std::chrono::steady_clock::time_point set_last_bot_movement_time();

    void update_bot_movement(bool isMultiplayerGame, WebserverClient &webserverClientContext, WebserverHost &webserverHostContext);
};