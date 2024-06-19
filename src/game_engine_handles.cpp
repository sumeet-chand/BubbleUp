/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Definition file
    License: MIT License


    _________________________________________________________________________________________________

                                SDL HANDLE FUNCTIONS DEFINITIONS
    _________________________________________________________________________________________________


    DESCRIPTION

    Handles for keyboard input for SDL framework, Has Mouse, Keyboard and Gamepad on button clicks
    defined here called from handle() in core game logic elsewhere.

    Declarations: ./headers/game_enginehandles.hpp
    Definitions: ./src/game_enginehandles.cpp


    EXAMPLE

    1. In SDL handle() game loop call appropriate function for whichever scene.

    void handle()
    {
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (scene == 1) {
                handle_keyboard_scene_1();
            }
        }
        else if (event.type == SDL_KEYUP)
        {
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_FINGERDOWN)
        {
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
        }
        else if (event.type == SDL_CONTROLLERBUTTONDOWN)
        {
        }
        else if (event.type == SDL_CONTROLLERBUTTONUP)
        {

        }
        else if (event.type == SDL_TEXTINPUT)
        {
        }
    }
    }

*/

#include "../headers/game_engine_handles.hpp"
#include "../headers/SaveLoadData.hpp"

// Forward declarations
void setup_reset_game();
void toggle_countdown();
void recreate_renderer(); /** for user vsync toggle button */

