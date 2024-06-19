/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Class Declaration file
    License: MIT License
*/

#pragma once

#include <iostream>
#include <algorithm> // for std::find in DropownButton
#include <string>
#include <cmath>  // for std::fabs() velocity, and sqrt for button class Euclidean distance calculations
#include <limits> // For Shortest path - Euclidean Distance calculation
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/**
 * @brief A Base class for initialisating SDL button subclasses e.g. push buttons, sliders, text fields
 *
 *_________________________________________________________________________________________________
 *
 *                                    SDL BUTTON BASE CLASS
 *_________________________________________________________________________________________________
 *
 *
 * DESCRIPTION:
 *
 * The C++ language SDL Framework code below can be implemented in any SDL derived project
 * as a method to create button object instances of many variations such as radio buttons,
 * volume slider buttons, Input text fields and submit buttons.
 *
 * The steps below outline the method to initialise, add to a vector, and handle the objects.
 *
 * Button navigation includes multiple variations from shortest path key direction algorithms
 * to find nearest button using directional keyboard/gamepad movement to clicking and even dragging
 * buttons.
 *
 * REQUIREMENTS
 *
 * The below libraries are required to instantiate the buttons
 * * SDL2
 * * SDL2_ttf
 * * SDL2_image
 *
 *_______________________________________________________________________________________________
 *
 *
 * EXAMPLE:
 *
 * Optional: Use comment button placement image below to design layout
 *
 *
 *    0           1            2            3            4            5            6            7            8            9            10
 *    __________________________________________________________________________________________________________________________________ 0
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 1
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 2
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 3
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 4
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 5
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 6
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 7
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 8
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________| 9
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |            |            |            |            |            |            |            |            |            |            |
 *   |____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
 *
 *  1. Include BaseButton header. It includes all button subclasses.
 *
 *  include <BaseButton.hpp>
 *
 * _______________________________________________________________________________________________
 *
 *  2. Create global variables for tracking mouse/and key press and release
 *  (Optional for SliderButton) as well as create global variables for x and y drag offset for mouse
 *  click and drag to change SliderButton dot rect.
 *
 *
 *  int xDragOffset = 0;
 *  int yDragOffset = 0;
 *  bool mousePressed = false;
 *  bool keyPressed = false;
 *  std::string buttonDirection = "";
 *
 *  _______________________________________________________________________________________________
 *
 *  3. Initliase subclass button instances and load appropriate texture file paths
 *
 *      ClickableButton scene2ReturnToTitleButton{
 *          static_cast<int>(SCREEN_WIDTH * 0.7),                  // int X-coordinate
 *          static_cast<int>(SCREEN_HEIGHT * 0.2),                 // int Y-coordinate
 *          static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
 *          static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
 *          "Return",                                              // Button label
 *          144, 238, 144, 255,                                    // Button color (RGBA)
 *          "assets/graphics/buttons/settings/restart-button.png", // Button texture path
 *          defaultFont,                                           // Button font
 *          0, 0, 0, 1};                                           // Text color (RGBA)
 *      InputButton scene4inputPlayerNameButton{
 *          static_cast<int>(SCREEN_WIDTH * 0.5),  // int X-coordinate
 *          static_cast<int>(SCREEN_HEIGHT * 0.4), // int Y-coordinate
 *          static_cast<int>(SCREEN_WIDTH * 0.4),  // Width
 *          static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
 *          "Input Player name",                   // Button label
 *          255, 255, 255, 255,                    // Button color (RGBA)
 *          "assets/graphics/boxes/button.png",    // Button texture path
 *          defaultFont,                           // Button font
 *          0, 0, 0, 255,};                        // Text color (RGBA)
 *      SliderButton scene2VolumeSliderButton{
 *          static_cast<int>(SCREEN_WIDTH * 0.25),       // int X-coordinate
 *          static_cast<int>(SCREEN_HEIGHT * 0.8),       // int Y-coordinate
 *          static_cast<int>(SCREEN_WIDTH * 0.5),        // Width
 *          static_cast<int>(SCREEN_HEIGHT * 0.1),       // Height
 *          "Volume Slider",                             // Button label
 *          144, 238, 144, 255,                          // Button color (RGBA)
 *          "assets/graphics/boxes/Slider_button_2.png", // Button texture path
 *          defaultFont,                                 // Button font
 *          0, 0, 0, 1,                                  // Text color (RGBA)
 *          static_cast<int>(SCREEN_WIDTH * 0.4),        // dot int X-coordinate
 *          static_cast<int>(SCREEN_HEIGHT * 0.8),       // dot int Y-coordinate
 *          static_cast<int>(SCREEN_WIDTH * 0.05),       // dot Width
 *          static_cast<int>(SCREEN_HEIGHT * 0.05),      // dot Height
 *          "assets/graphics/boxes/Slider_dot.png"};     // dot Texture path
 *
 *  _______________________________________________________________________________________________
 *
 *  4. Create vectors of different buttons
 *
 *  std::vector<BaseButton *> scene2buttons;
 *  std::vector<BaseButton *> allButtons;
 *
 *  _______________________________________________________________________________________________
 *
 *  5. Create a static pointer global variable to keep track of selected button
 *
 *  BaseButton *BaseButton::selectedButton = nullptr;
 *
 *  _______________________________________________________________________________________________
 *
 *  6.  (Optional) For each scene/page, Create function to push back button subclass instances to
 *  BaseButton vector and remember to call function
 *
 *  void load_buttons_to_scene_vectors()
 *  {
 *      scene2buttons.push_back(&scene4playerNameSubmitButton);
 *      scene2buttons.push_back(&scene4inputPlayerNameButton);
 *  }
 *
 *  _______________________________________________________________________________________________
 *
 *  7.  Create function to push load all scene vectors into an allButtons vector
 *  and remember to call function
 *
 *  void load_buttons_to_all_buttons_vector()
 *  {
 *      allButtons.insert(allButtons.end(), scene2buttons.begin(), scene2buttons.end());
 *  }
 *
 *  _______________________________________________________________________________________________
 *
 *  8. Call a function once to set all button textures from the button constructor texture filepath
 *  and remember to call function
 *
 *  void initialise_button_textures()
 *  {
 *      for (BaseButton *button : allButtons)
 *      {
 *          button->set_button_texture();
 *      }
 *  }
 *
 *  _______________________________________________________________________________________________
 *
 *  9. (Optional for SliderButton) if you have a SliderButton Instance
 *  to render slider button dot textures replace above step 6 code with below to
 *  to static cast search only those button types and render that dot texture also
 *  and remember to call function
 *
 *  void initialise_button_textures()
 *  {
 *      for (BaseButton *button : allButtons)
 *      {
 *          button->set_button_texture();
 *          if (SliderButton *x = dynamic_cast<SliderButton *>(button)) {
 *              x->set_slider_dot_texture();
 *          }
 *      }
 *  }
 *
 *  _______________________________________________________________________________________________
 *
 *  10. Call a function once to set all button fonts from the button constructor
 *
 *  void initialise_button_fonts()
 *  {
 *      for (BaseButton *button : allButtons)
 *      {
 *          button->set_font_size(defaultFont, 24);
 *      }
 *  }
 *
 *  _______________________________________________________________________________________________
 *
 *  11. Create all relevant handles
 *
 *  void handle()
 *  {
 *      while (SDL_PollEvent(&event) != 0)
 *      {
 *          if (event.type == SDL_QUIT)
 *          {
 *              std::cout << "Game Quitting" << std::endl;
 *              quitEventLoop = true;
 *          }
 *          else if (event.type == SDL_KEYDOWN)
 *          {
 *              keyPressed = true;
 *              if (scene == 1)
 *              {
 *                  handle_keyboard_scene_1(event);
 *              }
 *          }
 *          else if (event.type == SDL_KEYUP)
 *          {
 *              keyPressed = false;
 *              if (scene == 1)
 *              {
 *                  handle_keyboard_scene_1(event);
 *              }
 *          }
 *          else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_FINGERDOWN)
 *          {
 *              mousePressed = true;
 *              int mouseX, mouseY;
 *              if (event.type == SDL_MOUSEBUTTONDOWN)
 *              {
 *                  SDL_GetMouseState(&mouseX, &mouseY);
 *              }
 *              else if (event.type == SDL_FINGERDOWN)
 *              {
 *                  mouseX = static_cast<int>(event.tfinger.x * SCREEN_WIDTH);
 *                  mouseY = static_cast<int>(event.tfinger.y * SCREEN_HEIGHT);
 *              }
 *              if (scene == 1)
 *              {
 *                  handle_mouse_scene_1(mouseX, mouseY);
 *              }
 *          }
 *          else if (event.type == SDL_MOUSEBUTTONUP)
 *          {
 *              mousePressed = false;
 *          }
 *          else if (event.type == SDL_CONTROLLERBUTTONDOWN) // for gamepad input
 *          {
 *              SDL_ControllerButtonEvent controllerButtonEvent = event.cbutton;
 *              int button = controllerButtonEvent.button;
 *              if (scene == 1)
 *              {
 *                  handle_gamepad_scene_1(button);
 *              }
 *          }
 *      }
 *  }
 *
 *  _______________________________________________________________________________________________
 *
 *  11a. Create Keyboard, Mouse/Touch, Gamepad relevant handles
 *
 *  e.g. MOUSE/TOUCH HANDLES
 *
 *  SDL_Point mousePosition = {mouseX, mouseY};
 *  if (scene2ReturnToTitleButton.is_clicked(mousePosition))
 *  {
 *      scene = 1;
 *  }
 *
 *
 *  _______________________________________________________________________________________________
 *
 *  11b. e.g, KEYBOARD HANDLES, remember to call the static function to check button direction
 *  against the global variable ButtonDirection set locally
 *  buttonDirection = "UP";
 *  BaseButton::find_nearest_button(scene1buttons, buttonDirection);
 *
 *
 *
 *  void handle_keyboard_scene_1(SDL_Event &event)
 *  {
 *  if (keyPressed)
 *  {
 *      switch (event.key.keysym.sym)
 *      {
 *      case SDLK_ESCAPE:
 *          std::cout << "You pressed: ESC" << std::endl;
 *          quitEventLoop = true;
 *          break;
 *      case SDLK_UP:
 *          std::cout << "You pressed: UP" << std::endl;
 *          buttonDirection = "UP";
 *          BaseButton::find_nearest_button(scene1buttons, buttonDirection);
 *          break;
 *      case SDLK_DOWN:
 *          std::cout << "You pressed: DOWN" << std::endl;
 *          buttonDirection = "DOWN";
 *          BaseButton::find_nearest_button(scene1buttons, buttonDirection);
 *          break;
 *      case SDLK_LEFT:
 *          std::cout << "You pressed: LEFT" << std::endl;
 *          buttonDirection = "LEFT";
 *          BaseButton::find_nearest_button(scene1buttons, buttonDirection);
 *          break;
 *      case SDLK_RIGHT:
 *          std::cout << "You pressed: RIGHT" << std::endl;
 *          buttonDirection = "RIGHT";
 *          BaseButton::find_nearest_button(scene1buttons, buttonDirection);
 *          break;
 *      case SDLK_RETURN:
 *          std::cout << "You pressed: RETURN" << std::endl;
 *          if (scene1newGameButton.is_selected())
 *          {
 *              logic_newgame();
 *              scene = 3;
 *          }
 *          else if (scene1settingsButton.is_selected())
 *          {
 *              scene = 2;
 *          }
 *          else if (scene1quitGameButton.is_selected())
 *          {
 *              quitEventLoop = true;
 *          }
 *      default:
 *          break;
 *  }
 *  }
 *  }
 *  _______________________________________________________________________________________________
 *
 *  11c. e.g, GAMEPAD HANDLES
 *
 *  case SDL_CONTROLLER_BUTTON_A:
 *  std::cout << "You pressed: RETURN" << std::endl;
 *  if (scene2ReturnToTitleButton.is_selected())
 *  {
 *      scene = 1;
 *  }
 *
 *
 *  _______________________________________________________________________________________________
 *
 *  11d. (Optional - for SliderButton) Create keyboard case movements if desired to global variables
 *  for the slider option to increment or decrement.
 *
 *  int soundVolume = 100;
 *
 *  case SDLK_UP:
 *      std::cout << "You pressed: UP" << std::endl;
 *      if (scene2VolumeSliderButton.is_selected())
 *      {
 *          soundVolume = std::min(100, soundVolume + 1);
 *      }
 *      break;
 *  case SDLK_DOWN:
 *      std::cout << "You pressed: DOWN" << std::endl;
 *      if (scene2VolumeSliderButton.is_selected())
 *      {
 *          soundVolume = std::max(0, soundVolume - 1);
 *      }
 *
 *
 *  In handle() add a new SDL_MOUSEMOTION case that sees if button is selected and if so
 *  add a option to drag dot texture
 *
 *  else if (event.type == SDL_MOUSEMOTION)
 *  {
 *      if (mousePressed)
 *      {
 *          for (BaseButton *button : allButtons)
 *          {
 *              if (button->is_selected())
 *              {
 *                  if (SliderButton *b = dynamic_cast<SliderButton *>(button))
 *                  {
 *                      int mouseX, mouseY;
 *                      SDL_GetMouseState(&mouseX, &mouseY);
 *                      int x = mouseX - xDragOffset;
 *                      b->set_dot_rect_x_pos(x);
 *                      int y = mouseY - yDragOffset;
 *                      b->set_dot_rect_y_pos(y);
 *
 *                      // Ensure texture stays within the bounds of the SliderButton rectangle
 *                      if (b->get_dot_rect().x < button->get_rect().x)
 *                      {
 *                      b->set_dot_rect_x_pos(button->get_rect().x);
 *                      }
 *                      else if (b->get_dot_rect().x + b->get_dot_rect().w > button->get_rect().x + button->get_rect().w)
 *                      {
 *                      int x = button->get_rect().x + button->get_rect().w - b->get_dot_rect().w;
 *                      b->set_dot_rect_x_pos(x);
 *                      }
 *
 *                      if (b->get_dot_rect().y < button->get_rect().y)
 *                      {
 *                      b->set_dot_rect_y_pos(button->get_rect().y);
 *                      }
 *                      else if (b->get_dot_rect().y + b->get_dot_rect().h > button->get_rect().y + button->get_rect().h)
 *                      {
 *                      int y = button->get_rect().y + button->get_rect().h - b->get_dot_rect().h;
 *                      b->set_dot_rect_y_pos(y);
 *                      }
 *
 *                      // Update soundVolume global variable
 *                      // Calculate the position of the dot texture relative to the SliderButton rectangle
 *                      double relativePosition = (b->get_dot_rect().x - button->get_rect().x) / (double)(button->get_rect().w - b->get_dot_rect().w);
 *                      // Calculate the sound volume based on the relative position
 *                      soundVolume = static_cast<int>(relativePosition * 100);
 *                      // Ensure that the sound volume is within the range of 0 to 100
 *                      soundVolume = std::max(0, std::min(100, soundVolume));
 *                  }
 *              }
 *          }
 *     }
 * }
 *
 *  _______________________________________________________________________________________________
 *
 *  11e. (Optional - for InputButton)
 *
 *  In handle() add a new SDL_TEXTINPUT case that sees if button is selected and if so
 *  add a option to live enter text to button
 *
 *  else if (event.type == SDL_TEXTINPUT)
 *  {
 *      // Need to use SDL_TEXTINPUT for live interactive type and render at same time
 *      for (BaseButton *button : allButtons)
 *      {
 *          if (button->is_selected())
 *          {
 *              if (InputButton *x = dynamic_cast<InputButton *>(button))
 *              {
 *                  x->set_text(event);
 *              }
 *          }
 *      }
 *  break;
 *  }
 *
 *  add new case in scene with input field for SDLK_BACKSPACE to call remove_last_character() for deleting
 *  characters for interactive text session
 *
 *  case SDLK_BACKSPACE:
 *  std::cout << "You pressed: BACKSPACE" << std::endl;
 *  if (scene4inputPlayerNameButton.is_selected())
 *  {
 *      scene4inputPlayerNameButton.remove_last_character();
 *  }
 *  break;
 *  _______________________________________________________________________________________________
 *
 *  12. Render the textures in your draw()
 *
 *  void draw_scene_3()
 *  {
 *      for (Entity *e : entities)
 *      {
 *          e->render_texture();
 *      }
 *  }
 *
 *  _______________________________________________________________________________________________
 *
 *  13. Remember to clear Vectors before ending program
 *
 *  scene1buttons.clear();
 *  scene2buttons.clear();
 *  allButtons.clear();
 *
 *  _______________________________________________________________________________________________
 *
 */
