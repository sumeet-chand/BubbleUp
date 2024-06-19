/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Class Declaration file
    License: MIT License
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for std::min/max
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// Forward declarations
class Item;
class Skill;
class Player;
class Enemy;
class Obstacle;

/**
 * @brief Classes to initialise and integrate Game entities into a project e.g, players,
 * items, enemies and obstacles
 *
 * This C++ class and following subclasses are part of Game Development best practice, of
 * encapsulating common characteristics of video games such as characters/avatars/players, enemies,
 * items/objects, skills and obstacles/walls.
 *
 * You create a vector of entities, then use procedural generation to define specific or random
 * entity attributes such as health, texture file path, dimensions, which then pushes them back to
 * the vector.
 *
 * You then create functions to iterate over the vector to set the texture as per Entity class
 * functions for initialisation.
 *
 * Then the last step is to implement the vector in your game by calling various movement,
 * collision, update logic in your update game loop logic.
 *
 * Player handles can be created to control movement by keys effecting velocity passed onto functions
 * set_rect_x_pos() and set_rect_y_pos(0)
 *
 * The default Entities below can be adapted easily for any type of game. E.g. You can rename Hearts
 * to Potion, and Gem to Money, or water to lava.
 *
 * Note: Enemies subclass refers to both hostile entities e.g, attacking monsters and non-hostile
 * entities e.g., NPCs, pets, followers, quest givers, shop keepers etc.,
 *
 * Base and Subclasses
 * * headers/Entity.hpp:   Base class declaration file
 * * Entity.cpp:           Base class definition file
 * * headers/Player.hpp:   Player subclass declaration file
 * * Player.cpp:           Player subclass definition file
 * * headers/Item.hpp:     Item subclass declaration file
 * * Item.cpp:             Item subclass definition file
 * * headers/Enemy.hpp:    Enemy subclass declaration file
 * * Enemy.cpp:            Enemy subclass definition file
 *
 *
 * EXAMPLE
 *
 * Entities are initialised with EntityManager.hpp
 */
