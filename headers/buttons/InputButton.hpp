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
 * @brief SDL input text field subclass of BaseButton.hpp base class
 *
 * read the BaseButton.hpp comment block for more details
 */
class InputButton : public BaseButton
{
private:
    std::string inputText{}; /**< holds the value of text input into this text field button */
public:
    /**
     * @brief SDL input text field constructor
     *
     * Has 2 unique member variables for the text entered into the rect, and a bool to track if the text
     * was submitted. You can use this object along with a ClickableButton object to have a submit button
     * that triggers this buttons .set_clicked(true);
     *
     * Use an SDL handle to send text input to this button if selected
     * you can have an additional submit ClickableButton object that when clicked
     * you can set this button to set_clicked(true) then send the text somewher
     * e.g. a JSON string to a webserver
     *
     * EXAMPLE
     * else if (event.type == SDL_TEXTINPUT)
     * {
     *     // Need to use SDL_TEXTINPUT for live interactive type and render at same time
     *     for (BaseButton *button : allButtons)
     *     {
     *         if (button->is_selected())
     *         {
     *             if (InputButton *x = dynamic_cast<InputButton *>(button))
     *             {
     *                 x->set_text(event);
     *             }
     *         }
     *     }
     *     break;
     * }
     */
    InputButton(int x, int y, int width, int height, std::string buttonLabel, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
                const std::string buttonTexturePath, TTF_Font *buttonFont, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText)
        : BaseButton(x, y, width, height, buttonLabel, r, g, b, a, buttonTexturePath, buttonFont, redText, greenText, blueText, alphaText)
    {
        std::cout << "Constructed: Text input button: " << buttonLabel << std::endl;
    }

    /**
     * @brief get input text fields text
     *
     * e.g. You can enter a player name and on submit button, send this buttons inputText to an scoreboard
     */
    std::string get_text() const
    {
        return inputText;
    }

    /**
     * @brief write text to button
     *
     * Use an SDL handle to send text input to this button if selected
     */
    void set_text(const SDL_Event &event)
    {
        inputText += event.text.text;
    }

    /**
     * @brief set button submitted status
     *
     * After submitting text to reset all a buttons variables you can call these functions
     * scene4inputPlayerNameButton.clear_text();
     * scene4inputPlayerNameButton.set_clicked(false);
     */
    void clear_text()
    {
        inputText.clear();
    }

    /**
     * @brief remove the last character in text input field
     *
     * use a handle to listen to BACKSPACE key press then delete
     * last character in text input field
     *
     * EXAMPLE
     * case SDLK_BACKSPACE:
     *          std::cout << "You pressed: BACKSPACE" << std::endl;
     *          if (scene4inputPlayerNameButton.is_selected())
     *          {
     *              scene4inputPlayerNameButton.remove_last_character();
     *          }
     */
    void remove_last_character()
    {
        if (!inputText.empty())
        {
            inputText.pop_back();
        }
    }

    /**
     * @brief render a vertical straight arrow text cursor in text input field rect
     *
     * render a vertical straight arrow text cursor in text input field rect
     * called in render_button_rect
     */
    void render_cursor() const
    {
        // called in overridden render_button_rect()
        // Calculate the x-coordinate of the cursor (left side of the text input field)
        int cursorX = buttonRect.x;

        // Calculate the y-coordinate of the cursor (top of the text input field)
        int cursorY = buttonRect.y;

        // Calculate the height of the cursor line to match the height of the text input field
        int cursorHeight = buttonRect.h;

        // Set the width of the cursor line
        int cursorWidth = 5; // Adjust as needed

        // Create the cursor rectangle with calculated dimensions
        SDL_Rect cursorRect = {cursorX, cursorY, cursorWidth, cursorHeight};

        // Set the color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Render the cursor line
        SDL_RenderFillRect(renderer, &cursorRect);
    }

    /**
     * @brief render button rect
     *
     * Will render button with unique addition of render_cursor()
     */
    void render_button_rect() override
    {
        if (isSelected)
        {
            // Draw yellow border
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow border
            SDL_Rect borderRect = {buttonRect.x - 2, buttonRect.y - 2, buttonRect.w + 4, buttonRect.h + 4};
            SDL_RenderFillRect(renderer, &borderRect);

            // Draw Cursor within texture
            render_cursor();
        }

        // Draw button
        SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);

        // Render button text as you type
        render_button_text(buttonLabel, buttonRect, buttonTextColor);
    }
};
