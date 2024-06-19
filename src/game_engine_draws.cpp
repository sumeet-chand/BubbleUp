/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Definition file
    License: MIT License


    _________________________________________________________________________________________________

                                SDL DRAWS FUNCTIONS DEFINITIONS
    _________________________________________________________________________________________________


    DESCRIPTION

    Draw function calls for SDL game (e.g, render_text(), or entity->render_rect()) seperated by each
    scene.

    Declarations: ./headers/game_enginedraws.hpp
    Definitions: ./src/game_enginedraws.cpp


    EXAMPLE


*/

#include "../headers/game_engine_draws.hpp"

// FORWARD DECLARATIONS
void render_text(const std::string &text, int x, int y, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText, TTF_Font *font);
void draw_file_contents_to_screen(const std::string &fileToOutput);

void draw_timer()
{
    SDL_Rect timerRect = {static_cast<int>(SCREEN_WIDTH * 0.05), static_cast<int>(SCREEN_HEIGHT * 0.03), (SCREEN_WIDTH / 5), (SCREEN_HEIGHT / 8)};
    SDL_RenderCopy(renderer, timerTexture, nullptr, &timerRect);

    int minutes = countdownSeconds / 60;
    int seconds = countdownSeconds % 60;

    // If minutes or seconds < 10, it will add an 0 e.g. 120 seconds = 2. As 2 < 10, final output: 02:00
    std::string timerText = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);

    render_text(timerText, timerRect.x + 130, timerRect.y + 30, 0, 0, 0, 255, defaultFont);
}
void draw_scores(const std::vector<Score> &scores)
{
    // Draw grid titles
    render_text("NAME", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.2), 0, 0, 0, 255, defaultFont);
    render_text("SCORE", (SCREEN_WIDTH * 0.4), (SCREEN_HEIGHT * 0.2), 0, 0, 0, 255, defaultFont);
    render_text("TIME", (SCREEN_WIDTH * 0.7), (SCREEN_HEIGHT * 0.2), 0, 0, 0, 255, defaultFont);

    // Draw grid lines
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
    for (int i = 0; i < 11; i++)                    // draw 11 horizontal lines
    {
        SDL_RenderDrawLine(renderer, 0, (SCREEN_HEIGHT * 0.25) + i * (SCREEN_HEIGHT * 0.1), SCREEN_WIDTH, (SCREEN_HEIGHT * 0.25) + i * (SCREEN_HEIGHT * 0.1));
    }
    for (int i = 1; i < 3; ++i) // Draw 2 vertical lines
    {
        SDL_RenderDrawLine(renderer, i * (SCREEN_WIDTH * 0.3), (SCREEN_HEIGHT * 0.2), i * (SCREEN_WIDTH * 0.3), SCREEN_HEIGHT);
    }

    // std::sort(scores.begin(), scores.end(), compare_scores);

    for (size_t i = 0; i < scores.size(); ++i)
    {
        const Score &s = scores[i]; // Accessing the current score
        float y;
        if (i == 0)
        {
            y = 0.0f;
        }
        else
        {
            y = 0.0f + (i * 0.1f);
        }
        if (i != 10) // Render only 10 scores max
        {
            render_text(s.name, (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * (0.3 + y)), 0, 0, 0, 255, defaultFont);
            render_text(std::to_string(s.score), (SCREEN_WIDTH * 0.4), (SCREEN_HEIGHT * (0.3 + y)), 0, 0, 0, 255, defaultFont);
            render_text(s.datetime, (SCREEN_WIDTH * 0.7), (SCREEN_HEIGHT * (0.3 + y)), 0, 0, 0, 255, defaultFont);
        }
    }
}
void draw_HUD()
{
    for (Entity *e : entities)
    {
        if (Player *player = dynamic_cast<Player *>(e))
        {
            if (player->get_player_id() == clientPlayerID)
            {
                render_text("Score: " + std::to_string(player->get_score()), (SCREEN_WIDTH * 0.4), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);
                render_text("Health: " + std::to_string(player->get_health()), (SCREEN_WIDTH * 0.6), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);
            }
        }
    }
}
void draw_entities()
{
    for (Entity *e : entities)
    {
        // update entity position based on player camera position
        SDL_Point cameraDisplacement;
        if (Player *player = dynamic_cast<Player *>(e))
        {
            if (player->get_player_id() == clientPlayerID)
            {
                cameraDisplacement.x = ((player->get_rect().x + (player->get_rect().w / 2)) - (SCREEN_WIDTH / 2)) * 0.1;
                cameraDisplacement.y = ((player->get_rect().y + (player->get_rect().h / 2)) - (SCREEN_HEIGHT / 2)) * 0.1;
                // finally draw player then exit out of function with continue
                e->update_animation();
                e->set_animation_texture();
                e->render_texture(cameraRect.x, cameraRect.y);
            }
            continue;
        }
        // draw entities with displacement
        e->update_animation();
        e->set_animation_texture();
        e->render_texture(cameraDisplacement.x, cameraDisplacement.y);
    }
}

