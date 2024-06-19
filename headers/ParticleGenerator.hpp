/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

#pragma once
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
/**
 * @brief Particle graphic render effect
 *
 * You can use this in any software e.g, game to draw particle effects such as treading on water,
 * lava from volcanoes, clouds, stars, or any image that you can represent with dots
 *
 * EXAMPLE
 *
 * 1. Create a vector to hold all the particles
 * std::vector<ParticleGenerator> particles{};
 *
 * 2. In a event e.g. Mouse handle click pass a preconfigured animation in the 3rd parameter
 * fireworks = random colours and transparency levels e.g. a firework
 * water = Water effects e.g. water splashes
 * fire = fire effects e.g. candle flame
 *
 * int random = (rand() % 50) + 5;
 * for (int i = 0; i < random; ++i)
 * {
 *     particles.push_back(Particle(mouseX, mouseY, "fire"));
 * }
 *
 * 3. In your rendering e.g. draw() draw the particles vector
 * ParticleGenerator::render_particles(particles, renderer);
 *
 * 4. (Optional) Clear particles on exit depending on how you setup your camera/particles vector scope
 * ParticleGenerator::clear_particles(particles, SCREEN_HEIGHT);
 *
 */
class ParticleGenerator
{
public:
    int xPos{};              /**< Particle x-axis position */
    int yPos{};              /**< Particle y-axis position */
    int vx{};                /**< Velocity of particle */
    int vy{};                /**< Velocity of particle */
    int r{};                 /**< Particle red color */
    int g{};                 /**< Particle green color */
    int b{};                 /**< Particle blue color */
    int a{};                 /**< Particle alpha transparency level 255 is solid 0 is transparent */
    std::string animation{}; /**< preconfigured particle colours textures you want to draw e.g. random, water, fire */

    /**
     * @brief Particle default constructor
     */
    ParticleGenerator(int xPos, int yPos, std::string animation);

    /**
     * @brief Update particle position
    */
    void update();

    /**
     * @brief render the particles
     * @param particles the particles vector
     * @param renderer the reference to the renderer to draw on
     */
    static void render_particles(std::vector<ParticleGenerator> &particles, SDL_Renderer *renderer);

    /**
     * @brief clear particles vector by removing if objects go out of camera view
     *
     * Clearing particles vector prematurely in draw will prevent full animation so in order
     * to clear the particles vector periodically and before final cleanup call this functino
     * after render_particles()
     * Only renders what you can visualise by deleting all the pixels that move out of the screens width
     *
     * @param particles the global vector holding all particles
     * @param SCREEN_HEIGHT to be changed to camera view for rending only whats in scren
     */
    static void clear_particles(std::vector<ParticleGenerator> &particles, int SCREEN_HEIGHT);
};
