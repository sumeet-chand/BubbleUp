/*
    Author: Sumeet Singh
    Dated: 28/05/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

#pragma once

#include <SDL2/SDL.h>
#include "globals.hpp"


/**
 * @brief Add buttons to the drop down buttons
 */
void add_buttons_to_dropdown_buttons();
/**
 * @brief Initialise button objects into scene vectors for handle() commands
 *
 * BaseButton.hpp has declarations for multiple button classes which are defined in global variables.
 * This function groups them in scenes vector also defined in global variables then adds the relevant
 * buttons to that scene. Will be used later in handle() input functions for clicking/selecting.
 *
 */
void load_buttons_to_scene_vectors();
/**
 * @brief Initialise all scene vectors filled with button objects to a complete allButtons vector
 *
 * BaseButton.hpp objects pushed in individual scene vectors grouped by scene are now pushed
 * into a complete allButtons vector defined in global variables. This is used to itterate
 * through for changing all GUI elements e.g. change button font to different language/font size etc.,
 *
 */
void load_buttons_to_all_buttons_vector(std::vector<BaseButton *> &allButtons);
/**
 * @brief initialise button renderer
 * to call once before buttons are drawn, and called during anytime e.g. button presses to update renderer to also
 * update buttons e.g. when you click a button to enable/disable Vsync and thus recreate a renderer in a graphics/game/simulation software
 * then the buttons will need to draw their textures and fonts onto the new renderer
 * @param renderer the new renderer
 * */
void initialise_button_renderer(SDL_Renderer *renderer);
/**
 * @brief Set all buttons textures
 *
 * BaseButton.hpp declares function for setting the texture passed in the global variable constructor
 * which will then be used in draws() to draw the button to GUI
 */
void initialise_button_textures(std::vector<BaseButton *> &allButtons);
/**
 * @brief Set all buttons fonts
 *
 * BaseButton.hpp declares function for setting the fonts passed in the global variable constructor
 * which will then be used in draws() to draw the button text to GUI
 */
void initialise_button_fonts(std::vector<BaseButton *> &allButtons);

/**
 * @brief SDL function to load texture
 *
 * uses SDL_Image to load textures from c style filepath
 *
 * @param textureFilePath path of the asset texture to load
 * @return a SDL_Texture *texture object to then load in a renderer
 *
 */
SDL_Texture *load_texture(const std::string &textureFilePath);
/**
 * @brief SDL function to load sound
 *
 * uses SDL_Mixer to load sounds from c style filepath
 *
 * @param sfxFilePath path of the asset texture to load
 * @return a Mix_Chunk *sound object to then play in audio channel
 *
 */
Mix_Chunk *load_sound(const std::string sfxFilePath);
/**
 * @brief SDL function to load font
 *
 * uses SDL_ttf to load fonts from c style filepath
 *
 * @param sfxFilePath path of the asset texture to load
 * @return a TTF_Font *font object to then call in render_text() to draw text to GUI
 *
 */
TTF_Font *load_font(const std::string &fontFilePath, const int &fontSize);
/**
 * @brief SDL function to initialise controller support
 *
 * uses SDL to load find available controllers connected and initialise them for gamepad input
 *
 * @param controllers dynamically changing vector of controller
 */
void load_controllers();
/**
 * @brief SDL function to initialise textures
 *
 * uses SDL_texture to load a bunch of filepaths into load_texture() to then render to GUI
 * at a later stage
 *
 *
 */
void load_textures();
/**
 * @brief SDL function to initialise sound files
 *
 * uses SDL_mixer to load a bunch of filepaths into load_sound() to then render to play
 * audio in softwarre on trigger
 *
 *
 */
void load_sounds();
/**
 * @brief SDL function to initialise music files
 *
 * uses SDL_mixer to accept parameter of a audio file sound path to play that music
 *
 * @param songTitle accepts a string filepath of music to play
 */
void load_music(const std::string &songTitle);
/**
 * @brief SDL function to initialise fonts
 *
 * uses SDL_ttf to initialise fonts into load_font() to render to GUi at a later stage
 */
void load_fonts();
/**
 * @brief Change font language
 *
 * insert a language in string text to load a font that supports that language
 *
 * @param language font to rener
 */
void set_font(const std::string &language);
/**
 * @brief render font text to window
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
 * @param alpha the transparency. alpha value 255 - solid, value 1 = transparent, alpha value 0 breaks and becomes transparent again. Just use 1;
 * @param font the passed SDL_ttf font object
 */
void render_text(const std::string &text, int x, int y, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText, TTF_Font *font);
/**
 * @brief SDL and Asset initialisations
 *
 * Contains the SDL Library initialisations as well as various functions for starting the
 * loading of every asset e.g.
 * load_fonts();
 * set_font(language);
 * load_controllers();
 * load_textures();
 * load_sounds();
 * load_buttons_to_scene_vectors();
 * load_buttons_to_all_buttons_vector(allButtons);
 * initialise_button_renderer(renderer);
 * initialise_button_textures(allButtons);
 * initialise_button_fonts(allButtons);
 * load_music(level1song);
 */
void start_SDL();
/**
 * @brief SDL event loop initialisation
 *
 * Calls the functions to run in an SDL event loop until manually closed by user
 */
void run_SDL();
/**
 * @brief SDL exit initialisation
 *
 * Calls the functions to destroy all SDL Objects run on program exit
 */
void exit_SDL();

/**
 * @brief SDL Event loop handle input functions
 *
 * in SDL event loop run_SDL() calls this handle() which contains functions for all the different key inputs
 * by mouse/touch, keyboard, and gamepad to handle key input for different scenes.
 *
 * EXAMPLE
 *
 * When software starts the scene 1 buttons are drawn, and the input for them is handled
 * by the relevant keyboard/mouse/gamepad handles e.g. below;
 *
 *         if (event.type == SDL_KEYDOWN) {
 *           switch (scene) {
 *           case 1:
 *               handle_keyboard_scene_1(event);
 *               break;
 */
void handle(bool gamePaused);
/**
 * @brief SDL Event loop update logic functions
 *
 * In SDL event loop run_SDL() calls update() which contains functions for all the different
 * logic to run for every scene e.g. on scene 29 game start play a video cutscene or
 * on software startup scene 1, play a developer logo.
 */
void update(int &soundVolume, int &musicVolume, int &scene, bool gamePaused);
/**
 * @brief SDL Event loop update logic functions
 *
 * In SDL event loop run_SDL() calls update() which contains functions for all the different
 * elements to draw to window e.g. Entities, Buttons, Text, Animations Images, etc.,
 * text comes from render_text()
 * entities come from your Entity.hpp
 * Buttons constructed from your BaseButton.hpp
 * Images loaded from load_texture()
 * You can use draw SDL_Rect's, or anything to renderer to appear here
 */
void draw(SDL_Renderer *&renderer, int &scene, SDL_Texture *&background1Texture, float fps, bool gamePaused);