void draw_scene_1()
{
    // row 1
    render_text("Bubble UP", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.01), 0, 0, 0, 255, font48);

    // row 7
    render_text("Version: " + softwareVersion, (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.9), 0, 0, 0, 255, defaultFont);
    render_text("by Sumeet Singh @sumeet-singh.com", (SCREEN_WIDTH * 0.4), (SCREEN_HEIGHT * 0.9), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene1buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_2()
{
    render_text("SETTINGS", (SCREEN_WIDTH * 0.4), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene2buttons)
    {
        b->render_button_rect();
    }

    if (scene2resolutionsDropdownButton.get_clicked())
    {
        scene2resolutionsDropdownButton.render_buttons_from_dropdown_list(renderer);
    }

    render_text("Sound Volume: " + std::to_string(soundVolume), (SCREEN_WIDTH * 0.6), (SCREEN_HEIGHT * 0.5), 0, 0, 0, 255, defaultFont);
    render_text("Music Volume: " + std::to_string(musicVolume), (SCREEN_WIDTH * 0.6), (SCREEN_HEIGHT * 0.6), 0, 0, 0, 255, defaultFont);
    render_text("Scroll Speed: " + std::to_string(scrollSpeed), (SCREEN_WIDTH * 0.6), (SCREEN_HEIGHT * 0.7), 0, 0, 0, 255, defaultFont);
}
void draw_scene_3()
{
    // row 1
    render_text("UNLOCKABLES", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene3buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_4()
{
    // Row 1
    render_text("SCORE", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    draw_scores(scores);

    if (!scene4inputPlayerNameButton.get_clicked())
    {
        render_text("Enter Name: ", (SCREEN_WIDTH * 0.05), (SCREEN_HEIGHT * 0.8), 0, 0, 0, 255, defaultFont);
        scene4submitNameButton.render_button_rect();
        scene4inputPlayerNameButton.render_button_rect();
    }

    scene4returnToTitleButton.render_button_rect();
}
void draw_scene_5()
{
    // row 1
    render_text("HELP", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    // Draw a box background to read easier
    SDL_SetRenderDrawColor(renderer, 220, 193, 167, 255); // RGB: Sepia
    SDL_Rect greyboxRect = {static_cast<int>(SCREEN_WIDTH * 0.05), static_cast<int>(SCREEN_HEIGHT * 0.01),
                            static_cast<int>(SCREEN_WIDTH * 0.85), SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &greyboxRect);

    draw_file_contents_to_screen(readmeFileName);

    for (BaseButton *b : scene5buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_6()
{
    // row 1
    render_text("ACHIEVEMENTS", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);
    // row 2
    render_text("1. Loser Loser (Lost once)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.2), 0, 0, 0, 255, defaultFont);
    // row 3
    render_text("2. Winner Winner (Won once)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.25), 0, 0, 0, 255, defaultFont);
    // row 4
    render_text("3. Richy Richy (Reached high score of 100)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.3), 0, 0, 0, 255, defaultFont);
    // row 5
    render_text("4. Sleepy Sleepy (Trapped 100 enemies)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.35), 0, 0, 0, 255, defaultFont);
    // row 6
    render_text("5. Looky Looky (Found hidden level)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.4), 0, 0, 0, 255, defaultFont);
    // row 7
    render_text("6. Breaky Breaky (Destroyed an Obstacle)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.45), 0, 0, 0, 255, defaultFont);
    // row 8
    render_text("7. Touchy Touchy (Bumped into another Player)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.5), 0, 0, 0, 255, defaultFont);
    // row 9
    render_text("8. Shaky Shaky (Escaped from 10 bubbles)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.55), 0, 0, 0, 255, defaultFont);
    // row 10
    render_text("9. Queeney Queeney (Won game ending 1)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.6), 0, 0, 0, 255, defaultFont);
    // row 11
    render_text("10. Kingy Kingy (Won Game ending 2)", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.65), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene6buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_7()
{
    // row 1
    render_text("CHECK FOR UPDATES", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    render_text("To access online services your game needs to be updated to the latest version.",
                (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.3), 0, 0, 0, 255, defaultFont);
    render_text("Checking online to see if new game version is available. Current version is: " + updateApp.currentVersion,
                (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.4), 0, 0, 0, 255, defaultFont);

    if (updateApp.clickedCheckForUpdates)
    {
        updateApp.curl_website_to_find_string();
        updateApp.clickedCheckForUpdates = false;
    }

    if (updateApp.newVersionAvailable)
    {
        render_text("New version is available: " + updateApp.foundString, (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.5), 0, 0, 0, 255, defaultFont);
        render_text("Would you like to download?", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.6), 0, 0, 0, 255, defaultFont);

        if (!updateApp.startUpdate)
        {
            scene7updateButton.render_button_rect();
            scene7cancelButton.render_button_rect();
            scene7returnToTitleButton.render_button_rect();
        }
        if (updateApp.startUpdate)
        {
            render_text("UPDATING GAME. PLEASE BE PATIENT. DO NOT CLOSE...", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.7), 0, 0, 0, 255, defaultFont);
        }
        if (updateApp.applicationUpdated)
        {
            softwareVersion = updateApp.newVersionAvailable;
            render_text("You have downloaded latest version: " + softwareVersion, (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.7), 0, 0, 0, 255, defaultFont);
            SDL_Delay(3000);
            scene = 8;
        }
    }
    else
    {
        scene = 8;
    }
}
void draw_scene_8()
{
    // row 1
    render_text("ONLINE LOGIN", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    render_text("Enter Email:", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.3), 0, 0, 0, 255, defaultFont);
    render_text("Enter Password:", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.4), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene8buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_9()
{
    // row 1
    render_text("CREATE ACCOUNT", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    render_text("Enter Username:", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.3), 0, 0, 0, 255, defaultFont);
    render_text("Enter Email:", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.4), 0, 0, 0, 255, defaultFont);
    render_text("Enter Password:", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.5), 0, 0, 0, 255, defaultFont);

    if (scene9submitButton.get_clicked())
    {
        if (scene9inputusernameButton.get_text().empty())
        {
            render_text("Username missing", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.6), 0, 0, 0, 255, defaultFont);
        }
        else if (scene9inputemailButton.get_text().empty())
        {
            render_text("Email missing", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.7), 0, 0, 0, 255, defaultFont);
        }
        else if (scene9inputpasswordNameButton.get_text().empty())
        {
            render_text("Password missing", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.8), 0, 0, 0, 255, defaultFont);
        }
    }

    if (!webserverClientContext.response_success())
    {
        render_text("Failed to login: ", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.8), 0, 0, 0, 255, defaultFont);
    }

    for (BaseButton *b : scene9buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_10()
{
    // row 1
    render_text("DISPLAY POLICIES", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    // Draw a box background to read easier
    SDL_SetRenderDrawColor(renderer, 220, 193, 167, 255); // RGB: Sepia
    SDL_Rect greyboxRect = {static_cast<int>(SCREEN_WIDTH * 0.05), static_cast<int>(SCREEN_HEIGHT * 0.01),
                            static_cast<int>(SCREEN_WIDTH * 0.85), SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &greyboxRect);

    if (!scene10acceptPrivacyPolicyButton.get_clicked())
    {
        draw_file_contents_to_screen(privacyPolicyFileName);
        scene10acceptPrivacyPolicyButton.render_button_rect();
        scene10denyPrivacyPolicyButton.render_button_rect();
    }
    if (scene10acceptPrivacyPolicyButton.get_clicked())
    {
        draw_file_contents_to_screen(termsAndConditionsFileName);
        scene10acceptTermsPolicyButton.render_button_rect();
        scene10denyTermsPolicyButton.render_button_rect();
    }
    scene10returnToTitleButton.render_button_rect();
}
void draw_scene_11()
{
    // row 1
    render_text("MULTIPLAYER LOBBY", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene11buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_12()
{
    // row 1
    render_text("KEYBINDINGS", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene12buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_13()
{
    // row 1
    render_text("CREATE GAME", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene13buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_14()
{
    // row 1
    render_text("CREDITS", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    // Draw a box background to read easier
    SDL_SetRenderDrawColor(renderer, 220, 193, 167, 255); // RGB: Sepia
    SDL_Rect greyboxRect = {static_cast<int>(SCREEN_WIDTH * 0.05), static_cast<int>(SCREEN_HEIGHT * 0.01),
                            static_cast<int>(SCREEN_WIDTH * 0.85), SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &greyboxRect);

    draw_file_contents_to_screen(creditsFileName);

    for (BaseButton *b : scene14buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_15()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    if (scene15FileDropdownButton.get_clicked())
    {
        scene15FileDropdownButton.render_buttons_from_dropdown_list(renderer);
    }

    for (BaseButton *b : scene15buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_16()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene16buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_17()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene17buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_18()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene18buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_19()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene19buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_20()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene20buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_21()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene21buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_22()
{
    // row 1
    render_text("Mod Store", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene22buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_23()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene23buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_24()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene24buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_25()
{
    // row 1
    render_text("LEVEL EDITOR", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene25buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_26()
{
    // row 1
    render_text("Soundtrack", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);

    for (BaseButton *b : scene26buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_27()
{
    // Player select
    render_text("Player select", (SCREEN_WIDTH * 0.45), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, font48);
    render_text("Rajan", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.2), 0, 0, 0, 255, defaultFont);
    render_text("King", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.3), 0, 0, 0, 255, defaultFont);
    render_text("Shah", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.4), 0, 0, 0, 255, defaultFont);
    render_text("Tenno", (SCREEN_WIDTH * 0.2), (SCREEN_HEIGHT * 0.5), 0, 0, 0, 255, defaultFont);

    for (BaseButton *b : scene27buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_28()
{
    for (BaseButton *b : scene28buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_29()
{
    for (BaseButton *b : scene29buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_30()
{
    for (BaseButton *b : scene30buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_31()
{
    for (BaseButton *b : scene31buttons)
    {
        b->render_button_rect();
    }
}
void draw_scene_gameplay()
{
    draw_entities();
    draw_HUD();
    draw_timer();
    ParticleGenerator::render_particles(particles, renderer);
    ParticleGenerator::clear_particles(particles, SCREEN_HEIGHT);

    if (displayOnScreenKeys) // if you want on screen keys show all the buttons e.g. UP, DOWN, A, MENU
    {
        for (BaseButton *b : sceneGameplaybuttons)
        {
            b->render_button_rect();
        }
    }
}
