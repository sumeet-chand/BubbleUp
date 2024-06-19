/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

#pragma once

#include "globals.hpp"
#include "WebserverClient.hpp"
/**
 * @brief When new controller is detected this function associates with a player entity  
 * When a new controller is connected (SDL_CONTROLLERDEVICEADDED event), the system checks if the controller was
 * previously connected (by matching SDL_JoystickID).
 * If it was previously connected, the controller is re-assigned to the same player entity.
 * If it is a new controller, it is assigned to the first available player entity without a controller.
 */
void handle_controller_added(SDL_Event event);
/**
 * @brief When connected removed this function disassociates from a player entity  
 * When a controller is disconnected (SDL_CONTROLLERDEVICEREMOVED event), the system identifies which player
 * entity was using that controller (by matching SDL_JoystickID) and updates the player entity to reflect the disconnection.
 */
void handle_controller_removed(SDL_Event event);
/**
 * @brief Main menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_1(const int &mouseX, const int &mouseY);
/**
 * @brief Settings mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
 * @param gamePaused unpause game if !isMultiplayerGame when clicking return to game, restarting update() and draw()
*/
void handle_mouse_scene_2(const int &mouseX, const int &mouseY, bool gamePaused);
/**
 * @brief Unlockables/Bonus menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_3(const int &mouseX, const int &mouseY);
/**
 * @brief Scoreboard menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_4(const int &mouseX, const int &mouseY);
/**
 * @brief Help Guide menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_5(const int &mouseX, const int &mouseY);
/**
 * @brief Achievements menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_6(const int &mouseX, const int &mouseY);
/**
 * @brief Check for Updates menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_7(const int &mouseX, const int &mouseY);
/**
 * @brief Online login menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_8(const int &mouseX, const int &mouseY);
/**
 * @brief Create account menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_9(const int &mouseX, const int &mouseY);
/**
 * @brief Display policies menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_10(const int &mouseX, const int &mouseY);
/**
 * @brief Multiplayer lobby menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_11(const int &mouseX, const int &mouseY);
/**
 * @brief Keybindings menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_12(const int &mouseX, const int &mouseY);
/**
 * @brief Create game menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_13(const int &mouseX, const int &mouseY);
/**
 * @brief Credits menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_14(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_15(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_16(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_17(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_18(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_19(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_20(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_21(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_22(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_23(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_24(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_25(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_26(const int &mouseX, const int &mouseY);
/**
 * @brief Level editor menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_27(const int &mouseX, const int &mouseY);
/**
 * @brief Cutscene menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_28(const int &mouseX, const int &mouseY);
/**
 * @brief Cutscene menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_29(const int &mouseX, const int &mouseY);
/**
 * @brief Cutscene menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_30(const int &mouseX, const int &mouseY);
/**
 * @brief Cutscene menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch
*/
void handle_mouse_scene_31(const int &mouseX, const int &mouseY);
/**
 * @brief Game HUD menu on mouse/touch click determine which button was clicked
 * 
 * @param mouseX Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse click event or static_cast<int>(event.tfinger.x * SCREEN_WIDTH); for touch
 * @param mouseY Taken from SDL_GetMouseState(&mouseX, &mouseY) for mouse clickevent or  static_cast<int>(event.tfinger.y * SCREEN_HEIGHT); for touch'
*/
void handle_mouse_scene_gameplay(const int &mouseX, const int &mouseY);

/**
 * @brief Main menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_1(const SDL_Event &event);
/**
 * @brief Settings menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
 * @param gamePaused unpause game if !isMultiplayerGame when clicking return to game, restarting update() and draw()
*/
void handle_keyboard_scene_2(const SDL_Event &event, bool gamePaused);
/**
 * @brief Unlockables/Bonus menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_3(const SDL_Event &event);
/**
 * @brief Scoreboard menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_4(const SDL_Event &event);
/**
 * @brief Help guide menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_5(const SDL_Event &event);
/**
 * @brief Achievements menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_6(const SDL_Event &event);
/**
 * @brief Check for updates menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_7(const SDL_Event &event);
/**
 * @brief Online login menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_8(const SDL_Event &event);
/**
 * @brief Create account menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_9(const SDL_Event &event);
/**
 * @brief Display policies menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_10(const SDL_Event &event);
/**
 * @brief Multiplayer lobby menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_11(const SDL_Event &event);
/**
 * @brief Keybindings menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_12(const SDL_Event &event);
/**
 * @brief Create game menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_13(const SDL_Event &event);
/**
 * @brief Credits menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_14(const SDL_Event &event);
/**
 * @brief Level editor menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_15(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_16(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_17(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_18(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_19(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_20(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_21(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_22(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_23(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_24(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_25(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_26(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_27(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_28(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_29(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_30(const SDL_Event &event);
/**
 * @brief Cutscene menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
*/
void handle_keyboard_scene_31(const SDL_Event &event);
/**
 * @brief Game HUD menu on keyboard click determine which button was clicked
 * 
 * @param event the SDL keyboard click event is passed to see which individual button was clicked
 * @param gamePaused the ESC key in gameplay pauses game if not in multiplayer which stops timer, and stops update() and draw()
 * reset in settings button to return to game
*/
void handle_keyboard_scene_gameplay(const SDL_Event &event, bool gamePaused);

/**
 * @brief Main menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_1(const int &button);
/**
 * @brief Settings menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
 * @param gamePaused unpause game if !isMultiplayerGame when clicking return to game, restarting update() and draw()
*/
void handle_gamepad_scene_2(const int &button, bool gamePaused);
/**
 * @brief Unlockables/Bonus menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_3(const int &button);
/**
 * @brief Scoreboard menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_4(const int &button);
/**
 * @brief Scoreboard menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_5(const int &button);
/**
 * @brief Achievements menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_6(const int &button);
/**
 * @brief Check for updates menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_7(const int &button);
/**
 * @brief Online login menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_8(const int &button);
/**
 * @brief Create account menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_9(const int &button);
/**
 * @brief Display policies menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_10(const int &button);
/**
 * @brief Multiplayer lobby menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_11(const int &button);
/**
 * @brief Keybindings menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_12(const int &button);
/**
 * @brief Create game menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_13(const int &button);
/**
 * @brief Credits menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_14(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_15(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_16(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_17(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_18(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_19(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_20(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_21(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_22(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_23(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_24(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_25(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_26(const int &button);
/**
 * @brief Level editor menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_27(const int &button);
/**
 * @brief Cutscene menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_28(const int &button);
/**
 * @brief Cutscene menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_29(const int &button);
/**
 * @brief Cutscene menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_30(const int &button);
/**
 * @brief Cutscene menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
*/
void handle_gamepad_scene_31(const int &button);
/**
 * @brief Game HUD menu on gamepad/controller click determine which button was clicked
 * 
 * @param button when a gamepad button is pressed the object is passed to this function to see what was clicked
 * @param gamePaused the ESC key in gameplay pauses game if not in multiplayer which stops timer, and stops update() and draw()
 * reset in settings button to return to game
*/
void handle_gamepad_scene_gameplay(const int &button, bool gamePaused);
