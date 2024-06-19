/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Score.hpp"
#include "Entity.hpp"
#include "entities/Player.hpp"

// Forward declarations
struct score;

/**
 * @brief Webserver Host class for game multiplayer
 *
 * Class web socket functions to connect to a remote destination webserver to POST data (e.g.
 * user data such as username, passwords, strings, or even game calls, JSON, etc.,) and recieve response.
 * Allowing dynamic asynchronous communication between a Client and Web Server to send and recieve data.
 *
 * This standalone file is the webserver host side. It however is designed to respond to the
 * client file GameWebserverClient.hpp bundled together.
 *
 * Used together the client executable can communicate with the webserver on it's public port and IP
 * interface to communicate.
 *
 * Declarations: ./headers/WebserverHost.hpp
 * Definitions: ./src/WebserverHost.cpp
 *
 */
class WebserverHost
{
private:
    std::string webserverIPAddress = "192.168.0.1"; /**< werbserver host IP address */
    int webserverPort = 8080;                       /**< webserver host port number */
    std::vector<Score> serverScores{};              /**< For leaderboard accepts score struct for players scorekeeping */
    std::vector<Entity *> serverEntities{};         /**< server keeps its own state of all entities to apply logic and pass on to all players clients */
    /**
     * @brief struct for holding player gameplay statistics for scoreboards/leaderboards/Competitive play
     */
public:
    /**
     * @brief Deconstructor for WebserverClient.
     */
    WebserverHost()
    {
        std::cout << "Constructed: WebserverClient" << std::endl;
    }
    /**
     * @brief Deonstructor for WebserverClient.
     */
    ~WebserverHost()
    {
        std::cout << "Destroyed: WebserverClient" << std::endl;
    }
    /**
     * @brief set the webserver entities to match the player entities on game startup
     * then it will incrementally update through client POST's
     * @param entities to be replaced by JSON STRING
     */
    void set_webserver_entities(std::vector<Entity *> entities)
    {
        serverEntities = entities;
    }
    /**
     * @brief get state of all webserver entities
     */
    std::vector<Entity *> get_webserver_entities() const
    {
        return serverEntities;
    }
    /**
     * @brief receives a score struct of player gameplay statistic to update single game leaderboard with last result
     * @param s to be replaced by JSON STRING
     */
    void webserver_process_single_game_player_score(const Score &s)
    {
        bool playerFound = false;
        // Iterate through the scores vector to find the player by playerID
        for (auto &existingScore : serverScores)
        {
            if (existingScore.playerID == s.playerID)
            {
                // Update the player's score and datetime
                existingScore.score = s.score;
                existingScore.datetime = s.datetime;
                playerFound = true;
                std::cout << "Updated Scoreboard time for " << s.playerID << " " << s.name << " to: " << s.datetime << std::endl;
                break;
            }
        }

        // If player was not found, add the new score entry
        if (!playerFound)
        {
            serverScores.push_back(s);
            std::cout << "Scoreboard time for " << s.playerID << " " << s.name << " is: " << s.datetime << std::endl;
        }
    }
    /**
     * @brief GET player movement
     * @param playerID to be replaced by JSON STRING
     * @param x to be replaced by JSON STRING
     * @param y to be replaced by JSON STRING
     * @param direction to be replaced by JSON STRING
     */
    void webserver_process_player_handle(int playerID, int x, int y, const std::string &direction)
    {
        // Find the player in the serverPlayers vector and update its position
        for (Entity *e : serverEntities)
        {
            if (Player *p = dynamic_cast<Player *>(e))
            {
                if (p->get_player_id() == playerID)
                {
                    p->set_rect_x_pos(x);
                    p->set_rect_y_pos(y);
                    // p->set_direction(direction);
                    std::cout << "Server updated player " << playerID << " position: x: " << p->get_rect().x << " y: " << p->get_rect().y << std::endl;
                    return;
                }
            }
        }
    }
    /**
     * @brief save webserver state to file
     */
    void save_webserver_state()
    {
    }
    /**
     * @brief load webserver state from file
     */
    void load_webserver_state()
    {
    }

    /**
     * @brief deserialisation step to update server entitites
     * @param entities in serialised data sent from multiplayer clients
    */
    void webserver_process_entity_vector(std::vector<Entity *> entities)
    {
        serverEntities = entities;
    }
    /**
     * @brief serialise server entities to send to clients
     * @return serverEntities serialised data
    */
    std::vector<Entity *> get_entities() const
    {
        return serverEntities;
    }
};
