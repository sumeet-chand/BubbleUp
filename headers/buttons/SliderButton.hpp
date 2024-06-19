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
 * @brief SDL slider Button subclass of BaseButton.hpp base class
 *
 * read the BaseButton.hpp comment block for more details
 */
class SliderButton : public BaseButton
{
private:
    SDL_Rect sliderDotRect{}; /**< Slider control dot x-pos, y-pos, width and height */
    std::string sliderDotTexturePath{}; /**< slider control dot texture file path */
    SDL_Texture *sliderDotTexture{}; /**< holds slider control dot texture */

public:
    /**
     * @brief SliderButton constructir
     *
     * Has 3 unique private member variables to track location of the slider control dot you can move and drag with touch/mouse controls
     * to lower slider up or down within bounds of the underlying rect.
     * You can use texture of a horizontal line, or a slider dot texture.
     */
    SliderButton(int x, int y, int width, int height, std::string buttonLabel, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
                 const std::string buttonTexturePath, TTF_Font *buttonFont, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText,
                 int dotX, int dotY, int dotWidth, int dotHeight, std::string sliderDotTexturePath)
        : BaseButton(x, y, width, height, buttonLabel, r, g, b, a, buttonTexturePath, buttonFont, redText, greenText, blueText, alphaText),
          sliderDotRect({dotX, dotY, dotWidth, dotHeight}), sliderDotTexturePath(sliderDotTexturePath)
    {
        std::cout << "Constructed: Slider button subclass: " << buttonLabel << std::endl;
    }

    /**
     * @brief load slider dot texture
     *
     * You dont necessarily have to use a control dot texture, you can use anything e.g. horizontal bar
     */
    void set_slider_dot_texture()
    {
        sliderDotTexture = IMG_LoadTexture(renderer, sliderDotTexturePath.c_str());
        if (!sliderDotTexture)
        {
            std::cout << "Error: Failed to load button image: " << sliderDotTexturePath << IMG_GetError() << std::endl;
        }
    }

    /**
     * @brief render slider button with control dot
     *
     * The difference between this render_button_rect() and the BaseButton class is the extra drawing of the
     * slider control dot texture within bounds of underlying rect
     */
    void render_button_rect() override
    {
        // Overrides base class due to new line to draw dot
        if (isSelected)
        {
            // Draw - YELLOW border
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // yellow
            SDL_Rect borderRect = {buttonRect.x - 2, buttonRect.y - 2, buttonRect.w + 4, buttonRect.h + 4};
            SDL_RenderFillRect(renderer, &borderRect);
        }
        // Draw Button
        SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);

        // Draw Dot
        SDL_RenderCopy(renderer, sliderDotTexture, nullptr, &sliderDotRect);

        // Draw text
        render_button_text(buttonLabel, buttonRect, buttonTextColor);
    }

    /**
     * @brief get the sliders control dot rect position
     * @return slider control dot rect position
    */
    SDL_Rect get_dot_rect() const
    {
        return sliderDotRect;
    }

    /**
     * @brief set the sliders control dot x-axis rect position
     * @param x new x-axis position of slider dot
    */
    void set_dot_rect_x_pos(int x)
    {
        sliderDotRect.x = x;
    }

    /**
     * @brief set the sliders control dot y-axis rect position
     * @param y new y-axis position of slider dot
    */
    void set_dot_rect_y_pos(int y)
    {
        sliderDotRect.y = y;
    }
};
