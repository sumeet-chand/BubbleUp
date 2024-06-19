/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Definition file
    License: MIT License
*/

#include "../../headers/entities/Enemy.hpp"

Enemy::Enemy(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) : Entity(name, x, y, width, height,  health, collisionSoundString, walkingTextures) {}

void Enemy::handle_player_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        SDL_Rect thisRect = this->get_rect();
        Player *player = dynamic_cast<Player *>(e);
        if (player != nullptr)
        {
            // Collision with enemy
            SDL_Rect playerRect = e->get_rect();
            if (SDL_HasIntersection(&thisRect, &playerRect))
            {
                Mix_PlayChannel(-1, collisionSound, 0);
                // Play some animation possible swining sword to attack player and making noise
            }
        }
    }
}

void Enemy::handle_item_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        SDL_Rect thisRect = this->get_rect();
        Player *player = dynamic_cast<Player *>(e);
        if (player != nullptr)
        {
            // Collision with enemy
            SDL_Rect playerRect = e->get_rect();
            if (SDL_HasIntersection(&thisRect, &playerRect))
            {
                // Enemy does not pickup items currently
            }
        }
    }
}

void Enemy::handle_enemy_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        Enemy *enemy = dynamic_cast<Enemy *>(e);
        if (enemy != nullptr)
        {
            SDL_Rect enemyRect1 = this->get_rect();
            SDL_Rect enemyRect2 = e->get_rect();

            // Check if it's the same enemy instance
            if (e == this)
            {
                // No action needed when an enemy collides with itself
                // It's safe to ignore this collision
                continue;
            }

            // Check for intersection between two enemies
            if (SDL_HasIntersection(&enemyRect1, &enemyRect2))
            {
                std::cout << "Enemy collided with another enemy: " << e->get_entity_name() << std::endl;

                // Determine the direction of collision
                int dx = enemyRect1.x + enemyRect1.w / 2 - enemyRect2.x - enemyRect2.w / 2;
                int dy = enemyRect1.y + enemyRect1.h / 2 - enemyRect2.y - enemyRect2.h / 2;

                int penetrationX = (enemyRect1.w + enemyRect2.w) / 2 - std::abs(dx);
                int penetrationY = (enemyRect1.h + enemyRect2.h) / 2 - std::abs(dy);

                // Resolve collision
                if (penetrationX < penetrationY)
                {
                    // Horizontal collision
                    if (dx < 0)
                    {
                        enemyRect1.x -= penetrationX / 2;
                        enemyRect2.x += penetrationX / 2;
                    }
                    else
                    {
                        enemyRect1.x += penetrationX / 2;
                        enemyRect2.x -= penetrationX / 2;
                    }
                }
                else
                {
                    // Vertical collision
                    if (dy < 0)
                    {
                        enemyRect1.y -= penetrationY / 2;
                        enemyRect2.y += penetrationY / 2;
                    }
                    else
                    {
                        enemyRect1.y += penetrationY / 2;
                        enemyRect2.y -= penetrationY / 2;
                    }
                }

                // Adjust enemy positions
                this->set_rect(enemyRect1.x, enemyRect1.y, enemyRect1.w, enemyRect1.h);
                e->set_rect(enemyRect2.x, enemyRect2.y, enemyRect2.w, enemyRect2.h);
            }
        }
    }
}
