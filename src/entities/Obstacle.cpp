/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Definition file
    License: MIT License
*/

#include "../../headers/entities/Obstacle.hpp"

Obstacle::Obstacle(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) : Entity(name, x, y, width, height,  health, collisionSoundString, walkingTextures) {}

void Obstacle::handle_player_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        if (dynamic_cast<Player *>(e) != nullptr)
        {
            SDL_Rect playerRect = e->get_rect();
            SDL_Rect obstacleRect = this->get_rect();

            // Check for intersection between player and obstacle
            if (SDL_HasIntersection(&playerRect, &obstacleRect))
            {
                std::cout << "Player collided with an obstacle: " << e->get_entity_name() << std::endl;
                Mix_PlayChannel(-1, collisionSound, 0);

                // Determine the direction of collision
                int dx = playerRect.x + playerRect.w / 2 - obstacleRect.x - obstacleRect.w / 2;
                int dy = playerRect.y + playerRect.h / 2 - obstacleRect.y - obstacleRect.h / 2;

                int penetrationX = (playerRect.w + obstacleRect.w) / 2 - std::abs(dx);
                int penetrationY = (playerRect.h + obstacleRect.h) / 2 - std::abs(dy);

                // Resolve collision
                if (penetrationX < penetrationY)
                {
                    // Horizontal collision
                    if (dx < 0)
                        playerRect.x -= penetrationX;
                    else
                        playerRect.x += penetrationX;
                }
                else
                {
                    // Vertical collision
                    if (dy < 0)
                        playerRect.y -= penetrationY;
                    else
                        playerRect.y += penetrationY;
                }

                // Adjust player's position
                e->set_rect(playerRect.x, playerRect.y, playerRect.w, playerRect.h);
            }
        }
    }
}

void Obstacle::handle_enemy_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        Enemy *enemy = dynamic_cast<Enemy *>(e);
        if (enemy != nullptr)
        {

            SDL_Rect enemyRect = e->get_rect();
            SDL_Rect obstacleRect = this->get_rect();

            // Check for intersection between enemy and obstacle
            if (SDL_HasIntersection(&enemyRect, &obstacleRect))
            {
                // Determine the direction of collision
                int dx = enemyRect.x + enemyRect.w / 2 - obstacleRect.x - obstacleRect.w / 2;
                int dy = enemyRect.y + enemyRect.h / 2 - obstacleRect.y - obstacleRect.h / 2;

                int penetrationX = (enemyRect.w + obstacleRect.w) / 2 - std::abs(dx);
                int penetrationY = (enemyRect.h + obstacleRect.h) / 2 - std::abs(dy);

                // Resolve collision
                if (penetrationX < penetrationY)
                {
                    // Horizontal collision
                    if (dx < 0)
                        enemyRect.x -= penetrationX;
                    else
                        enemyRect.x += penetrationX;
                }
                else
                {
                    // Vertical collision
                    if (dy < 0)
                        enemyRect.y -= penetrationY;
                    else
                        enemyRect.y += penetrationY;
                }

                // Adjust enemy's position
                e->set_rect(enemyRect.x, enemyRect.y, enemyRect.w, enemyRect.h);
            }
        }
    }
}

void Obstacle::handle_item_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        Item *item = dynamic_cast<Item *>(e);
        if (item != nullptr)
        {

            SDL_Rect itemRect = e->get_rect();
            SDL_Rect obstacleRect = this->get_rect();

            // Check for intersection between item and obstacle
            if (SDL_HasIntersection(&itemRect, &obstacleRect))
            {
                std::cout << "Item collided with an obstacle: " << e->get_entity_name() << std::endl;
                Mix_PlayChannel(-1, collisionSound, 0);

                // Determine the direction of collision
                int dx = itemRect.x + itemRect.w / 2 - obstacleRect.x - obstacleRect.w / 2;
                int dy = itemRect.y + itemRect.h / 2 - obstacleRect.y - obstacleRect.h / 2;

                int penetrationX = (itemRect.w + obstacleRect.w) / 2 - std::abs(dx);
                int penetrationY = (itemRect.h + obstacleRect.h) / 2 - std::abs(dy);

                // Resolve collision
                if (penetrationX < penetrationY)
                {
                    // Horizontal collision
                    if (dx < 0)
                        itemRect.x -= penetrationX;
                    else
                        itemRect.x += penetrationX;
                }
                else
                {
                    // Vertical collision
                    if (dy < 0)
                        itemRect.y -= penetrationY;
                    else
                        itemRect.y += penetrationY;
                }

                // Adjust item's position
                e->set_rect(itemRect.x, itemRect.y, itemRect.w, itemRect.h);
            }
        }
    }
}

void Obstacle::handle_obstacle_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {

        Obstacle *obstacle = dynamic_cast<Obstacle *>(e);
        if (obstacle != nullptr)
        {

            SDL_Rect obstacleRect1 = e->get_rect();
            SDL_Rect obstacleRect2 = this->get_rect();

            // Check if it's the same obstacle instance
            if (e == this)
            {
                // No action needed when an obstacle collides with itself
                // It's safe to ignore this collision
                continue;
            }

            // Check for intersection between two obstacles of different types
            if (SDL_HasIntersection(&obstacleRect1, &obstacleRect2))
            {
                std::cout << "Obstacle collided with another obstacle: " << e->get_entity_name() << std::endl;
                Mix_PlayChannel(-1, collisionSound, 0);

                // Determine the direction of collision
                int dx = obstacleRect1.x + obstacleRect1.w / 2 - obstacleRect2.x - obstacleRect2.w / 2;
                int dy = obstacleRect1.y + obstacleRect1.h / 2 - obstacleRect2.y - obstacleRect2.h / 2;

                int penetrationX = (obstacleRect1.w + obstacleRect2.w) / 2 - std::abs(dx);
                int penetrationY = (obstacleRect1.h + obstacleRect2.h) / 2 - std::abs(dy);

                // Resolve collision
                if (penetrationX < penetrationY)
                {
                    // Horizontal collision
                    if (dx < 0)
                    {
                        obstacleRect1.x -= penetrationX / 2;
                        obstacleRect2.x += penetrationX / 2;
                    }
                    else
                    {
                        obstacleRect1.x += penetrationX / 2;
                        obstacleRect2.x -= penetrationX / 2;
                    }
                }
                else
                {
                    // Vertical collision
                    if (dy < 0)
                    {
                        obstacleRect1.y -= penetrationY / 2;
                        obstacleRect2.y += penetrationY / 2;
                    }
                    else
                    {
                        obstacleRect1.y += penetrationY / 2;
                        obstacleRect2.y -= penetrationY / 2;
                    }
                }

                // Adjust obstacle positions
                e->set_rect(obstacleRect1.x, obstacleRect1.y, obstacleRect1.w, obstacleRect1.h);
                this->set_rect(obstacleRect2.x, obstacleRect2.y, obstacleRect2.w, obstacleRect2.h);
            }
        }
    }
}
