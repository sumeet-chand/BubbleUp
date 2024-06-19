/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/

#pragma once

#include "../Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

/**
 * @brief Game Entity.hpp subclass for in game Skills
 *
 * Game Entity subclass, Skill base class for defining common features related to
 * various Skill elements in a game e.g, Healing for increasing health
 */
class Skill : public Entity
{
public:
    /**
     * @brief default constructor
     */
    Skill(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
};
