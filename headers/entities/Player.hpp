/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/


#pragma once

#include "../Entity.hpp"
#include "Item.hpp"

/**
 * @brief Game Entity.hpp subclass for in game Player
 *
 * Defines the protagonist player for the game and multiplayer games.
 * read the Entity.hpp comment block for more details
 */
class Player : public Entity
{
private:
    bool gameWinner{}; /** used for tracking wins for game logic */
    int playerID{}; /** player id for multiplayer tracking players */
    SDL_GameController *controller{}; /** Link a SDL controller to a player */
    SDL_JoystickID controllerID{}; /** Link a SDL controller to a player */
    int reputation = 50; /**< Used for determining if player can trade/chat with enemy entity for immersive gameplay. 
    Increased with doing jobs, decreased with killing good alligned enemies based on enemy personality value towards 100 is good, 0 is towards bad */

public:
    /**
     * @brief Player class default constructor
     */
    Player(int playerID, const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);

    /**
     * @brief return player ID for multiplayer usage
     * @return player ID
     */
    int get_player_id() const;
    /**
     * @brief get details on which player won game
     * @return winner of game
     */
    bool get_game_winner() const;
    /**
     * @brief set gameWinner variable for update logic if player won game
     * @param won the status if they won game or not
     */
    void set_game_winner(bool won);
    /**
     * @brief return controller linked to player
     * @return SDLNcontroller linked to player
     */
    SDL_GameController *get_controller() const;
    /**
     * @brief set players controller, controlled through SDL handle event of controller activated
     * set to nullptr when sdl handle event controller deactivated
     * @param ctrl an controller single index element from a vector
     */
    void set_controller(SDL_GameController *ctrl);
    /**
     * @brief rumble the controller if available
     *
     * EXAMPLE
     * SDL_GameControllerRumble(controller, 0xFFFF * 3 / 4, 0xFFFF * 3 / 4, 500);
     * 1. Rumble both controllers left and right at 75% strength for 500ms
     * 0xFFFF * 3 / 4 = 75% rumble strength
     * 500 = miliseconds
     *
     * therefore you can swap 3 for a variable rumbleStrength and control the strength by making rumbleStrength either 1, 2, 3 or 4
     * with rumbleStrength = 1 being a light rumble, and 4 the strongest.
     *
     * SDL_GameControllerRumble(controller, 0xFFFF * rumbleStrength / 4, 0xFFFF * rumbleStrength / 4, 500);
     *
     */
    void rumble_controller(int rumbleStrength);
    /**
     * @brief set controller id to player object
     * @param id open controller id
    */
    void set_controller_instance_id(SDL_JoystickID id);
    /**
     * @brief get controller instance id
     * @return controller id linked to player
    */
    SDL_JoystickID get_controller_instance_id() const;
    
    /**
     * @brief handle player collission with another player
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_player_collision(std::vector<Entity *> &entities) override;
    /**
     * @brief handle player collission with an item
     *
     * Will pickup item, add to inventory, delete from entities vector
     *
     * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
     */
    void handle_item_collision(std::vector<Entity *> &entities) override;
};