void handle_controller_added(SDL_Event event)
{

    SDL_GameController *controller = SDL_GameControllerOpen(event.cdevice.which);
    if (controller)
    {
        SDL_JoystickID instance_id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
        bool reconnected = false;

        // Check if the controller was previously connected
        for (Entity *e : entities)
        {
            if (Player *player = dynamic_cast<Player *>(e))
            {
                if (player->get_controller_instance_id() == instance_id)
                {
                    player->set_controller(controller);
                    reconnected = true;
                    std::cout << "Controller reconnected for player " << player->get_player_id() << "." << std::endl;
                    break;
                }
            }
        }

        // If not reconnected, treat as new
        if (!reconnected)
        {
            for (Entity *e : entities)
            {
                if (Player *player = dynamic_cast<Player *>(e))
                {
                    if (player->get_controller() == nullptr)
                    {
                        player->set_controller(controller);
                        player->set_controller_instance_id(instance_id);
                        std::cout << "New controller added for player " << player->get_player_id() << "." << std::endl;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        logger.log_critical("Could not open controller: " + std::string(SDL_GetError()));
    }
}
void handle_controller_removed(SDL_Event event)
{
    SDL_JoystickID instance_id = event.cdevice.which;
    for (Entity *e : entities)
    {
        if (Player *player = dynamic_cast<Player *>(e))
        {
            if (player->get_controller_instance_id() == instance_id)
            {
                SDL_GameControllerClose(player->get_controller());
                player->set_controller(nullptr);
                std::cout << "Controller removed for player " << player->get_player_id() << std::endl;
                break;
            }
        }
    }
}

void handle_mouse_scene_1(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene1newGameButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: New Game" << std::endl;
        setup_reset_game();
        scene = 102;
    }
    else if (scene1settingsButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Settings" << std::endl;
        scene = 2;
    }
    else if (scene1unlockablesButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Unlockables" << std::endl;
        scene = 3;
    }
    else if (scene1scoreButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Score" << std::endl;
        scene = 4;
    }
    else if (scene1helpButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Help" << std::endl;
        scene = 5;
    }
    else if (scene1achievementsButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Achievements" << std::endl;
        scene = 6;
    }
    else if (scene1multiplayerButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Multiplayer" << std::endl;
        updateApp.clickedCheckForUpdates = true;
        scene = 7;
    }
    else if (scene1levelEditorButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Level Editor" << std::endl;
        scene = 15;
    }
    else if (scene1modStoreButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Mod Store" << std::endl;
        scene = 22;
    }
    else if (scene1quitGameButton.is_clicked(mousePosition))
    {
        std::cout << "You pressed: Quit Game" << std::endl;
        quitEventLoop = true;
    }
}
void handle_mouse_scene_2(const int &mouseX, const int &mouseY, bool gamePaused)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene2ChangeFontButton.is_clicked(mousePosition))
    {
        if (defaultFont == font24)
        {
            std::cout << "You pressed: Changed to Font 36" << std::endl;
            defaultFont = font36;
            for (BaseButton *b : allButtons)
            {
                b->set_font_size(defaultFont, 36);
            }
        }
        else if (defaultFont == font36)
        {
            std::cout << "You pressed: Changed to Font 48" << std::endl;
            defaultFont = font48;
            for (BaseButton *b : allButtons)
            {
                b->set_font_size(defaultFont, 48);
            }
        }
        else if (defaultFont == font48)
        {
            std::cout << "You pressed: Changed to Font 24" << std::endl;
            defaultFont = font24;
            for (BaseButton *b : allButtons)
            {
                b->set_font_size(defaultFont, 24);
            }
        }
    }
    else if (scene2ChangeLanguageButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Change Language" << std::endl;
        if (language == "English")
        {
            language = "日本語";
            std::cout << "Language now set to: " << language << std::endl;
        }
        else
        {
            language = "English";
            std::cout << "Language now set to: " << language << std::endl;
        }
    }
    else if (scene2changeKeymappingButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Keymapping" << std::endl;
        scene = 12;
    }
    else if (scene2displayOnScreenKeysButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Display On Screen Keys" << std::endl;
        displayOnScreenKeys = !displayOnScreenKeys;
    }
    else if (scene2fullscreenToggleButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: FUllscreen toggle" << std::endl;
        int borderFlag = SDL_GetWindowFlags(window);
        bool isFullscreen = (borderFlag & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
        if (isFullscreen)
        {
            SDL_SetWindowFullscreen(window, 0);
        }
        else
        {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }
    else if (scene2enableVsyncButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Vsync toggle" << std::endl;
        vsyncEnabled = !vsyncEnabled;
        recreate_renderer();
    }
    else if (scene2toggleFPSButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: FPS toggle" << std::endl;
        displayFPS = !displayFPS;
    }
    else if (scene2resolutionsDropdownButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Resolutions drop down" << std::endl;
        scene2resolutionsDropdownButton.set_clicked(true);
    }
    else if (scene2resolutionsDropdown1366x768Button.is_clicked(mousePosition))
    {
        std::cout << " You selected: 1366 x 768 resolution" << std::endl;
        SDL_SetWindowSize(window, 1366, 768);
    }
    else if (scene2resolutionsDropdown800x640Button.is_clicked(mousePosition))
    {
        std::cout << " You selected: 800 x 640 resolution" << std::endl;
        SDL_SetWindowSize(window, 800, 640);
    }
    else if (scene2toggleSoundButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Sound toggle" << std::endl;
    }
    else if (scene2toggleMusicButton.is_clicked(mousePosition))
    {
        logger.log_critical("You selected: toggle Music");
        musicPlaying = !musicPlaying;
        if (musicPlaying)
        {
            Mix_PauseMusic();
        }
        else
        {
            Mix_ResumeMusic();
        }
        logger.log_critical("Music is: " + std::string(musicPlaying ? "true" : "false"));
    }
    else if (scene2SFXSliderButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Sound Slider" << std::endl;
    }
    else if (scene2VolumeSliderButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Volume Slider" << std::endl;
    }
    else if (scene2scrollSpeedSliderButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Scroll speed Slider" << std::endl;
    }
    else if (scene2returnToTitleButton.is_clicked(mousePosition))
    {
        scene = 1;
    }
    else if (scene2returnToGameButton.is_clicked(mousePosition))
    {
        if (gameStarted)
        {
            if (!isMultiplayerGame)
            {
                startTimer = true;
                toggle_countdown();
                gamePaused = false;
            }
            scene = lastScene;
        }
        else
        {
            std::cout << "Warning: Game hasn't started" << std::endl;
        }
    }
    else if (scene2saveSettingsButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Save settings" << std::endl;
        SaveLoadData::save_settings(saveFileName, language);
    }
    else if (scene2ResetToDefaultSettingsButton.is_clicked(mousePosition))
    {
        std::cout << " You selected: Reset settings" << std::endl;
        musicPlaying = true;
        language = "English";
        for (BaseButton *button : allButtons)
        {
            button->set_font_size(defaultFont, 36);
        }
    }
}
void handle_mouse_scene_3(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene3returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene3creditsButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Credits" << std::endl;
        scene = 14;
    }
    else if (scene3sandboxButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Sandbox" << std::endl;
        scene = 100;
    }
    else if (scene3soundtrackButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Level Editor" << std::endl;
        scene = 15;
    }
}
void handle_mouse_scene_4(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene4returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene4submitNameButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Submit Player Name Field" << std::endl;
        if (!scene4inputPlayerNameButton.get_text().empty())
        {
            scene4inputPlayerNameButton.set_clicked(true);
            std::cout << "Success: Submitted Player Name" << std::endl;
        }
        else
        {
            std::cout << "Error: Please enter player name" << std::endl;
        }
    }
    else if (scene4inputPlayerNameButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Input Player Name Field" << std::endl;
    }
}
void handle_mouse_scene_5(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene5returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene5backButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Back" << std::endl;
        scrollYpos += scrollSpeed;
    }
    else if (scene5forwardButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Forward" << std::endl;
        scrollYpos -= scrollSpeed;
    }
}
void handle_mouse_scene_6(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene6returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_7(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene7returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene7updateButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Update" << std::endl;
        updateApp.start_update();
    }
    else if (scene7cancelButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Cancel" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_8(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene8returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene8loginButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Login" << std::endl;
    }
    else if (scene8registerButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Register" << std::endl;
        scene = 10;
    }
    else if (scene8inputemailButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Input Email" << std::endl;
    }
    else if (scene8inputpasswordButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Input Password" << std::endl;
    }
}
void handle_mouse_scene_9(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene9returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene9submitButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Submit" << std::endl;
        if (!scene9inputusernameButton.get_text().empty() &&
            !scene9inputemailButton.get_text().empty() &&
            !scene9inputpasswordNameButton.get_text().empty())
        {

            webserverClientContext.create_account(scene9inputusernameButton.get_text(), scene9inputemailButton.get_text(), scene9inputpasswordNameButton.get_text());
        }
    }
    else if (scene9inputusernameButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Input Username" << std::endl;
    }
    else if (scene9inputemailButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Input Email" << std::endl;
    }
    else if (scene9inputpasswordNameButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Input Password" << std::endl;
    }
}
void handle_mouse_scene_10(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene10returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene10acceptPrivacyPolicyButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Accept Privacy Policy" << std::endl;
        scene10acceptPrivacyPolicyButton.set_clicked(true);
    }
    else if (scene10denyPrivacyPolicyButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Deny Privacy Policy" << std::endl;
        scene = 8;
    }
    else if (scene10acceptTermsPolicyButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Accept Terms Policy" << std::endl;
        scene10acceptTermsPolicyButton.set_clicked(true);
    }
    else if (scene10denyTermsPolicyButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Deny Terms Policy" << std::endl;
        scene = 8;
    }
}
void handle_mouse_scene_11(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene11returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene11createGameButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Create Game" << std::endl;
    }
    else if (scene11joinGameButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Join Game" << std::endl;
    }
    else if (scene11refreshGamesButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Refresh Game" << std::endl;
    }
    else if (scene11sendMessageButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Send Message" << std::endl;
    }
    else if (scene11addFriendButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Add friend" << std::endl;
    }
    else if (scene11refreshFriendsButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Refresh Friends" << std::endl;
    }
}
void handle_mouse_scene_12(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene12returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene12acceptButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Accept" << std::endl;
    }
    else if (scene12resetButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Reset" << std::endl;
    }
}
void handle_mouse_scene_13(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene13cancelButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Cancel" << std::endl;
        scene = 12;
    }
    else if (scene13createButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Create" << std::endl;
    }
}
void handle_mouse_scene_14(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene14returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_15(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene15FileDropdownButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: File" << std::endl;
        scene15FileDropdownButton.render_buttons_from_dropdown_list(renderer);
    }
    else if (scene15returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_16(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene16returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_17(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene17returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_18(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene18returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_19(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene19returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_20(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene20returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_21(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene21returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_22(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene22returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_23(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene23returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_24(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene24returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_25(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene25returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_26(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene26returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_27(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene27returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
    else if (scene27backButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Back" << std::endl;
    }
    else if (scene27nextButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Next" << std::endl;
    }
    else if (scene27acceptButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Accept" << std::endl;
    }
    else if (scene27denyButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Deny" << std::endl;
    }
}
void handle_mouse_scene_28(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene28returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Skip" << std::endl;
        scene = 101; // Go to Tutorial
    }
}
void handle_mouse_scene_29(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene29returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_30(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene30returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_31(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    if (scene31returnToTitleButton.is_clicked(mousePosition))
    {
        std::cout << "You clicked: Return to title" << std::endl;
        scene = 1;
    }
}
void handle_mouse_scene_gameplay(const int &mouseX, const int &mouseY)
{
    SDL_Point mousePosition = {mouseX, mouseY};
    for (Entity *e : entities)
    {
        if (Player *p = dynamic_cast<Player *>(e))
        {
            if (p->get_player_id() == clientPlayerID)
            {
                if (sceneGameplayMenuButton.is_clicked(mousePosition))
                {
                    std::cout << "You clicked: Menu" << std::endl;
                    startTimer = false;
                    lastScene = scene;
                    scene = 2;
                }
                else if (sceneGameplayUpButton.is_clicked(mousePosition))
                {
                    if (isMultiplayerGame)
                    {
                        webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity(), p->get_yVelocity() - p->get_acceleration(), "UP", webserverHostContext);
                    }
                    else
                    {
                        p->set_velocity(p->get_xVelocity(), p->get_yVelocity() - p->get_acceleration());
                        if (p->get_yVelocity() < -2.0f)
                        {
                            p->set_velocity(p->get_xVelocity(), -2.0f);
                        }
                    }
                }
                else if (sceneGameplayDownButton.is_clicked(mousePosition))
                {
                    if (isMultiplayerGame)
                    {
                        webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity(), p->get_yVelocity() + p->get_acceleration(), "DOWN", webserverHostContext);
                    }
                    else
                    {
                        p->set_velocity(p->get_xVelocity(), p->get_yVelocity() + p->get_acceleration());
                        if (p->get_yVelocity() > 2.0f)
                        {
                            p->set_velocity(p->get_xVelocity(), 2.0f);
                        }
                    }
                }
                else if (sceneGameplayLeftButton.is_clicked(mousePosition))
                {
                    if (isMultiplayerGame)
                    {
                        webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity() - p->get_acceleration(), p->get_yVelocity(), "LEFT", webserverHostContext);
                    }
                    else
                    {
                        p->set_velocity(p->get_xVelocity() - p->get_acceleration(), p->get_yVelocity());
                        if (p->get_xVelocity() < -2.0f)
                        {
                            p->set_velocity(-2.0f, p->get_yVelocity());
                        }
                    }
                }
                else if (sceneGameplayRightButton.is_clicked(mousePosition))
                {
                    if (isMultiplayerGame)
                    {
                        webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity() + p->get_acceleration(), p->get_yVelocity(), "RIGHT", webserverHostContext);
                    }
                    else
                    {
                        p->set_velocity(p->get_xVelocity() + p->get_acceleration(), p->get_yVelocity());
                        if (p->get_xVelocity() > 2.0f)
                        {
                            p->set_velocity(2.0f, p->get_yVelocity());
                        }
                    }
                }
                else if (sceneGameplayUseButton.is_clicked(mousePosition))
                {
                    std::cout << "You clicked: USE" << std::endl;
                }
            }
        }
    }
}

void handle_keyboard_scene_1(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            quitEventLoop = true;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene1buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene1buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene1buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene1buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene1newGameButton.is_selected())
            {
                std::cout << "You pressed: New Game" << std::endl;
                setup_reset_game();
                scene = 102;
            }
            else if (scene1settingsButton.is_selected())
            {
                std::cout << "You pressed: Settings" << std::endl;
                scene = 2;
            }
            else if (scene1unlockablesButton.is_selected())
            {
                std::cout << "You pressed: Unlockables" << std::endl;
                scene = 3;
            }
            else if (scene1scoreButton.is_selected())
            {
                std::cout << "You pressed: Score" << std::endl;
                scene = 4;
            }
            else if (scene1helpButton.is_selected())
            {
                std::cout << "You pressed: Help" << std::endl;
                scene = 5;
            }
            else if (scene1achievementsButton.is_selected())
            {
                std::cout << "You pressed: Achievements" << std::endl;
                scene = 6;
            }
            else if (scene1multiplayerButton.is_selected())
            {
                std::cout << "You pressed: Multiplayer" << std::endl;
                scene = 7;
            }
            else if (scene1levelEditorButton.is_selected())
            {
                std::cout << "You pressed: Level Editor" << std::endl;
                scene = 15;
            }
            else if (scene1modStoreButton.is_selected())
            {
                std::cout << "You pressed: Mod Store" << std::endl;
                scene = 22;
            }
            else if (scene1quitGameButton.is_selected())
            {
                std::cout << "You pressed: Quit Game" << std::endl;
                quitEventLoop = true;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_2(const SDL_Event &event, bool gamePaused)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene2buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene2buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            if (scene2SFXSliderButton.is_selected())
            {
                // soundVolume = std::max<int>(0, soundVolume - 1);
                soundVolume = soundVolume - 1;
                if (soundVolume <= 0)
                {
                    soundVolume = 0;
                }
            }
            else if (scene2VolumeSliderButton.is_selected())
            {
                // musicVolume = std::max<int>(0, musicVolume - 1);
                musicVolume = musicVolume - 1;
                if (musicVolume <= 0)
                {
                    musicVolume = 0;
                }
            }
            else if (scene2scrollSpeedSliderButton.is_selected())
            {
                // scrollSpeed = std::min<int>(0, scrollSpeed - 1);
                scrollSpeed = scrollSpeed - 1;
                if (scrollSpeed <= 0)
                {
                    scrollSpeed = 0;
                }
            }
            else
            {
                BaseButton::find_nearest_button(scene2buttons, buttonDirection);
            }
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            if (scene2SFXSliderButton.is_selected())
            {
                // soundVolume = std::min<int>(100, soundVolume + 1);
                soundVolume = soundVolume + 1;
                if (soundVolume >= 100)
                {
                    soundVolume = 100;
                }
            }
            else if (scene2VolumeSliderButton.is_selected())
            {
                // musicVolume = std::min<int>(100, musicVolume + 1);
                musicVolume = musicVolume + 1;
                if (musicVolume >= 100)
                {
                    musicVolume = 100;
                }
            }
            else if (scene2scrollSpeedSliderButton.is_selected())
            {
                // scrollSpeed = std::min<int>(100, scrollSpeed + 1);
                scrollSpeed = scrollSpeed + 1;
                if (scrollSpeed >= 100)
                {
                    scrollSpeed = 100;
                }
            }
            else
            {
                BaseButton::find_nearest_button(scene2buttons, buttonDirection);
            }
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene2ChangeFontButton.is_selected())
            {
                if (defaultFont == font24)
                {
                    std::cout << "You pressed: Changed to Font 36" << std::endl;
                    defaultFont = font36;
                    for (BaseButton *b : allButtons)
                    {
                        b->set_font_size(defaultFont, 36);
                    }
                }
                else if (defaultFont == font36)
                {
                    std::cout << "You pressed: Changed to Font 48" << std::endl;
                    defaultFont = font48;
                    for (BaseButton *b : allButtons)
                    {
                        b->set_font_size(defaultFont, 48);
                    }
                }
                else if (defaultFont == font48)
                {
                    std::cout << "You pressed: Changed to Font 24" << std::endl;
                    defaultFont = font24;
                    for (BaseButton *b : allButtons)
                    {
                        b->set_font_size(defaultFont, 24);
                    }
                }
            }
            else if (scene2ChangeLanguageButton.is_selected())
            {
                std::cout << " You selected: Change Language" << std::endl;
                if (language == "English")
                {
                    language = "日本語";
                    std::cout << "Language now set to: " << language << std::endl;
                }
                else
                {
                    language = "English";
                    std::cout << "Language now set to: " << language << std::endl;
                }
            }
            else if (scene2changeKeymappingButton.is_selected())
            {
                std::cout << " You selected: Keymapping" << std::endl;
                scene = 12;
            }
            else if (scene2displayOnScreenKeysButton.is_selected())
            {
                std::cout << " You selected: Display On Screen Keys" << std::endl;
                displayOnScreenKeys = !displayOnScreenKeys;
            }
            else if (scene2fullscreenToggleButton.is_selected())
            {
                std::cout << " You selected: FUllscreen toggle" << std::endl;
                int borderFlag = SDL_GetWindowFlags(window);
                bool isFullscreen = (borderFlag & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
                if (isFullscreen)
                {
                    SDL_SetWindowFullscreen(window, 0);
                }
                else
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
            }
            else if (scene2enableVsyncButton.is_selected())
            {
                std::cout << " You selected: Vsync toggle" << std::endl;
                vsyncEnabled = !vsyncEnabled;
                recreate_renderer();
            }
            else if (scene2toggleFPSButton.is_selected())
            {
                std::cout << " You selected: FPS toggle" << std::endl;
                displayFPS = !displayFPS;
            }
            else if (scene2resolutionsDropdownButton.is_selected())
            {
                std::cout << " You selected: Resolutions drop down" << std::endl;
                scene2resolutionsDropdownButton.set_clicked(true);
            }
            else if (scene2toggleSoundButton.is_selected())
            {
                std::cout << " You selected: Sound toggle" << std::endl;
            }
            else if (scene2toggleMusicButton.is_selected())
            {
                logger.log_critical("You selected: toggle Music");
                musicPlaying = !musicPlaying;
                if (musicPlaying)
                {
                    Mix_PauseMusic();
                }
                else
                {
                    Mix_ResumeMusic();
                }
                logger.log_critical("Music is: " + std::string(musicPlaying ? "true" : "false"));
            }
            else if (scene2SFXSliderButton.is_selected())
            {
                std::cout << " You selected: Sound Slider" << std::endl;
            }
            else if (scene2VolumeSliderButton.is_selected())
            {
                std::cout << " You selected: Volume Slider" << std::endl;
            }
            else if (scene2scrollSpeedSliderButton.is_selected())
            {
                std::cout << " You selected: Scroll speed Slider" << std::endl;
            }
            else if (scene2returnToTitleButton.is_selected())
            {
                scene = 1;
            }
            else if (scene2returnToGameButton.is_selected())
            {
                if (gameStarted)
                {
                    if (!isMultiplayerGame)
                    {
                        startTimer = true;
                        toggle_countdown();
                        gamePaused = false;
                    }
                    scene = lastScene;
                }
                else
                {
                    std::cout << "Warning: Game hasn't started" << std::endl;
                }
            }
            else if (scene2saveSettingsButton.is_selected())
            {
                std::cout << " You selected: Save settings" << std::endl;
                SaveLoadData::save_settings(saveFileName, language);
            }
            else if (scene2ResetToDefaultSettingsButton.is_selected())
            {
                std::cout << " You selected: Reset settings" << std::endl;
                musicPlaying = true;
                language = "English";
                for (BaseButton *button : allButtons)
                {
                    button->set_font_size(defaultFont, 36);
                }
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_3(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene3buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene3buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene3buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene3buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene3returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene3creditsButton.is_selected())
            {
                std::cout << "You clicked: Credits" << std::endl;
                scene = 14;
            }
            else if (scene3sandboxButton.is_selected())
            {
                std::cout << "You clicked: Sandbox" << std::endl;
                scene = 100;
            }
            else if (scene3soundtrackButton.is_selected())
            {
                std::cout << "You clicked: Level Editor" << std::endl;
                scene = 15;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_4(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene4buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene4buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene4buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene4buttons, buttonDirection);
            break;
        case SDLK_BACKSPACE:
            std::cout << "You pressed: BACKSPACE" << std::endl;
            if (scene4inputPlayerNameButton.is_selected())
            {
                scene4inputPlayerNameButton.remove_last_character();
            }
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene4returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene4submitNameButton.is_selected())
            {
                std::cout << "You clicked: Submit Player Name Field" << std::endl;
                if (!scene4inputPlayerNameButton.get_text().empty())
                {
                    scene4inputPlayerNameButton.set_clicked(true);
                    std::cout << "Success: Submitted Player Name" << std::endl;
                }
                else
                {
                    std::cout << "Error: Please enter player name" << std::endl;
                }
            }
            else if (scene4inputPlayerNameButton.is_selected())
            {
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_5(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene5buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene5buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene5buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene5buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene5returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene5backButton.is_selected())
            {
                std::cout << "You clicked: Back" << std::endl;
                scrollYpos += scrollSpeed;
            }
            else if (scene5forwardButton.is_selected())
            {
                std::cout << "You clicked: Forward" << std::endl;
                scrollYpos -= scrollSpeed;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_6(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene6buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene6buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene6buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene6buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene6returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_7(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene7buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene7buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene7buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene7buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene7returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene7updateButton.is_selected())
            {
                std::cout << "You clicked: Update" << std::endl;
            }
            else if (scene7cancelButton.is_selected())
            {
                std::cout << "You clicked: Cancel" << std::endl;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_8(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene8buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene8buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene8buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene8buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene8returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene8loginButton.is_selected())
            {
                std::cout << "You clicked: Login" << std::endl;
            }
            else if (scene8registerButton.is_selected())
            {
                std::cout << "You clicked: Register" << std::endl;
                scene = 10;
            }
            else if (scene8inputemailButton.is_selected())
            {
                std::cout << "You clicked: Input Email" << std::endl;
            }
            else if (scene8inputpasswordButton.is_selected())
            {
                std::cout << "You clicked: Input Password" << std::endl;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_9(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene9buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene9buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene9buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene9buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene9returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene9submitButton.is_selected())
            {
                std::cout << "You clicked: Submit" << std::endl;
                if (!scene9inputusernameButton.get_text().empty() &&
                    !scene9inputemailButton.get_text().empty() &&
                    !scene9inputpasswordNameButton.get_text().empty())
                {
                    webserverClientContext.create_account(scene9inputusernameButton.get_text(), scene9inputemailButton.get_text(), scene9inputpasswordNameButton.get_text());
                }
            }
            else if (scene9inputusernameButton.is_selected())
            {
                std::cout << "You clicked: Input Username" << std::endl;
            }
            else if (scene9inputemailButton.is_selected())
            {
                std::cout << "You clicked: Input Email" << std::endl;
            }
            else if (scene9inputpasswordNameButton.is_selected())
            {
                std::cout << "You clicked: Input Password" << std::endl;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_10(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene10returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene10acceptPrivacyPolicyButton.is_selected())
            {
                std::cout << "You clicked: Accept Privacy Policy" << std::endl;
                scene10acceptPrivacyPolicyButton.set_clicked(true);
            }
            else if (scene10denyPrivacyPolicyButton.is_selected())
            {
                std::cout << "You clicked: Deny Privacy Policy" << std::endl;
                scene = 8;
            }
            else if (scene10acceptTermsPolicyButton.is_selected())
            {
                std::cout << "You clicked: Accept Terms Policy" << std::endl;
                scene10acceptTermsPolicyButton.set_clicked(true);
            }
            else if (scene10denyTermsPolicyButton.is_selected())
            {
                std::cout << "You clicked: Deny Terms Policy" << std::endl;
                scene = 8;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_11(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene11returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene11createGameButton.is_selected())
            {
                std::cout << "You clicked: Create Game" << std::endl;
            }
            else if (scene11joinGameButton.is_selected())
            {
                std::cout << "You clicked: Join Game" << std::endl;
            }
            else if (scene11refreshGamesButton.is_selected())
            {
                std::cout << "You clicked: Refresh Game" << std::endl;
            }
            else if (scene11sendMessageButton.is_selected())
            {
                std::cout << "You clicked: Send Message" << std::endl;
            }
            else if (scene11addFriendButton.is_selected())
            {
                std::cout << "You clicked: Add friend" << std::endl;
            }
            else if (scene11refreshFriendsButton.is_selected())
            {
                std::cout << "You clicked: Refresh Friends" << std::endl;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_12(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene12returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene12acceptButton.is_selected())
            {
                std::cout << "You clicked: Accept" << std::endl;
            }
            else if (scene12resetButton.is_selected())
            {
                std::cout << "You clicked: Reset" << std::endl;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_13(const SDL_Event &event) // Create Game
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene13buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene13buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene13buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene13buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene13cancelButton.is_selected())
            {
                std::cout << "You clicked: Cancel" << std::endl;
                scene = 12;
            }
            else if (scene13createButton.is_selected())
            {
                std::cout << "You clicked: Create" << std::endl;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_14(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene14buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene14buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene14buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene14buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene14returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_15(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene15buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene15buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene15buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene15buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene15FileDropdownButton.is_selected())
            {
                std::cout << "You clicked: File" << std::endl;
                scene15FileDropdownButton.render_buttons_from_dropdown_list(renderer);
            }
            else if (scene15returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_16(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene16buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene16buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene16buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene16buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene16returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_17(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene17buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene17buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene17buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene17buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene17returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_18(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene18buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene18buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene18buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene18buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene18returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_19(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene19buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene19buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene19buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene19buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene19returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_20(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene20buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene20buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene20buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene20buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene20returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_21(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene21buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene21buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene21buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene21buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene21returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_22(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene22buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene22buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene22buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene22buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene22returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_23(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene23buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene23buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene23buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene23buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene23returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_24(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene24buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene24buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene24buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene24buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene24returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_25(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene25buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene25buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene25buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene25buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene25returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_26(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene26buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene26buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene26buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene26buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene26returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_27(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene27buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene27buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene27buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene27buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene27returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene27backButton.is_selected())
            {
                std::cout << "You clicked: Back" << std::endl;
            }
            else if (scene27nextButton.is_selected())
            {
                std::cout << "You clicked: Next" << std::endl;
            }
            else if (scene27acceptButton.is_selected())
            {
                std::cout << "You clicked: Accept" << std::endl;
            }
            else if (scene27denyButton.is_selected())
            {
                std::cout << "You clicked: Deny" << std::endl;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_28(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene28buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene28buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene28buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene28buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene28returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Skip" << std::endl;
                scene = 101;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_29(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene29buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene29buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene29buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene29buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene29returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_30(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene30buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene30buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene30buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene30buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene30returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_31(const SDL_Event &event)
{
    if (keyPressed)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDLK_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene31buttons, buttonDirection);
            break;
        case SDLK_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene31buttons, buttonDirection);
            break;
        case SDLK_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene31buttons, buttonDirection);
            break;
        case SDLK_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene31buttons, buttonDirection);
            break;
        case SDLK_RETURN:
            std::cout << "You pressed: RETURN" << std::endl;
            if (scene31returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
        default:
            break;
        }
    }
}
void handle_keyboard_scene_gameplay(const SDL_Event &event, bool gamePaused)
{
    for (Entity *e : entities)
    {
        if (Player *p = dynamic_cast<Player *>(e))
        {
            if (p->get_player_id() == clientPlayerID)
            {
                if (keyPressed)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        std::cout << "You pressed: ESC" << std::endl;
                        if (!isMultiplayerGame)
                        {
                            startTimer = false;
                            gamePaused = true;
                            logger.log_non_critical("Game Paused");
                        }
                        lastScene = scene;
                        scene = 2;
                        break;
                    case SDLK_UP:
                        if (isMultiplayerGame)
                        {
                            webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity(), p->get_yVelocity() - p->get_acceleration(), "UP", webserverHostContext);
                        }
                        else
                        {
                            p->set_velocity(p->get_xVelocity(), p->get_yVelocity() - p->get_acceleration());
                            if (p->get_yVelocity() < -2.0f)
                            {
                                p->set_velocity(p->get_xVelocity(), -2.0f);
                            }
                        }
                        break;
                    case SDLK_DOWN:
                        if (isMultiplayerGame)
                        {
                            webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity(), p->get_yVelocity() + p->get_acceleration(), "DOWN", webserverHostContext);
                        }
                        else
                        {
                            p->set_velocity(p->get_xVelocity(), p->get_yVelocity() + p->get_acceleration());
                            if (p->get_yVelocity() > 2.0f)
                            {
                                p->set_velocity(p->get_xVelocity(), 2.0f);
                            }
                        }
                        break;
                    case SDLK_LEFT:
                        if (isMultiplayerGame)
                        {
                            webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity() - p->get_acceleration(), p->get_yVelocity(), "LEFT", webserverHostContext);
                        }
                        else
                        {
                            p->set_velocity(p->get_xVelocity() - p->get_acceleration(), p->get_yVelocity());
                            if (p->get_xVelocity() < -2.0f)
                            {
                                p->set_velocity(-2.0f, p->get_yVelocity());
                            }
                        }
                        break;
                    case SDLK_RIGHT:
                        if (isMultiplayerGame)
                        {
                            webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity() + p->get_acceleration(), p->get_yVelocity(), "RIGHT", webserverHostContext);
                        }
                        else
                        {
                            p->set_velocity(p->get_xVelocity() + p->get_acceleration(), p->get_yVelocity());
                            if (p->get_xVelocity() > 2.0f)
                            {
                                p->set_velocity(2.0f, p->get_yVelocity());
                            }
                        }
                        break;
                    case SDLK_RETURN:
                        std::cout << "You pressed: RETURN" << std::endl;
                    default:
                        break;
                    }
                }
                else
                {

                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        std::cout << "Released key: UP" << std::endl;
                        // Placeholder for playing stop animation if person is walking and stops still
                        break;
                    case SDLK_DOWN:
                        std::cout << "Released key: DOWN" << std::endl;
                        // Placeholder for playing stop animation if person is walking and stops still
                        break;
                    case SDLK_LEFT:
                        std::cout << "Released key: LEFT" << std::endl;
                        // Placeholder for playing stop animation if person is walking and stops still
                        break;
                    case SDLK_RIGHT:
                        std::cout << "Released key: RIGHT" << std::endl;
                        // Placeholder for playing stop animation if person is walking and stops still
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

void handle_gamepad_scene_1(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            quitEventLoop = true;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene1buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene1buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene1buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene1buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene1newGameButton.is_selected())
            {
                std::cout << "You pressed: New Game" << std::endl;
                setup_reset_game();
                scene = 102;
            }
            else if (scene1settingsButton.is_selected())
            {
                std::cout << "You pressed: Settings" << std::endl;
                scene = 2;
            }
            else if (scene1unlockablesButton.is_selected())
            {
                std::cout << "You pressed: Unlockables" << std::endl;
                scene = 3;
            }
            else if (scene1scoreButton.is_selected())
            {
                std::cout << "You pressed: Score" << std::endl;
                scene = 4;
            }
            else if (scene1helpButton.is_selected())
            {
                std::cout << "You pressed: Help" << std::endl;
                scene = 5;
            }
            else if (scene1achievementsButton.is_selected())
            {
                std::cout << "You pressed: Achievements" << std::endl;
                scene = 6;
            }
            else if (scene1multiplayerButton.is_selected())
            {
                std::cout << "You pressed: Multiplayer" << std::endl;
                scene = 7;
            }
            else if (scene1levelEditorButton.is_selected())
            {
                std::cout << "You pressed: Level Editor" << std::endl;
                scene = 15;
            }
            else if (scene1modStoreButton.is_selected())
            {
                std::cout << "You pressed: Mod Store" << std::endl;
                scene = 22;
            }
            else if (scene1quitGameButton.is_selected())
            {
                std::cout << "You pressed: Quit Game" << std::endl;
                quitEventLoop = true;
            }
            break;
        case SDL_CONTROLLER_BUTTON_B:
            std::cout << "You pressed: B" << std::endl;
            quitEventLoop = true;
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_2(const int &button, bool gamePaused)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            if (scene2SFXSliderButton.is_selected())
            {
                // soundVolume = std::min<int>(100, soundVolume + 1);
                soundVolume = soundVolume + 1;
                if (soundVolume >= 100)
                {
                    soundVolume = 100;
                }
            }
            else if (scene2VolumeSliderButton.is_selected())
            {
                // musicVolume = std::min<int>(100, musicVolume + 1);
                musicVolume = musicVolume + 1;
                if (musicVolume >= 100)
                {
                    musicVolume = 100;
                }
            }
            else if (scene2scrollSpeedSliderButton.is_selected())
            {
                // scrollSpeed = std::min<int>(100, scrollSpeed + 1);
                scrollSpeed = scrollSpeed + 1;
                if (scrollSpeed >= 100)
                {
                    scrollSpeed = 100;
                }
            }
            else
            {
                BaseButton::find_nearest_button(scene2buttons, buttonDirection);
            }
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            if (scene2SFXSliderButton.is_selected())
            {
                // soundVolume = std::max<int>(0, soundVolume - 1);
                soundVolume = soundVolume - 1;
                if (soundVolume <= 0)
                {
                    soundVolume = 0;
                }
            }
            else if (scene2VolumeSliderButton.is_selected())
            {
                // musicVolume = std::max<int>(0, musicVolume - 1);
                musicVolume = musicVolume - 1;
                if (musicVolume <= 0)
                {
                    musicVolume = 0;
                }
            }
            else if (scene2scrollSpeedSliderButton.is_selected())
            {
                // scrollSpeed = std::min<int>(0, scrollSpeed - 1);
                scrollSpeed = scrollSpeed - 1;
                if (scrollSpeed <= 0)
                {
                    scrollSpeed = 0;
                }
            }
            else
            {
                BaseButton::find_nearest_button(scene2buttons, buttonDirection);
            }
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene2buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene2buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene2ChangeFontButton.is_selected())
            {
                if (defaultFont == font24)
                {
                    std::cout << "You pressed: Changed to Font 36" << std::endl;
                    defaultFont = font36;
                    for (BaseButton *b : allButtons)
                    {
                        b->set_font_size(defaultFont, 36);
                    }
                }
                else if (defaultFont == font36)
                {
                    std::cout << "You pressed: Changed to Font 48" << std::endl;
                    defaultFont = font48;
                    for (BaseButton *b : allButtons)
                    {
                        b->set_font_size(defaultFont, 48);
                    }
                }
                else if (defaultFont == font48)
                {
                    std::cout << "You pressed: Changed to Font 24" << std::endl;
                    defaultFont = font24;
                    for (BaseButton *b : allButtons)
                    {
                        b->set_font_size(defaultFont, 24);
                    }
                }
            }
            else if (scene2ChangeLanguageButton.is_selected())
            {
                std::cout << " You selected: Change Language" << std::endl;
                if (language == "English")
                {
                    language = "日本語";
                    std::cout << "Language now set to: " << language << std::endl;
                }
                else
                {
                    language = "English";
                    std::cout << "Language now set to: " << language << std::endl;
                }
            }
            else if (scene2changeKeymappingButton.is_selected())
            {
                std::cout << " You selected: Keymapping" << std::endl;
                scene = 12;
            }
            else if (scene2displayOnScreenKeysButton.is_selected())
            {
                std::cout << " You selected: Display On Screen Keys" << std::endl;
                displayOnScreenKeys = !displayOnScreenKeys;
            }
            else if (scene2fullscreenToggleButton.is_selected())
            {
                logger.log_non_critical("You selected: FUllscreen toggle");
                int borderFlag = SDL_GetWindowFlags(window);
                bool isFullscreen = (borderFlag & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
                if (isFullscreen)
                {
                    SDL_SetWindowFullscreen(window, 0);
                }
                else
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
            }
            else if (scene2enableVsyncButton.is_selected())
            {
                logger.log_non_critical("You selected: Vsync toggle");
                vsyncEnabled = !vsyncEnabled;
                recreate_renderer();
            }
            else if (scene2toggleFPSButton.is_selected())
            {
                std::cout << " You selected: FPS toggle" << std::endl;
                displayFPS = !displayFPS;
            }
            else if (scene2resolutionsDropdownButton.is_selected())
            {
                std::cout << " You selected: Resolutions drop down" << std::endl;
                scene2resolutionsDropdownButton.set_clicked(true);
            }
            else if (scene2toggleSoundButton.is_selected())
            {
                std::cout << " You selected: Sound toggle" << std::endl;
            }
            else if (scene2toggleMusicButton.is_selected())
            {
                logger.log_critical("You selected: toggle Music");
                musicPlaying = !musicPlaying;
                if (musicPlaying)
                {
                    Mix_PauseMusic();
                }
                else
                {
                    Mix_ResumeMusic();
                }
                logger.log_critical("Music is: " + std::string(musicPlaying ? "true" : "false"));
            }
            else if (scene2SFXSliderButton.is_selected())
            {
                std::cout << " You selected: Sound Slider" << std::endl;
            }
            else if (scene2VolumeSliderButton.is_selected())
            {
                std::cout << " You selected: Volume Slider" << std::endl;
            }
            else if (scene2scrollSpeedSliderButton.is_selected())
            {
                std::cout << " You selected: Scroll speed Slider" << std::endl;
            }
            else if (scene2returnToTitleButton.is_selected())
            {
                scene = 1;
            }
            else if (scene2returnToGameButton.is_selected())
            {
                if (gameStarted)
                {
                    if (!isMultiplayerGame)
                    {
                        startTimer = true;
                        toggle_countdown();
                        gamePaused = false;
                    }
                    scene = lastScene;
                }
                else
                {
                    std::cout << "Warning: Game hasn't started" << std::endl;
                }
            }
            else if (scene2saveSettingsButton.is_selected())
            {
                std::cout << " You selected: Save settings" << std::endl;
                SaveLoadData::save_settings(saveFileName, language);
            }
            else if (scene2ResetToDefaultSettingsButton.is_selected())
            {
                std::cout << " You selected: Reset settings" << std::endl;
                musicPlaying = true;
                language = "English";
                for (BaseButton *button : allButtons)
                {
                    button->set_font_size(defaultFont, 36);
                }
            }
        case SDL_CONTROLLER_BUTTON_B:
            std::cout << "You pressed: B" << std::endl;
            scene = 1;
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_3(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene3buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene3buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene3buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene3buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene3returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene3creditsButton.is_selected())
            {
                std::cout << "You clicked: Credits" << std::endl;
                scene = 14;
            }
            else if (scene3sandboxButton.is_selected())
            {
                std::cout << "You clicked: Sandbox" << std::endl;
                scene = 100;
            }
            else if (scene3soundtrackButton.is_selected())
            {
                std::cout << "You clicked: Level Editor" << std::endl;
                scene = 15;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_4(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene4buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene4buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene4buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene4buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene4returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene4submitNameButton.is_selected())
            {
                std::cout << "You clicked: Submit Player Name Field" << std::endl;
                if (!scene4inputPlayerNameButton.get_text().empty())
                {
                    scene4inputPlayerNameButton.set_clicked(true);
                    std::cout << "Success: Submitted Player Name" << std::endl;
                }
                else
                {
                    std::cout << "Error: Please enter player name" << std::endl;
                }
            }
            else if (scene4inputPlayerNameButton.is_selected())
            {
                std::cout << "You pressed: Input Player Name" << std::endl;
            }
        case SDL_CONTROLLER_BUTTON_B:
            std::cout << "You pressed: B" << std::endl;
            if (scene4inputPlayerNameButton.is_selected())
            {
                scene4inputPlayerNameButton.remove_last_character();
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_5(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene5buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene5buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene5buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene5buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene5returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene5backButton.is_selected())
            {
                std::cout << "You clicked: Back" << std::endl;
                scrollYpos += scrollSpeed;
            }
            else if (scene5forwardButton.is_selected())
            {
                std::cout << "You clicked: Forward" << std::endl;
                scrollYpos -= scrollSpeed;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_6(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene6buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene6buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene6buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene6buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene6returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_7(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene7buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene7buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene7buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene7buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene7returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene7updateButton.is_selected())
            {
                std::cout << "You clicked: Update" << std::endl;
            }
            else if (scene7cancelButton.is_selected())
            {
                std::cout << "You clicked: Cancel" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_8(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene8buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene8buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene8buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene8buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene8returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene8loginButton.is_selected())
            {
                std::cout << "You clicked: Login" << std::endl;
            }
            else if (scene8registerButton.is_selected())
            {
                std::cout << "You clicked: Register" << std::endl;
                scene = 10;
            }
            else if (scene8inputemailButton.is_selected())
            {
                std::cout << "You clicked: Input Email" << std::endl;
            }
            else if (scene8inputpasswordButton.is_selected())
            {
                std::cout << "You clicked: Input Password" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_9(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene9buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene9buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene9buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene9buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene9returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene9submitButton.is_selected())
            {
                std::cout << "You clicked: Submit" << std::endl;
                if (!scene9inputusernameButton.get_text().empty() &&
                    !scene9inputemailButton.get_text().empty() &&
                    !scene9inputpasswordNameButton.get_text().empty())
                {

                    webserverClientContext.create_account(scene9inputusernameButton.get_text(), scene9inputemailButton.get_text(), scene9inputpasswordNameButton.get_text());
                }
            }
            else if (scene9inputusernameButton.is_selected())
            {
                std::cout << "You clicked: Input Username" << std::endl;
            }
            else if (scene9inputemailButton.is_selected())
            {
                std::cout << "You clicked: Input Email" << std::endl;
            }
            else if (scene9inputpasswordNameButton.is_selected())
            {
                std::cout << "You clicked: Input Password" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_10(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene10returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene10acceptPrivacyPolicyButton.is_selected())
            {
                std::cout << "You clicked: Accept Privacy Policy" << std::endl;
                scene10acceptPrivacyPolicyButton.set_clicked(true);
            }
            else if (scene10denyPrivacyPolicyButton.is_selected())
            {
                std::cout << "You clicked: Deny Privacy Policy" << std::endl;
                scene = 8;
            }
            else if (scene10acceptTermsPolicyButton.is_selected())
            {
                std::cout << "You clicked: Accept Terms Policy" << std::endl;
                scene10acceptTermsPolicyButton.set_clicked(true);
            }
            else if (scene10denyTermsPolicyButton.is_selected())
            {
                std::cout << "You clicked: Deny Terms Policy" << std::endl;
                scene = 8;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_11(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene11returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene11createGameButton.is_selected())
            {
                std::cout << "You clicked: Create Game" << std::endl;
            }
            else if (scene11joinGameButton.is_selected())
            {
                std::cout << "You clicked: Join Game" << std::endl;
            }
            else if (scene11refreshGamesButton.is_selected())
            {
                std::cout << "You clicked: Refresh Game" << std::endl;
            }
            else if (scene11sendMessageButton.is_selected())
            {
                std::cout << "You clicked: Send Message" << std::endl;
            }
            else if (scene11addFriendButton.is_selected())
            {
                std::cout << "You clicked: Add friend" << std::endl;
            }
            else if (scene11refreshFriendsButton.is_selected())
            {
                std::cout << "You clicked: Refresh Friends" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_12(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene10buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene12returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene12acceptButton.is_selected())
            {
                std::cout << "You clicked: Accept" << std::endl;
            }
            else if (scene12resetButton.is_selected())
            {
                std::cout << "You clicked: Reset" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_13(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene13buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene13buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene13buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene13buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene13cancelButton.is_selected())
            {
                std::cout << "You clicked: Cancel" << std::endl;
                scene = 12;
            }
            else if (scene13createButton.is_selected())
            {
                std::cout << "You clicked: Create" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_14(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene14buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene14buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene14buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene14buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene14returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_15(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene15buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene15buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene15buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene15buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene15FileDropdownButton.is_selected())
            {
                std::cout << "You clicked: File" << std::endl;
                scene15FileDropdownButton.render_buttons_from_dropdown_list(renderer);
            }
            else if (scene15returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_16(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene16buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene16buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene16buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene16buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene16returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_17(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene17buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene17buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene17buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene17buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene17returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_18(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene18buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene18buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene18buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene18buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene18returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_19(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene19buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene19buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene19buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene19buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene19returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_20(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene20buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene20buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene20buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene20buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene20returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_21(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene21buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene21buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene21buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene21buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene21returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_22(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene22buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene22buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene22buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene22buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene22returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_23(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene23buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene23buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene23buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene23buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene23returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_24(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene24buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene24buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene24buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene24buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene24returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_25(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene25buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene25buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene25buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene25buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene25returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_26(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene26buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene26buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene26buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene26buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene26returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_27(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene27buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene27buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene27buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene27buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene27returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            else if (scene27backButton.is_selected())
            {
                std::cout << "You clicked: Back" << std::endl;
            }
            else if (scene27nextButton.is_selected())
            {
                std::cout << "You clicked: Next" << std::endl;
            }
            else if (scene27acceptButton.is_selected())
            {
                std::cout << "You clicked: Accept" << std::endl;
            }
            else if (scene27denyButton.is_selected())
            {
                std::cout << "You clicked: Deny" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_28(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene28buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene28buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene28buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene28buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene28returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 101;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_29(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene29buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene29buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene29buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene29buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene29returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_30(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene30buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene30buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene30buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene30buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene30returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_31(const int &button)
{
    if (keyPressed)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_START:
            std::cout << "You pressed: ESC" << std::endl;
            scene = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            std::cout << "You pressed: UP" << std::endl;
            buttonDirection = "UP";
            BaseButton::find_nearest_button(scene31buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            std::cout << "You pressed: DOWN" << std::endl;
            buttonDirection = "DOWN";
            BaseButton::find_nearest_button(scene31buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            std::cout << "You pressed: LEFT" << std::endl;
            buttonDirection = "LEFT";
            BaseButton::find_nearest_button(scene31buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            std::cout << "You pressed: RIGHT" << std::endl;
            buttonDirection = "RIGHT";
            BaseButton::find_nearest_button(scene31buttons, buttonDirection);
            break;
        case SDL_CONTROLLER_BUTTON_A:
            std::cout << "You pressed: A" << std::endl;
            if (scene31returnToTitleButton.is_selected())
            {
                std::cout << "You clicked: Return to title" << std::endl;
                scene = 1;
            }
            break;
        default:
            break;
        }
    }
}
void handle_gamepad_scene_gameplay(const int &button, bool gamePaused)
{
    for (Entity *e : entities)
    {
        if (Player *p = dynamic_cast<Player *>(e))
        {
            if (p->get_player_id() == clientPlayerID)
            {
                if (keyPressed)
                {
                    switch (button)
                    {
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        std::cout << "You pressed: UP" << std::endl;
                        if (isMultiplayerGame)
                        {
                            webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity(), p->get_yVelocity() - p->get_acceleration(), "UP", webserverHostContext);
                        }
                        else
                        {
                            p->set_velocity(p->get_xVelocity(), p->get_yVelocity() - p->get_acceleration());
                            if (p->get_yVelocity() < -2.0f)
                            {
                                p->set_velocity(p->get_xVelocity(), -2.0f);
                            }
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        if (isMultiplayerGame)
                        {
                            webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity(), p->get_yVelocity() + p->get_acceleration(), "DOWN", webserverHostContext);
                        }
                        else
                        {
                            p->set_velocity(p->get_xVelocity(), p->get_yVelocity() + p->get_acceleration());
                            if (p->get_yVelocity() > 2.0f)
                            {
                                p->set_velocity(p->get_xVelocity(), 2.0f);
                            }
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        if (isMultiplayerGame)
                        {
                            webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity() - p->get_acceleration(), p->get_yVelocity(), "LEFT", webserverHostContext);
                        }
                        else
                        {
                            p->set_velocity(p->get_xVelocity() - p->get_acceleration(), p->get_yVelocity());
                            if (p->get_xVelocity() < -2.0f)
                            {
                                p->set_velocity(-2.0f, p->get_yVelocity());
                            }
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        if (isMultiplayerGame)
                        {
                            webserverClientContext.POST_player_movement(p->get_player_id(), p->get_xVelocity() + p->get_acceleration(), p->get_yVelocity(), "RIGHT", webserverHostContext);
                        }
                        else
                        {
                            p->set_velocity(p->get_xVelocity() + p->get_acceleration(), p->get_yVelocity());
                            if (p->get_xVelocity() > 2.0f)
                            {
                                p->set_velocity(2.0f, p->get_yVelocity());
                            }
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_A:
                        std::cout << "You pressed: RETURN" << std::endl;
                    case SDL_CONTROLLER_BUTTON_B:
                        std::cout << "You pressed: B" << std::endl;
                        if (!isMultiplayerGame)
                        {
                            startTimer = false;
                            gamePaused = true;
                            logger.log_non_critical("Game Paused");
                        }
                        lastScene = scene;
                        scene = 2;
                    default:
                        break;
                    }
                }
                else
                {

                    switch (button)
                    {
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        std::cout << "Released key: UP" << std::endl;
                        // Placeholder for playing stop animation if person is walking and stops still
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        std::cout << "Released key: DOWN" << std::endl;
                        // Placeholder for playing stop animation if person is walking and stops still
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        std::cout << "Released key: LEFT" << std::endl;
                        // Placeholder for playing stop animation if person is walking and stops still
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        std::cout << "Released key: RIGHT" << std::endl;
                        // Placeholder for playing stop animation if person is walking and stops still
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}
