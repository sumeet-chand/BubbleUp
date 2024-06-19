/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Definition file
    License: MIT License
*/

#include "../../headers/entities/Item.hpp"

Item::Item(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) : Entity(name, x, y, width, height,  health, collisionSoundString, walkingTextures) {}

void Item::handle_player_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {   
        if (dynamic_cast<Player*>(e) != nullptr)
        {
            SDL_Rect playerRect = e->get_rect();
            SDL_Rect thisRect = this->get_rect();
            if (SDL_HasIntersection(&thisRect, &playerRect))
            {
                Mix_PlayChannel(-1, collisionSound, 0);
            }
        }
    }
}

void Item::handle_item_collision(std::vector<Entity *> &entities)
{
    for (Entity *e : entities)
    {
        if (dynamic_cast<Item *>(e) != nullptr)
        {

            SDL_Rect itemRect1 = this->get_rect();
            SDL_Rect itemRect2 = e->get_rect();

            // Check if it's the same item instance
            if (e == this)
            {
                // No action needed when an item collides with itself
                // It's safe to ignore this collision
                continue;
            }

            // Check for intersection between two items
            if (SDL_HasIntersection(&itemRect1, &itemRect2))
            {
                std::cout << "Item collided with another item: " << e->get_entity_name() << std::endl;

                // Determine the direction of collision
                int dx = itemRect1.x + itemRect1.w / 2 - itemRect2.x - itemRect2.w / 2;
                int dy = itemRect1.y + itemRect1.h / 2 - itemRect2.y - itemRect2.h / 2;

                int penetrationX = (itemRect1.w + itemRect2.w) / 2 - std::abs(dx);
                int penetrationY = (itemRect1.h + itemRect2.h) / 2 - std::abs(dy);

                // Resolve collision
                if (penetrationX < penetrationY)
                {
                    // Horizontal collision
                    if (dx < 0)
                    {
                        itemRect1.x -= penetrationX / 2;
                        itemRect2.x += penetrationX / 2;
                    }
                    else
                    {
                        itemRect1.x += penetrationX / 2;
                        itemRect2.x -= penetrationX / 2;
                    }
                }
                else
                {
                    // Vertical collision
                    if (dy < 0)
                    {
                        itemRect1.y -= penetrationY / 2;
                        itemRect2.y += penetrationY / 2;
                    }
                    else
                    {
                        itemRect1.y += penetrationY / 2;
                        itemRect2.y -= penetrationY / 2;
                    }
                }

                // Adjust item positions
                this->set_rect(itemRect1.x, itemRect1.y, itemRect1.w, itemRect1.h);
                e->set_rect(itemRect2.x, itemRect2.y, itemRect2.w, itemRect2.h);
            }
        }
    }
}
