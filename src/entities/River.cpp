/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Definition file
    License: MIT License
*/


#include "../../headers/entities/River.hpp"
#include "../../headers/globals.hpp" // to know particles vector

River::River(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) : Obstacle(name, x, y, width, height,  health, collisionSoundString, walkingTextures) {}

void River::handle_player_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        if (dynamic_cast<Player *>(e) != nullptr)
        {
            SDL_Rect playerRect = e->get_rect();
            SDL_Rect thisRect = this->get_rect();

            // Check for intersection between player and obstacle
            if (SDL_HasIntersection(&playerRect, &thisRect))
            {
                std::cout << "Player collided with an obstacle: " << e->get_entity_name() << std::endl;
                Mix_PlayChannel(-1, collisionSound, 0);
                // Play water particles animation
                int random = (rand() % 50) + 5;
                for (int i = 0; i < random; ++i)
                {
                    particles.push_back(ParticleGenerator(thisRect.x, thisRect.y, "water"));
                }

                // Determine the direction of collision
                int dx = playerRect.x + playerRect.w / 2 - thisRect.x - thisRect.w / 2;
                int dy = playerRect.y + playerRect.h / 2 - thisRect.y - thisRect.h / 2;

                int penetrationX = (playerRect.w + thisRect.w) / 2 - std::abs(dx);
                int penetrationY = (playerRect.h + thisRect.h) / 2 - std::abs(dy);

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