class Entity
{
protected:
    SDL_Renderer *renderer{};                                       /**< pointer to renderer set with set_renderer() for drawing entity */
    const std::string name{};                                       /**< name of object e.g. Player1, or enemy2 */
    SDL_Rect rect{};                                                /**< entity x-pos, y-pos, width and length */
    int health{};                                                   /**< entities in game health */
    std::string collisionSoundString{};                             /**< file path of collission sound .wav */
    std::vector<std::string> walkingTextures{};                     /**< for animation */
    Mix_Chunk *collisionSound{};                                    /**< holds collission sound .wav in SDL_mixer format */
    SDL_Texture *texture{};                                         /**< holds texture value of  walkingTextures */
    float xVelocity{};                                              /**< x-pos velocity of entity */
    float yVelocity{};                                              /**< y-pos velocity of entity */
    float zVelocity{};                                              /**< z-pos velocity of entity */
    std::chrono::steady_clock::time_point lastAccelerationChange{}; /**< Used for random movement of entities */
    bool accelerateX{};                                             /**< Used for random movement of entities */
    int score{};                                                    /**< entity in game score/xp/money etc., */
    std::vector<Item *> inventory{};                                /**< inventory of all item subclasses picked up */
    std::vector<Item *> inventoryForSale{};                         /**< inventory of all item subclasses picked up */
    std::vector<Skill *> skills{};                                  /**< inventory of all skills subclasses picked up */
    std::vector<Item *> notes{};                                    /**< inventory of all journal subclasses picked up for quests/jobs/notes */
    bool hasCollided{};                                             /**< On player collied with unpassable object set this flag true as API for controller rumble */
    int currentAnimationFrame{};                                    /**< for animation */
    std::chrono::steady_clock::time_point lastFrameChange{};        /**< for animation */
    const int animationDelay = 200;                                 /**< for animation */
    std::string texturePath{};                                      /**< for animation */
    std::unordered_map<std::string, SDL_Texture *> textureMap{};    /**< for animation */
    int zPos{};                                                     /**< 3D Height position. Cannot represent in member SDL_Rect rect */
    float acceleration = 0.5f;                                      /**< value to modify velocity for moving entity */
    float Decceleration = 0.01f;                                    /**< value to modify velocity for moving entity */

public:
    /**
     * @brief Entity class constructor
     *
     */
    Entity(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures) : name(name), rect({x, y, width, height}), health(health), collisionSoundString(collisionSoundString), walkingTextures(walkingTextures)
    {
        std::cout << "Success: Constructed Entity object: " << name << std::endl;
        lastFrameChange = std::chrono::steady_clock::now();
    }
    /**
     * @brief Entity class deconstructor
     *
     */
    virtual ~Entity() {}
    /**
     * @brief for changingn entity animations calculate difference between last frame rate
     *
     */
    void update_animation()
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameChange).count();

        if (elapsedTime >= animationDelay)
        {
            lastFrameChange = currentTime;
            currentAnimationFrame = (currentAnimationFrame + 1) % walkingTextures.size();

            texturePath = walkingTextures[currentAnimationFrame];
        }
    }
    /**
     * @brief load Entity animations into vector from constructor passed file path
     */
    void preload_textures()
    {
        for (const auto &filePath : walkingTextures)
        {
            if (textureMap.find(filePath) == textureMap.end())
            {
                // Texture not found, load it
                texture = IMG_LoadTexture(renderer, filePath.c_str());
                if (!texture)
                {
                    std::cerr << "Error: Failed to load texture: " << filePath << IMG_GetError() << std::endl;
                }
                else
                {
                    // Texture loaded successfully, store it in the map
                    textureMap[filePath] = texture;
                    // std::cout << "Success: Texture loaded: " << filePath << std::endl;
                }
            }
        }
    }
    /**
     * @brief set current animation texture from vector
     *
     */
    void set_animation_texture()
    {
        if (!texturePath.empty())
        {
            // Try to find texture in the map
            auto it = textureMap.find(texturePath);
            if (it != textureMap.end())
            {
                // Texture found in the map, use it
                texture = it->second;
            }
            else
            {
                // Texture not found, load it
                texture = IMG_LoadTexture(renderer, texturePath.c_str());
                if (!texture)
                {
                    std::cerr << "Error: Failed to load texture: " << texturePath << IMG_GetError() << std::endl;
                }
                else
                {
                    // Texture loaded successfully, store it in the map
                    textureMap[texturePath] = texture;
                    std::cout << "Success: Texture loaded: " << texturePath << std::endl;
                }
            }
        }
    }
    /**
     * @brief dynamically set renderer
     * @param r pass a SDL_Renderer *r object for this entity to render on with render_texture()
     * */
    void set_renderer(SDL_Renderer *r)
    {
        renderer = r;
    }
    /**
     * @brief load entity sound into private member variable passed from constructor
     */
    void set_sound()
    {
        collisionSound = Mix_LoadWAV(collisionSoundString.c_str());
        if (collisionSound == nullptr)
        {
            std::cerr << "Error: Failed to load sound: " << collisionSound << ": " << Mix_GetError() << std::endl;
        }
    }
    /**
     * @brief render current texture set from set_animation_texture() in draw loop
     *
     * EXAMPLE
     *
     * draw() {
     *    player1.update_animation();
     *    player1.set_animation_texture();
     *    player1.render_texture(player1.get_rect());
     * }
     *
     * @param rect the positions and dimensions to draw the entity texture on the renderer
     */
    void render_texture(int x, int y)
    {
        SDL_Rect cameraDisplacement = {x, y, get_rect().w, get_rect().y};
        SDL_RenderCopy(renderer, texture, nullptr, &cameraDisplacement);
    }

    /**
     * @brief return entity name
     *
     * @return name of entity object
     */
    std::string get_entity_name() const
    {
        return name;
    }

    /**
     * @brief return entity health to use with set_health() to increase or decrease health
     *
     * EXAMPLE
     *
     * 1. For adding health e.g. picking up a health potion item
     *
     * set_health(get_health() + 1)
     *
     * @return health of entity
     */
    int get_health() const
    {
        return health;
    }
    /**
     * @brief set entity health to use with get_health() to increase or decrease health
     *
     * EXAMPLE
     *
     * 1. For adding health e.g. picking up a health potion item
     *
     * set_health(get_health() + 1)
     *
     * @param h is the health value of entity
     */
    void set_health(int h)
    {
        health = h;
    }

    /**
     * @brief draw items in inventory
     */
    std::vector<Item *> get_inventory() const
    {
        return inventory;
    }
    /**
     * @brief add item to entities inventory
     *
     * e.g. buying an item, or picking it up, or gaining reward from a quest...
     *
     * EXAMPLE
     *
     * 1. if a Player or Enemy collides with an item they pick it up and
     * its removed from world
     *
     * for (auto it = entities.begin(); it != entities.end(); ++it)
     * {
     *     Entity *e = *it;
     *     Item *item = dynamic_cast<Item *>(e);
     *     if (item != nullptr)
     *     {
     *         SDL_Rect playerRect = this->get_rect();
     *         SDL_Rect itemRect = item->get_rect();
     *         if (SDL_HasIntersection(&playerRect, &itemRect))
     *         {
     *             std::cout << "You collided with an item: " << item->get_entity_name() << std::endl;
     *             add_item(item);
     *             it = entities.erase(it);
     *             delete item;
     *             if (it == entities.end())
     *                 break;
     *             else
     *                 continue;
     *         }
     *     }
     * }
     *
     * @param item to add from entities inventory
     */
    void add_item(Item *item)
    {
        if (inventory.size() < 10)
        {
            inventory.push_back(item);
        }
    }
    /**
     * @brief use the item in inventory
     *
     * In handle key input logic if you click/press on an inventory item or click/press use item button
     * then use the item
     */
    void use_item(Item *item)
    {
        auto foundItem = std::find(inventory.begin(), inventory.end(), item);
        if (foundItem != inventory.end())
        {
            item_effect();
            remove_inventory_item(item);
        }
    }
    /**
     * @brief subclass item effect to be overwritten by each private member subclass
     */
    virtual void item_effect()
    {
    }
    /**
     * @brief remove an item from an entities inventory
     *
     * @param item to remove from entities inventory
     */
    void remove_inventory_item(Item *item)
    {
        auto foundItem = std::find(inventory.begin(), inventory.end(), item);
        if (foundItem != inventory.end())
            inventory.erase(foundItem);
    }

    /**
     * @brief draw note in notes
     */
    std::vector<Item *> get_notes() const
    {
        return notes;
    }
    /**
     * @brief add note to entities notes
     *
     * e.g. buying an note, or picking it up, or gaining reward from a quest...
     *
     * EXAMPLE
     *
     * 1. if a Player or Enemy collides with an note they pick it up and
     * its removed from world
     *
     * for (auto it = entities.begin(); it != entities.end(); ++it)
     * {
     *     Entity *e = *it;
     *     note *note = dynamic_cast<note *>(e);
     *     if (note != nullptr)
     *     {
     *         SDL_Rect playerRect = this->get_rect();
     *         SDL_Rect noteRect = note->get_rect();
     *         if (SDL_HasIntersection(&playerRect, &noteRect))
     *         {
     *             std::cout << "You collided with an note: " << note->get_entity_name() << std::endl;
     *             add_note(note);
     *             it = entities.erase(it);
     *             delete note;
     *             if (it == entities.end())
     *                 break;
     *             else
     *                 continue;
     *         }
     *     }
     * }
     *
     * @param note to add from entities notes
     */
    void add_note(Item *note)
    {
        if (notes.size() < 10)
        {
            notes.push_back(note);
        }
    }
    /**
     * @brief use the note in notes
     *
     * In handle key input logic if you click/press on an notes note or click/press use note button
     * then use the note
     */
    void use_note(Item *note)
    {
        auto foundnote = std::find(notes.begin(), notes.end(), note);
        if (foundnote != notes.end())
        {
            note_effect();
        }
    }
    /**
     * @brief subclass note effect to be overwritten by each private member subclass
     */
    virtual void note_effect()
    {
    }
    /**
     * @brief remove an note from an entities notes
     *
     * @param note to remove from entities notes
     */
    void remove_notes_note(Item *note)
    {
        auto foundnote = std::find(notes.begin(), notes.end(), note);
        if (foundnote != notes.end())
            notes.erase(foundnote);
    }

    /**
     * @brief get skills in skills
     * @return skills vector for drawing, or for calculations
     */
    std::vector<Skill *> get_skills() const
    {
        return skills;
    }
    /**
     * @brief add skill to entities skills
     *
     * e.g. buying an skill, or picking it up, or gaining reward from a quest...
     *
     * EXAMPLE
     *
     * 1. if a Player or Enemy collides with an skill they pick it up and
     * its removed from world
     *
     * for (auto it = entities.begin(); it != entities.end(); ++it)
     * {
     *     Entity *e = *it;
     *     skill *skill = dynamic_cast<skill *>(e);
     *     if (skill != nullptr)
     *     {
     *         SDL_Rect playerRect = this->get_rect();
     *         SDL_Rect skillRect = skill->get_rect();
     *         if (SDL_HasIntersection(&playerRect, &skillRect))
     *         {
     *             std::cout << "You collided with an skill: " << skill->get_entity_name() << std::endl;
     *             add_skill(skill);
     *             it = entities.erase(it);
     *             delete skill;
     *             if (it == entities.end())
     *                 break;
     *             else
     *                 continue;
     *         }
     *     }
     * }
     *
     * @param skill to add from entities skills
     */
    void add_skill(Skill *skill)
    {
        if (skills.size() < 10)
        {
            skills.push_back(skill);
        }
    }
    /**
     * @brief use the skill in skills
     *
     * In handle key input logic if you click/press on an skills skill or click/press use skill button
     * then use the skill
     */
    void use_skill(Skill *skill)
    {
        auto foundskill = std::find(skills.begin(), skills.end(), skill);
        if (foundskill != skills.end())
        {
            skill_effect();
        }
    }
    /**
     * @brief subclass skill effect to be overwritten by each private member subclass
     */
    virtual void skill_effect()
    {
    }
    /**
     * @brief remove an skill from an entities skills
     *
     * @param skill to remove from entities skills
     */
    void remove_skills_skill(Skill *skill)
    {
        auto foundskill = std::find(skills.begin(), skills.end(), skill);
        if (foundskill != skills.end())
            skills.erase(foundskill);
    }

    /**
     * @brief get entity rect position and dimensions
     *
     * @return rect x-pos, y-pos, width and height of the entity for collission/rendering etc., logic
     */
    SDL_Rect get_rect() const { return rect; }
    /**
     * @brief get entity Z position
     * @return rect z position e.g. for jumping
     */
    int get_z_pos() const { return zPos; }
    /**
     * @brief set entity rect position and dimensions
     *
     * @param x the 2D x position of entity
     * @param y the 2D y position of entity
     * @param width the entities width e.g. how wide they will render to screen e.g. house front
     * @param height the entities height e.g. how wide they will render to screen e.g. house side/depth
     */
    void set_rect(int x, int y, int width, int height)
    {
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
    }
    /**
     * @brief set entities x-pos e.g, for camera displacement or velocity calculations
     *
     * @param x the 2D x position of entity
     */
    void set_rect_x_pos(int x)
    {
        rect.x = x;
    }
    /**
     * @brief set entities y-pos e.g, for camera displacement or velocity calculations
     *
     * @param y the 2D y position of entity
     */
    void set_rect_y_pos(int y)
    {
        rect.y = y;
    }
    /**
     * @brief set entities z-pos e.g, for jumping
     *
     * @param z the 2D y position of entity
     */
    void set_z_pos(int z)
    {
        zPos = z;
    }

    /**
     * @brief get entities x-pos direction movement
     *
     * @return xVelocity x-pos accelerating velocitry of entity
     */
    float get_xVelocity() const { return xVelocity; }
    /**
     * @brief get entities y-pos direction movement
     *
     * @return xVelocity y-pos accelerating velocitry of entity
     */
    float get_yVelocity() const { return yVelocity; }
    /**
     * @brief get entities z-pos direction movement
     *
     * @return xVelocity z-pos accelerating velocitry of entity
     */
    float get_zVelocity() const { return zVelocity; }
    /**
     * @brief get acelleration for movement handle modifying velocity
     * each entity has their own unique acceleration, to control their own speeds with modifiers
     * e.g. using an boots item object increases acceleration due to running faster effect
     * @return acceleration of entity e.g. player moves at
     */
    float get_acceleration() const
    {
        return acceleration;
    }
    /**
     * @brief set acelleration for movement handle modifying velocity
     * each entity has their own unique acceleration, to control their own speeds with modifiers
     * e.g. using an boots item object increases acceleration due to running faster effect
     * @param a the required acceleration
     */
    void set_acceleration(float a)
    {
        acceleration = a;
    }
    /**
     * @brief set entities x-pos and y-pos velocity for direction movement
     *
     * @param xVel the x-pos direction velocity of entity to set
     * @param yVel the y-pos direction velocity of entity to set
     */
    void set_velocity(float xVel, float yVel)
    {
        xVelocity = xVel;
        yVelocity = yVel;
    }

    /**
     * @brief get entities score/xp/money
     *
     * used with set_score() to add money/xp/score to entity e.g. for adding money to the player for spending/dropping later
     *
     * @return score
     */
    int get_score() const { return score; }
    /**
     * @brief set entities score/xp/money
     *
     * @param s score/xp/money of entity e.g. for adding money to the player for spending/dropping later
     */
    void set_score(int s) { score = s; }

    /**
     * @brief move entity based on either player handle() or entity->move_entity() random/path movement
     */
    void update_position_from_velocity()
    {
        rect.x += static_cast<int>(xVelocity);
        rect.y += static_cast<int>(yVelocity);
    }

    /**
     * @brief apply decelerating physics logic to entity when they stop moving
     */
    void update_deceleration(float deceleration)
    {
        // std::cout << "Decelerating Y Velocity: " << player1.get_xVelocity() << std::endl;
        // std::cout << "Decelerating X Velocity: " << yVelocity << std::endl;

        if (yVelocity < 0.0f) // move up y--
        {
            yVelocity += deceleration; // Increase y-velocity
            if (yVelocity > 0.0f)      // if y++ too much reset to 0.0
            {
                yVelocity = 0.0f;
            }
        }
        else if (yVelocity > 0.0f) // moving down y++
        {
            yVelocity -= deceleration; // Decrease y-velocity
            if (yVelocity < 0.0f)      // if y-- too much, reset to 0.0
            {
                yVelocity = 0.0f;
            }
        }

        if (xVelocity < 0.0f) // move left x--
        {
            xVelocity += deceleration; // Increase x-velocity
            if (xVelocity > 0.0f)      // if x++ too much, reset to 0.0
            {
                xVelocity = 0.0f;
            }
        }
        else if (xVelocity > 0.0f) // move right x++ accelerate
        {
            xVelocity -= deceleration; // Decrease x-velocity
            if (xVelocity < 0.0f)
            {
                xVelocity = 0.0f; // if x-- too much, reset to 0.0
            }
        }
    }

    /**
     * @brief move entity based on either player handle() or entity->move_entity() random/path movement
     * @param acceleration the modifier to move the entity rect a direction
     */
    virtual void move_entity(float acceleration) {};

    /**
     * @brief entities collission logic with a player e.g. they attack it, and get pushed back
     *
     */
    virtual void handle_player_collision(std::vector<Entity *> &entities) {};

    /**
     * @brief entities collission logic with a player e.g. they add_item()
     */
    virtual void handle_item_collision(std::vector<Entity *> &entities) {};

    /**
     * @brief entities collission logic with a player e.g. they attack it, ad get pushed back
     */
    virtual void handle_enemy_collision(std::vector<Entity *> &entities) {};

    /**
     * @brief entities collission logic with a player e.g. they get pushed back
     */
    virtual void handle_obstacle_collision(std::vector<Entity *> &entities) {};
    /**
     * @brief entities collission logic with world boundary e.g. they get pushed back
     */
    void collisions_prevent_leaving_game_world_bounds(int GAME_WORLD_WIDTH, int GAME_WORLD_HEIGHT)
    {
        if (rect.x < 0)
        {
            rect.x = 0;
        }
        else if (rect.x + rect.w > GAME_WORLD_WIDTH)
        {
            rect.x = GAME_WORLD_WIDTH - rect.w;
        }

        if (rect.y < 0)
        {
            rect.y = 0;
        }
        else if (rect.y + rect.h > GAME_WORLD_HEIGHT)
        {
            rect.y = GAME_WORLD_HEIGHT - rect.h;
        }
    }
};
