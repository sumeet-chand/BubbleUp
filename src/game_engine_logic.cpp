/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Definition file
    License: MIT License


    _________________________________________________________________________________________________

                                SDL LOGIC FUNCTIONS DEFINITIONS
    _________________________________________________________________________________________________


    DESCRIPTION

    Game engine logic code e.g. drawing maps, using in game quest system, etc.,
    
    Declarations: ./headers/game_engine_logic.hpp
    Definitions: ./src/game_engine_logic.cpp


    EXAMPLE


*/

#include "../headers/game_engine_logic.hpp"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>

// FORWARD DECLARATIONS
void render_text(const std::string &text, int x, int y, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText, TTF_Font *font);

void toggle_countdown()
{
    if (startTimer)
    {
        std::thread timer_thread([]()
                                 {
            while (countdownSeconds > 0 && startTimer)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                countdownSeconds--; // Decrement countdown
                std::cout << "Countdown: " << countdownSeconds << std::endl; // Debugging output
            }

            if (!startTimer)
            {
                std::cout << "Timer stopped. Stopping countdown threads." << std::endl;
            }
            else if (countdownSeconds <= 0)
            {
                std::cout << "Timer reached 0 seconds. You lose" << std::endl;
                startTimer = false; // Stop the timer
            } });
        timer_thread.detach();
        std::cout << "Timer started for " << countdownSeconds << " seconds" << std::endl;
    }
    else
    {
        std::cout << "Timer stopped" << std::endl;
    }
}

std::string get_datetime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S %d/%m/%y", std::localtime(&time));
    return std::string(buffer);
}

void POST_player_scores_to_webserver(const Score &s)
{
    webserverHostContext.webserver_process_single_game_player_score(s);
}

void initialise_score()
{
    Score s;
    for (Entity *e : entities)
    {
        if (Player *player = dynamic_cast<Player *>(e))
        {
            if (player->get_player_id() == clientPlayerID)
            {
                s.playerID = player->get_player_id();
                s.name = scene4inputPlayerNameButton.get_text();
                s.score = player->get_score();
                s.datetime = get_datetime();
                scores.push_back(s);
                std::cout << "Scoreboard time for " << s.playerID << " " << s.name << " is: " << s.datetime << std::endl;
                if (isMultiplayerGame)
                {
                    POST_player_scores_to_webserver(s);
                }
            }
        }
    }
}

bool compare_Scores(const Score &a, const Score &b)
{
    return a.score > b.score;
}

std::string find_os()
{
    const char *os = SDL_GetPlatform();
    if (os != NULL)
    {
        std::cout << "Success: Found host operating system: " << os << std::endl;
        return os;
    }
    else
    {
        logger.log_critical("Error: Failed to detect the host operating system.");
        return "Unknown OS";
    }
}

void draw_file_contents_to_screen(const std::string &fileToOutput)
{
    std::ifstream sentence_file(fileToOutput);
    if (!sentence_file.is_open())
    {
        logger.log_critical("Error: Failed to open: " + fileToOutput);
        return;
    }

    // Render position for the first line of text
    int renderY = static_cast<int>(SCREEN_WIDTH * 0.2);

    // Adjust renderY based on scrolling position
    renderY += scrollYpos;

    // Read lines from the file and render them to the window
    std::string line;
    while (std::getline(sentence_file, line))
    {
        if (renderY < SCREEN_HEIGHT)
        {
            // Render only if the text is within the visible area of the window
            if (line.size() > 80) // Check if the line is too long
            {
                // Split the line into two parts
                std::string firstHalf = line.substr(0, 80); // assuming you want to split at 40 characters
                std::string secondHalf = line.substr(80);

                // Render the first half
                render_text(firstHalf, static_cast<int>(SCREEN_WIDTH * 0.1), renderY, 0, 0, 0, 255, defaultFont);
                renderY += 30; // Vertical spacing between lines

                // Render the second half
                if (renderY >= -30 && renderY < SCREEN_HEIGHT)
                {
                    render_text(secondHalf, static_cast<int>(SCREEN_WIDTH * 0.1), renderY, 0, 0, 0, 255, defaultFont);
                    renderY += 30; // Vertical spacing between lines
                }
            }
            else
            {
                render_text(line, static_cast<int>(SCREEN_WIDTH * 0.1), renderY, 0, 0, 0, 255, defaultFont);
                // Update render position for the next line of text
                renderY += 30; // Vertical spacing between lines
            }
        }
        else if (renderY >= SCREEN_HEIGHT)
        {
            // If the text goes beyond the screen, break the loop
            break;
        }
        else if (renderY < -30)
        {
            // Adjust renderY to prevent negative rendering
            renderY += 30;
        }
    }

    // Close the file
    sentence_file.close();
}

void draw_minimap()
{
}

void recreate_renderer()
{
    SDL_DestroyRenderer(renderer);
    if (vsyncEnabled)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }
}