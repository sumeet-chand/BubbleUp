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
 * To be used to add a drop down button that on click shows a list of
 * all drop down buttons. You can dynamically add or remove buttons from the list.
 * An example use case would be for a navigation bar menu e.g, the traditional Windows
 * File -> save as, windows options.
 *
 * EXAMPLE
 *
 * to implement see the BaseButton.hpp comments
 */
class DropdownButton : public BaseButton
{
private:
    std::vector<BaseButton *> dropdownList{}; /** list of buttons to show in drop down list*/

public:
    /**
     * @brief DropdownButton button constructor
     *
     */
    DropdownButton(int x, int y, int width, int height, std::string buttonLabel, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
                   const std::string buttonTexturePath, TTF_Font *buttonFont, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText)
        : BaseButton(x, y, width, height, buttonLabel, r, g, b, a, buttonTexturePath, buttonFont, redText, greenText, blueText, alphaText)
    {
        std::cout << "Constructed: DropdownButton button: " << buttonLabel << std::endl;
    }

    /**
     * @brief list all the drop down buttons
     *
     * When this button is_clicked() or ENTERED, it will show all available drop down buttons.
     * EXAMPLE
     * if (scene2resolutionsDropdownButton.get_clicked())
     * {
     *     scene2resolutionsDropdownButton.render_buttons_from_dropdown_list(renderer);
     * }
     */
    void render_buttons_from_dropdown_list(SDL_Renderer *&renderer)
    {
            for (BaseButton *b : dropdownList)
            { // for every button in this drop down list
                if (b->is_selected())
                {                                                  // if the button is already selected
                    this->set_button_label(b->get_button_label()); // change this buttons label to that button
                }
                for (int i = 0; i < dropdownList.size(); i++)
                {
                    SDL_Rect thisRect = this->get_rect();
                    b->set_rect_x_pos(thisRect.x);            // then draw all the buttons on same column as this button
                    b->set_rect_y_pos(thisRect.y + (i * 10)); // draw all buttons in a new row
                    b->render_button_rect();
                }
            }
    }

    /**
     * @brief add buttons to drop down list
     *
     * Dynamically set the buttons to show in the drop down list by adding them
     * with this function
     */
    void add_button_to_dropdown_list(BaseButton &button)
    {
        dropdownList.push_back(&button);
    }

    /**
     * @brief remove buttons from drop down list
     *
     * Dynamically remove buttons to show in the drop down list by removing them
     * with this function
     */
    void remove_button_from_dropdown_list(BaseButton &button)
    {
        auto it = std::find(dropdownList.begin(), dropdownList.end(), &button);

        if (it != dropdownList.end())
        {
            dropdownList.erase(it);
        }
    }
};
