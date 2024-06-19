/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Class Declaration file
    License: MIT License
*/

#pragma once

#include "BaseButton.hpp"

/**
 * @brief SDL Push Button subclass of BaseButton.hpp base class
 *
 * read the BaseButton.hpp comment block for more details
 */
class ClickableButton : public BaseButton
{
private:
public:
    /**
     * @brief default push button constructor
     *
     * Has no unique methods or variables. Used only as a push button so that on handle() you can select/trigger something on click
     * see BaseButton.hpp comments for full example details
     */
    ClickableButton(int x, int y, int width, int height, std::string buttonLabel, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
                    const std::string buttonTexturePath, TTF_Font *buttonFont, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText)
        : BaseButton(x, y, width, height, buttonLabel, r, g, b, a, buttonTexturePath, buttonFont, redText, greenText, blueText, alphaText)
    {
        std::cout << "Constructed: Clickable button subclass: " << buttonLabel << std::endl;
    }
};
