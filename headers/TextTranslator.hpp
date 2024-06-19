/*
    Author: Sumeet Singh
    Dated: 02/05/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

/**
 * @brief uses gettext library to create translations for text rendering
 * 
 * EXAMPLE
 * to use first use a special macro in front of all rendered text
*/

#pragma once

#include <iostream>

class TextTranslator
{
private:
public:
    /**
     * @brief Constructor for TextTranslator
     */
    TextTranslator()
    {
        std::cout << "Constructed: TextTranslator" << std::endl;
    }

    /**
     * @brief Destructor for TextTranslator
     */
    ~TextTranslator()
    {
        std::cout << "Destroyed: TextTranslator" << std::endl;
    }
};
