/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Definition file
    License: MIT License
*/


#include "../../headers/entities/Bomb.hpp"
#include "../../headers/globals.hpp" // to know particles vector

Bomb::Bomb(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) : Enemy(name, x, y, width, height,  health, collisionSoundString, walkingTextures) {}

void Bomb::handle_player_collision(std::vector<Entity *> &entities)
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
                e->set_health(e->get_health() - 1);
                // Play fire particles animation
                int random = (rand() % 50) + 5;
                for (int i = 0; i < random; ++i)
                {
                    particles.push_back(ParticleGenerator(thisRect.x, thisRect.y, "fire"));
                }
            }
        }
    }
}

void Bomb::move_entity(float acceleration)
{
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastAccelerationChange).count();

    if (elapsedTime > 2000)
    { // Change acceleration every 2 seconds (adjust as needed)
        // Randomly decide whether to accelerate in X or Y direction
        accelerateX = std::rand() % 2 == 0;

        // Reset the timer
        lastAccelerationChange = currentTime;
    }

    float maxVelocity = 2.0f;

    if (accelerateX)
    {
        // Accelerate in X direction
        set_velocity(std::min(maxVelocity, get_xVelocity() + acceleration), get_yVelocity());
    }
    else
    {
        // Accelerate in Y direction
        set_velocity(get_xVelocity(), std::min(maxVelocity, get_yVelocity() + acceleration));
    }

    // Update the entity's position based on the velocity
    rect.x += static_cast<int>(get_xVelocity());
    rect.y += static_cast<int>(get_yVelocity());
}