class BaseButton
{
protected:
    SDL_Rect buttonRect{};                 /**< Buttons 2D x pos, 2D y pos, width and height */
    std::string buttonLabel{};             /**< button label to display on rect e.g. NEW GAME */
    SDL_Color buttonColor{};               /**< button color in RGBA */
    const std::string buttonTexturePath{}; /**< button texture path */
    SDL_Texture *buttonTexture{};          /**< hold button texture set from path */
    TTF_Font *buttonFont{};                /**< button font for rendering button label text */
    SDL_Color buttonTextColor{};           /**< button text color in RGBA */
    int BaseButtonRectWidth{};             /**< value used to increase button dimensions on enlarging window resolution */
    int BaseButtonRectHeight{};            /**< value used to increase button dimensions on enlarging window resolution */
    static BaseButton *selectedButton;     /**< Static pointer for every BaseButton and subclass objects to track which is selected */
    bool isSelected{};                     /**< set button to isSelected for highlighting, pressing key inputs enter/A to traverse, and using as base navigation point */
    bool isClicked{};                      /**< flag to indicate button was clicked e.g. for Push Button SUBMIT to trigger submitting InputButton text */
    SDL_Renderer *renderer{};              /**< Dynamically set renderer anytime with set_renderer() for drawing button */

public:
    /**
     * @brief this is an abstract (base) class not meant for constructing
     * the subclasses that inherit from this are meant to be initialised into a vector of type
     * BaseButton in order to iterate through for various scenes GUI rendering/placement
     */
    BaseButton(int x,
               int y,
               int width,
               int height,
               std::string buttonLabel,
               Uint8 r, Uint8 g, Uint8 b, Uint8 a,
               const std::string buttonTexturePath,
               TTF_Font *buttonFont,
               Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText) : buttonRect({x, y, width, height}),
                                                                                  buttonLabel(buttonLabel),
                                                                                  buttonColor{r, g, b, a},
                                                                                  buttonTexturePath(buttonTexturePath),
                                                                                  buttonFont(buttonFont),
                                                                                  buttonTextColor{redText, greenText, blueText, alphaText}
    {
        BaseButtonRectWidth = width;
        BaseButtonRectHeight = height;
    }

