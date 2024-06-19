/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Subclass Declaration file
    License: MIT License
*/


#pragma once

#include "Skill.hpp"

/**
 * @brief Skill subclass heart increases health on contact
 *
 */
class Heal : public Skill
{
public:
    /**
     * @brief default constructor
     */
    Heal(const std::string name, int x, int y, int width, int height, int health, std::string collisionSoundString, const std::vector<std::string> &walkingTextures);
};
