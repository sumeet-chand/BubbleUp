/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Class Definition file
    License: MIT License
*/

#include "../headers/ParticleGenerator.hpp"

ParticleGenerator::ParticleGenerator(int xPos, int yPos, std::string animation) : xPos(xPos), yPos(yPos), animation(animation)
{
    // Creation logic for item entities
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random velocity
    std::uniform_int_distribution<int> xDistribution(-2, 2);  // For x velocity -2, -1, 0, 1, 2
    std::uniform_int_distribution<int> yDistribution(-9, -5); // For y velocity -9, -8, -7, -6, -5

    vx = xDistribution(gen);
    vy = yDistribution(gen);

    if (animation == "fireworks")
    {
        // draw fireworks
        std::uniform_int_distribution<int> colorDistribution(0, 255);
        r = colorDistribution(gen);
        g = colorDistribution(gen);
        b = colorDistribution(gen);
        a = colorDistribution(gen);
    }

    if (animation == "water")
    {
        // draw different water particle colours
        std::uniform_int_distribution<int> colorDistribution(0, 255);
        int random = colorDistribution(gen) % 2;
        if (random == 0)
        {
            // add blue water particles
            b = colorDistribution(gen);
            a = colorDistribution(gen);
        }
        else
        {
            // add some white colours to water
            b = 255;
            r = 255;
            g = 255;
            a = colorDistribution(gen);
        }
    }

    if (animation == "fire")
    {
        // draw different fire particle colours
        std::uniform_int_distribution<int> colorDistribution(0, 255);
        int random = colorDistribution(gen) % 2;
        if (random == 0)
        {
            // add red flame particles
            r = colorDistribution(gen);
            a = colorDistribution(gen);
        }
        else
        {
            // add some yellow colours to flame
            r = 255;
            g = 255;
            a = 128 + colorDistribution(gen) % 128;
        }
    }
}

void ParticleGenerator::update()
{
    // Update position based on velocity
    xPos += vx;
    yPos += vy;

    // Apply gravity
    vy += 1;
}

void ParticleGenerator::render_particles(std::vector<ParticleGenerator> &particles, SDL_Renderer *renderer)
{
    for (auto &particle : particles)
    {
        particle.update();
        SDL_SetRenderDrawColor(renderer, particle.r, particle.g, particle.b, particle.a);
        SDL_Rect rect = {particle.xPos, particle.yPos, 3, 3}; // Increase size here
        SDL_RenderFillRect(renderer, &rect);
    }
}

void ParticleGenerator::clear_particles(std::vector<ParticleGenerator> &particles, int SCREEN_HEIGHT)
{
    for (auto it = particles.begin(); it != particles.end();)
    {
        if (it->yPos > SCREEN_HEIGHT)
        {
            it = particles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
