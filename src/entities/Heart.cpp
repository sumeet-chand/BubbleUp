/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Definition file
    License: MIT License
*/

#include "../../headers/entities/Heart.hpp"

Heart::Heart(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) : Item(name, x, y, width, height,  health, collisionSoundString, walkingTextures) {}

void Heart::handle_player_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        if (dynamic_cast<Player*>(e) != nullptr)
        {
            SDL_Rect thisRect = this->get_rect();
            SDL_Rect playerRect = e->get_rect();
            if (SDL_HasIntersection(&thisRect, &playerRect))
            {
                Mix_PlayChannel(-1, collisionSound, 0);
                e->set_health(e->get_health() + 1);
            }
        }
    }
}
