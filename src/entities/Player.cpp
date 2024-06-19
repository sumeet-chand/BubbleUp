/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Definition file
    License: MIT License
*/

#include "../../headers/entities/Player.hpp"

Player::Player(int playerID, const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) : Entity(name, x, y, width, height, health, collisionSoundString, walkingTextures), playerID(playerID) {}

int Player::get_player_id() const
{
    return playerID;
}

bool Player::get_game_winner() const
{
    return gameWinner;
}

void Player::set_game_winner(bool won)
{
    gameWinner = won;
}

SDL_GameController *Player::get_controller() const
{
    return controller;
}

void Player::set_controller(SDL_GameController* ctrl) {
    controller = ctrl;
    if (ctrl) {
        controllerID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(ctrl));
        rumble_controller(3);
        std::cout << "Success: assigned entity: " << this->name << " controller: " << ctrl << std::endl;
    } else {
        controllerID = -1;
        std::cout << "Error: Couldn't assign controller to entity: " << this->name << std::endl;
    }
}

void Player::rumble_controller(int rumbleStrength)
{
    if (SDL_GameControllerRumble(controller, 0xFFFF * rumbleStrength / 4, 0xFFFF * rumbleStrength / 4, 500) != 0)
    {
        std::cerr << "Error: Failed to rumble controller: " << controller << " " << SDL_GetError() << std::endl;
    }
}

void Player::set_controller_instance_id(SDL_JoystickID id) {
    controllerID = id;
}

SDL_JoystickID Player::get_controller_instance_id() const {
    return controllerID;
}

void Player::handle_player_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        Player *player = dynamic_cast<Player *>(e);
        if (player != nullptr)
        {

            SDL_Rect playerRect1 = this->get_rect();
            SDL_Rect playerRect2 = e->get_rect();

            // Check if it's the same player instance
            if (e == this)
            {
                // No action needed when a player collides with itself
                // It's safe to ignore this collision
                continue;
            }

            // Check for intersection between two players
            if (SDL_HasIntersection(&playerRect1, &playerRect2))
            {
                std::cout << "Player collided with another player: " << e->get_entity_name() << std::endl;
                rumble_controller(1);

                // Determine the direction of collision
                int dx = playerRect1.x + playerRect1.w / 2 - playerRect2.x - playerRect2.w / 2;
                int dy = playerRect1.y + playerRect1.h / 2 - playerRect2.y - playerRect2.h / 2;

                int penetrationX = (playerRect1.w + playerRect2.w) / 2 - std::abs(dx);
                int penetrationY = (playerRect1.h + playerRect2.h) / 2 - std::abs(dy);

                // Resolve collision
                if (penetrationX < penetrationY)
                {
                    // Horizontal collision
                    if (dx < 0)
                    {
                        playerRect1.x -= penetrationX / 2;
                        playerRect2.x += penetrationX / 2;
                    }
                    else
                    {
                        playerRect1.x += penetrationX / 2;
                        playerRect2.x -= penetrationX / 2;
                    }
                }
                else
                {
                    // Vertical collision
                    if (dy < 0)
                    {
                        playerRect1.y -= penetrationY / 2;
                        playerRect2.y += penetrationY / 2;
                    }
                    else
                    {
                        playerRect1.y += penetrationY / 2;
                        playerRect2.y -= penetrationY / 2;
                    }
                }

                // Adjust player positions
                this->set_rect(playerRect1.x, playerRect1.y, playerRect1.w, playerRect1.h);
                e->set_rect(playerRect2.x, playerRect2.y, playerRect2.w, playerRect2.h);
            }
        }
    }
}

void Player::handle_item_collision(std::vector<Entity *> &entities)
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        Entity *e = *it;
        Item *item = dynamic_cast<Item *>(e);
        if (item != nullptr)
        {
            SDL_Rect playerRect = this->get_rect();
            SDL_Rect itemRect = item->get_rect();
            if (SDL_HasIntersection(&playerRect, &itemRect))
            {
                std::cout << "You collided with an item: " << item->get_entity_name() << std::endl;
                rumble_controller(1);
                add_item(item);
                it = entities.erase(it);
                delete item;
                if (it == entities.end())
                    break;
                else
                    continue;
            }
        }
    }
}

// /**
//  * @brief handle player collission with an enemy
//  *
//  * rumble controller
//  *
//  * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
//  */
// void handle_enemy_collision(std::vector<Entity *> &entities)
// {
//     for (Entity *e : entities)
//     {
//         Player *player = dynamic_cast<Player *>(e);
//         if (player != nullptr)
//         {
//             SDL_Rect playerRect = this->get_rect();
//             SDL_Rect enemyRect = e->get_rect();

//             // Check if it's the same player instance
//             if (e == this)
//             {
//                 // No action needed when a player collides with itself
//                 // It's safe to ignore this collision
//                 continue;
//             }

//             // Check for intersection between two players
//             if (SDL_HasIntersection(&playerRect, &enemyRect))
//             {
//                 std::cout << "Player collided with another enemy: " << e->get_entity_name() << std::endl;
//                 rumble_controller(1);
//             }
//         }
//     }
// }

// /**
//  * @brief handle player collission with an obstacle
//  *
//  * rumble controller
//  *
//  * @param entities the vector of all entities in a scene e.g. items, enemies, players, obstalces
//  */
// void handle_obstacle_collision(std::vector<Entity *> &entities)
// {
//     for (Entity *e : entities)
//     {
//         Player *player = dynamic_cast<Player *>(e);
//         if (player != nullptr)
//         {
//             SDL_Rect playerRect = this->get_rect();
//             SDL_Rect obstacleRect = e->get_rect();

//             // Check if it's the same player instance
//             if (e == this)
//             {
//                 // No action needed when a player collides with itself
//                 // It's safe to ignore this collision
//                 continue;
//             }

//             // Check for intersection between two players
//             if (SDL_HasIntersection(&playerRect, &obstacleRect))
//             {
//                 std::cout << "Player collided with another obstacle: " << e->get_entity_name() << std::endl;
//                 rumble_controller(2);
//             }
//         }
//     }
// }