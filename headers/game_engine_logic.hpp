/*
    Author: Sumeet Singh
    Dated: 28/05/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

#pragma once

#include <iostream>
#include <string>
#include "globals.hpp"

/**
 * @brief Add timer to program
 *
 * Functions to integrate a timer countdown in your program. It can be drawn to screen or cout.
 * Creates individual threads for every scene which use the global variables countdownSeconds and startTimer
 * to turn off/reset/turn on
 *
 *         EXAMPLE
* 1. Initialise global variables
* bool startTimer = false;
* bool countdownSeconds = 300;
*
* 2. Add draw function
*
* You can customise to output anywhere you like example shows to SDL render text to screen
* void draw_timer()
* {
*     SDL_Rect timerRect = {static_cast<int>(SCREEN_WIDTH * 0.05), static_cast<int>(SCREEN_HEIGHT * 0.03), (SCREEN_WIDTH / 5), (SCREEN_HEIGHT / 8)};
*     SDL_RenderCopy(renderer, timerTexture, nullptr, &timerRect);
*
*     int minutes = countdownSeconds / 60;
*     int seconds = countdownSeconds % 60;
*
*     // If minutes or seconds < 10, it will add an 0 e.g. 120 seconds = 2. As 2 < 10, final output: 02:00
*     std::string timerText = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
*
*     render_text(timerText, timerRect.x + 80, timerRect.y + 30, 0, 0, 0, 255, defaultFont);
* }
*
* 3. Start timer
*
startTimer = true;
* toggle_countdown();
* Stop timer
* startTimer = false;
* toggle_countdown();
*
* 4. Restart timer
*
* startTimer = false;
* toggle_countdown();
* countdownSeconds = 300;
* // IMPORTANT include delay to allow threads to syncronise
* startTimer = true;
* toggle_countdown();

*/
void toggle_countdown();
/**
 * @brief calculate current time when called
 *
 * Use std::chrono to get a string of current time for timestamping e.g. logs
 *
 * @return current time in HH:MM:SS DD/MM/YY format
 */
std::string get_datetime();
/**
 * @brief post Score to webserver
 *
 * Use JSON to send a Score struct to webserver to update online Scoreboards
 */
void POST_player_scores_to_webserver(const Score &s);
/**
 * @brief Initialise Score on game end
 *
 * To enable Scorekeeping for a software where the index doesn't matter a struct can be constructed to hold
 * values about statistics/gameplay in order to print out through itteration.
 *
 * 1. Create a Score struct
 * struct Score
 * {
 * std::string name;
 * int Score;
 * std::string datetime;
 * };
 *
 * 2. Create a Scores vector:
 *
 * std::vector<Score> Scores;
 *
 * 3. on update() gameover go scene 4
 *
 * 4. On Scene 4 update, check if scene4 submit button is true (that inputbutton has text) then call initialise_Score(Scores)
 *
 * 5. initialise_Score(Scores) will get player object name and Score and initialise datetime value with get_datetime()
 * then pushback to Scores vector
 *
 * 6. Draw the Scores e.g.
 *
 * draw_Scores(Scores);
 */
void initialise_score();
/**
 * @brief sort 2 values in decending order
 *
 * Used to sort Score struct in decending order std::vector<Score> Scores;
 *
 * @param a value 1 to compare
 * @param b value 2 to compare
 * @return results of which value is greater then the other
 */
bool compare_Scores(const Score &a, const Score &b);
/**
 * @brief Find OS
 *
 * Uses SDL framework to find the underlying platform OS used for
 * specific OS functions
 *
 * @return string with OS name
 */
std::string find_os();
/**
 * @brief Output txt file text to window
 *
 * Pass a filename which will then output the text contents to screen for user
 * to read contents
 *
 * @param fileToOutput the filename to read and output to screen
 */
void draw_file_contents_to_screen(const std::string &fileToOutput);
/**
 * @brief Game Map | Minimap
 * https://lazyfoo.net/tutorials/SDL/09_the_viewport/index.php
 */
void draw_minimap();
/**
 * @brief recreate renderer for vsync enabling/disabling settings toggle
 */
void recreate_renderer();