    /**
     * @brief this is an abstract (base) class not meant for constructing
     * the subclasses that inherit from this are meant to be initialised into a vector of type
     * BaseButton in order to iterate through for various scenes GUI rendering/placement
     */
    virtual ~BaseButton()
    {
        std::cout << "Deconstructed: Button: " << buttonLabel << std::endl;
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
     * @brief when an SDL mouse handle
     *
     * SDL mouse state in mouse handle logic is passed to
     * SDL_Point mousePosition = {mouseX, mouseY}; which then on button
     * click will set the button selected which adds highlights in the render_button_rect
     * and selectes it for the base point for directional movement
     *
     * @param point accepts a SDL_Point mousePosition = {mouseX, mouseY}
     * @return if the point clicked matches the button will return true
     */
    bool is_clicked(SDL_Point &point)
    {
        set_selected();
        return SDL_PointInRect(&point, &buttonRect);
    }

    /**
     * @brief return button selected status
     *
     * return button selected status
     *
     * @return private member variable isSelected to signify button is selected
     */
    bool is_selected() const
    {
        return isSelected;
    }

    /**
     * @brief get buttons label which is the text written on it
     * can be replaced with set function for situations to display different text on click e.g. MUSIC ON || MUSIC OFF
     * @return the button label
     */
    std::string get_button_label() const
    {
        return buttonLabel;
    }

    /**
     * @brief set buttons label which is the text written on it
     * can be replaced with set function for situations to display different text on click e.g. MUSIC ON || MUSIC OFF
     * or when change language script
     * @param newButtonLabel a new label for button
     */
    void set_button_label(std::string newButtonLabel)
    {
        buttonLabel = newButtonLabel;
    }

    /**
     * @brief return button rect positions/dimensions
     *
     * return button rect positions/dimensions
     *
     * @return private member variable buttonRect for buttons SDL_Rect positions/dimensions
     */
    SDL_Rect get_rect() const
    {
        return buttonRect;
    }

    /**
     * @brief set button rect x position
     *
     * set button rect x position
     *
     * @param x int value is converted to button rect x position
     */
    void set_rect_x_pos(int x)
    {
        buttonRect.x = x;
    }

    /**
     * @brief set button rect y position
     *
     * set button rect y position
     *
     * @param y int value is converted to button rect y position
     */
    void set_rect_y_pos(int y)
    {
        buttonRect.y = y;
    }

    /**
     * @brief deselecting current button and select this button
     *
     * Used in handle input logic to select a new button and deselect
     * the old button
     *
     */
    void set_selected()
    {
        // Deselect the previous selected button
        if (selectedButton != nullptr)
        {
            selectedButton->isSelected = false;
        }
        isSelected = true;
        selectedButton = this;
    }

    /**
     * @brief get button clicked status
     *
     * @return if the button was clicked. Can be used further e.g. for SUBMIT button to send of InputButton text
     * to JSON elsewhere
     */
    bool get_clicked() const
    {
        return isClicked;
    }

    /**
     * @brief set button clicked status

     * After submitting text to reset all buttons variables you can call these functions
     * scene4inputPlayerNameButton.clear_text();
     * scene4inputPlayerNameButton.set_submitted(false);
     */
    void set_clicked(bool submitted)
    {
        isClicked = submitted;
    }

    /**
     * @brief set button button texture passed from constructor
     *
     * set button button texture passed from constructor
     * called anytime against the object, or you can itterate through a vector
     * of all for(button : allButtons) to set button->set_button_texture()
     *
     */
    void set_button_texture()
    {
        if (!buttonTexturePath.empty())
        {
            buttonTexture = IMG_LoadTexture(renderer, buttonTexturePath.c_str());
            if (!buttonTexture)
            {
                std::cout << "Error: Failed to load button image: " << buttonTexturePath << IMG_GetError() << std::endl;
            }
        }
    }

    /**
     * @brief render button font text to window
     *
     * Accepts a text string with styling parameters to write to window to show messages/label in GUI.
     * Uses SDL framework and traditionally loaded with TTF_Font *load_font() which returns a TTF_Font *font object
     *
     * EXAMPLE
     *
     * The below will draw a solid black "Hello World" message in the top left of window
     *
     * render_text("Hello World", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);
     *
     *
     * @param text message to render to the window
     * @param x x coordinate to draw the text to window
     * @param y y coordinate to draw the text to window
     * @param redText text rgb red value, use in conjunction with other rgb variable values
     * @param greenText text rgb green value, use in conjunction with other rgb variable values
     * @param blueText text rgb blue value, use in conjunction with other rgb variable values
     * @param alphaText the transparency. alpha value 255 - solid, value 1 = transparent, alpha value 0 breaks and becomes transparent again. Just use 1;
     */
    void render_button_text(const std::string &text, SDL_Rect buttonRect, SDL_Color textColor)
    {
        if (buttonFont)
        {
            SDL_Surface *textSurface = TTF_RenderUTF8_Blended(buttonFont, text.c_str(), textColor);

            if (textSurface)
            {
                int textWidth, textHeight;
                // Calculate textWidth and textHeight using TTF_SizeText
                TTF_SizeText(buttonFont, text.c_str(), &textWidth, &textHeight);

                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_FreeSurface(textSurface);

                if (textTexture)
                {
                    // Calculate the center position for the text
                    int x = buttonRect.x + (buttonRect.w - textWidth) / 2;
                    int y = buttonRect.y + (buttonRect.h - textHeight) / 2;

                    SDL_Rect textRect = {x, y, textWidth, textHeight};
                    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

                    SDL_DestroyTexture(textTexture);
                }
                else
                {
                    std::cout << "Error: Unable to create text texture" << TTF_GetError() << std::endl;
                }
            }
            else
            {
                std::cout << "Error: Unable to render text to surface" << TTF_GetError() << std::endl;
            }
        }
        else
        {
            std::cout << "Error: Button font is not initialized" << TTF_GetError() << std::endl;
        }
    }

    /**
     * @brief render button to window
     *
     * Depending on if the button has a passed texture to constructor, or if it's selected
     * will draw the button with the texture or the yellow selected border and also call
     * render_button_text() to draw text ontop of the button
     */
    virtual void render_button_rect()
    {
        // If no Texture, draw boxes
        if (buttonTexturePath.empty())
        {
            if (isSelected)
            {
                /*
                    Borders will appear as Grey/Yellow box if texture/Font is same color (Grey/Yellow) this is
                    because the order of events are

                    1. draw large Grey/Yellow (color depending on selected) box with pixels large e.g. 100
                    2. draw button with pixels smaller e.g. 98
                    3. Thus the large Grey/Yellow box has it's insides replaced with the texture/Button Text

                    thus this creates a border effect)
                */
                // Draw - YELLOW border
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // yellow
                SDL_Rect borderRect = {buttonRect.x - 2, buttonRect.y - 2, buttonRect.w + 4, buttonRect.h + 4};
                SDL_RenderFillRect(renderer, &borderRect);
            }
            else
            {
                // Draw - GREY border
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Grey
                SDL_Rect borderRect = {buttonRect.x - 2, buttonRect.y - 2, buttonRect.w + 4, buttonRect.h + 4};
                SDL_RenderFillRect(renderer, &borderRect);
            }
            // Draw button
            SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
            SDL_RenderFillRect(renderer, &buttonRect);
        }
        else
        {
            if (isSelected)
            {
                /*
                    Borders will appear as Grey/Yellow box if texture/Font is same color (Grey/Yellow) this is
                    because the order of events are

                    1. draw large Grey/Yellow (color depending on selected) box with pixels large e.g. 100
                    2. draw button with pixels smaller e.g. 98
                    3. Thus the large Grey/Yellow box has it's insides replaced with the texture/Button Text

                    thus this creates a border effect)
                */
                // Draw - YELLOW border
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // yellow
                SDL_Rect borderRect = {buttonRect.x - 2, buttonRect.y - 2, buttonRect.w + 4, buttonRect.h + 4};
                SDL_RenderFillRect(renderer, &borderRect);
            }
            // Draw Texture
            SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
        }
        // Draw text
        render_button_text(buttonLabel, buttonRect, buttonTextColor);
    }

    /**
     * @brief change button object font
     *
     * change button font size to a different font, you can pass the font
     * and size to control it e.g. japanese36, 36
     *
     * @param font pass the button font e.g. japanese36 loaded from a TTF_Font* font
     * @param size pass a font size matching the font
     */
    void set_font_size(TTF_Font *font, int size)
    {
        buttonFont = font;

        if (size == 24)
        {
            buttonRect.w = BaseButtonRectWidth;  // Stay at orinal constructed size
            buttonRect.h = BaseButtonRectHeight; // Stay at orinal constructed size
        }
        else if (size == 36)
        {
            buttonRect.w = BaseButtonRectWidth + 20; // from original size increase by 20
            buttonRect.h = BaseButtonRectHeight + 20;
        }
        else if (size == 48)
        {
            buttonRect.w = BaseButtonRectWidth + 40; // from original size increase by 40
            buttonRect.h = BaseButtonRectHeight + 40;
        }
    }

    /**
     * @brief find eulidean distance
     *
     * Find the difference between 2 points on an x, y graph
     * also called the cardassian plane.
     *
     * Used in further functions such as measuring distance for shortest path
     * between differnt buttons/GUI elements in a window to see which buttons
     * closer to move towards that button
     *
     * @param x1 button A x pos
     * @param y1 button A y bos
     * @param x2 button B x pos
     * @param y2 button B y pos
     */
    static double find_euclidean_distance(int x1, int y1, int x2, int y2)
    {
        double results = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        return results;
    }

    /**
     * @brief find nearest button
     *
     * uses find_euclidean_distance() to measure Euclidean distance used in finding closest
     * button to navigate to using directional navigation keys
     * E.g. if you press up directional arrow key on a keyboard or gamepad all the
     * buttons north in -y scale
     * will be calculated to find the nearest button.
     * then sets the closet button to isSelected = true
     *
     * @param sceneVector pass all the buttons in an vector in an window/scene to find the nearest
     * @param buttonDirection pass the button direction to travel up, down, left, right to closest in x-, x+, y-, y+
     */
    static void find_nearest_button(std::vector<BaseButton *> &sceneVector, const std::string buttonDirection)
    {
        float minDistance = std::numeric_limits<float>::max();
        int currentButtonXpos = 0;
        int currentButtonYpos = 0;

        BaseButton *nearestButton = nullptr;

        // Get the position of the selected button
        auto selectedButtonIt = std::find_if(sceneVector.begin(), sceneVector.end(), [](const BaseButton* button) {
            return button->is_selected();
        });

        if (selectedButtonIt != sceneVector.end())
        {
            const BaseButton* selectedButton = *selectedButtonIt;
            currentButtonXpos = selectedButton->get_rect().x + selectedButton->get_rect().w / 2;
            currentButtonYpos = selectedButton->get_rect().y + selectedButton->get_rect().h / 2;
        }

        // Prioritize moving in the specified direction
        for (BaseButton *button : sceneVector)
        {
            if (!button->is_selected())
            {
                if (buttonDirection == "UP" && button->get_rect().y < currentButtonYpos)
                {
                    float dist = find_euclidean_distance(currentButtonXpos, currentButtonYpos,
                                                         button->get_rect().x + button->get_rect().w / 2,
                                                         button->get_rect().y + button->get_rect().h / 2);

                    if (dist < minDistance)
                    {
                        minDistance = dist;
                        nearestButton = button;
                    }
                }
                else if (buttonDirection == "DOWN" && button->get_rect().y > currentButtonYpos)
                {
                    float dist = find_euclidean_distance(currentButtonXpos, currentButtonYpos,
                                                         button->get_rect().x + button->get_rect().w / 2,
                                                         button->get_rect().y + button->get_rect().h / 2);

                    if (dist < minDistance)
                    {
                        minDistance = dist;
                        nearestButton = button;
                    }
                }
                else if (buttonDirection == "LEFT" && button->get_rect().x < currentButtonXpos)
                {
                    float dist = find_euclidean_distance(currentButtonXpos, currentButtonYpos,
                                                         button->get_rect().x + button->get_rect().w / 2,
                                                         button->get_rect().y + button->get_rect().h / 2);

                    if (dist < minDistance)
                    {
                        minDistance = dist;
                        nearestButton = button;
                    }
                }
                else if (buttonDirection == "RIGHT" && button->get_rect().x > currentButtonXpos)
                {
                    float dist = find_euclidean_distance(currentButtonXpos, currentButtonYpos,
                                                         button->get_rect().x + button->get_rect().w / 2,
                                                         button->get_rect().y + button->get_rect().h / 2);

                    if (dist < minDistance)
                    {
                        minDistance = dist;
                        nearestButton = button;
                    }
                }
            }
        }

        // Select the nearest button
        if (nearestButton != nullptr)
        {
            nearestButton->set_selected();
        }
    }
    
};
