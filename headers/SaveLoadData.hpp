/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++17
    Purpose: Class Declaration file
    License: MIT License
*/



#pragma once

#include <iostream>
#include <sstream>
#include <vector>

/**
 * @brief class for adding custom file I/O functions to a program e.g, saving and loading game data
 * 
 * _________________________________________________________________________________________________
 * 
 *                                  SAVE LOAD DATA CLASS
 * _________________________________________________________________________________________________
 * 
 * 
 * DESCRIPTION
 * 
 * Static Class with functions to check if any data file exists and load to memory. Will also save
 * data to file.
 *
 * 
 * EXAMPLE
 * 
 * 1. To save settings call
 * 
 * SaveLoadData::save_settings(fileName, language);
 * 
 * 2. To load settings call
 * 
 * SaveLoadData::load_settings(fileName, language, unlockedAchievements);
 * 
 * 3. To save game call
 * 
 * SaveLoadData::save_file(fileName, language, unlockedAchievements);
 * 
 * 4. To load game call
 * 
 * SaveLoadData::load_file(fileName, language, unlockedAchievements);
 * 
 * 5. Check file exists
 * 
 * SaveLoadData::load_file(fileName, language, unlockedAchievements);
 * 
 * 6. Delete file
 * 
 * SaveLoadData::load_file(fileName);
 * 
*/
class SaveLoadData
{
private:
public:

/**
 * @brief save user set in program settings to file
 * 
 * save user set in program settings to file
 * 
 * @param fileName The name of the file to write to
 * @param language The language rendering of software on startup chosen from settings menu toggle to save to file
*/
  static void save_settings(const std::string &fileName, const std::string &language);

/**
 * @brief load user set in program settings to file
 * 
 * load user set in program settings to file
 * 
 * @param fileName The name of the file to load into software memory
 * @param language custom global variable that can be modified
 * @param unlockedAchievements custom global variable that can be modified
*/
  static void load_settings(const std::string &fileName, std::string &language, std::vector<int> &unlockedAchievements);

/**
 * @brief save user program data to file
 * 
 * save user program data to file
 * 
 * @param fileName The name of the file to write to
 * @param unlockedAchievements custom global variable that can be modified
*/
  static void save_file(const std::string &fileName, const std::vector<int> &unlockedAchievements);

/**
 * @brief load user program data from file
 * 
 * load user program data from file
 * 
 * @param fileName The name of the file to load into software memory
 * @param unlockedAchievements custom global variable that can be modified
*/
  static void load_file(const std::string &fileName, std::vector<int> &unlockedAchievements);

/**
 * @brief check if file exists on host platform/os
 * 
 * check if file exists on host platform/os
 * 
 * @param fileName The name of the file to check exists
*/
  static bool does_file_exist(const std::string &fileName);

/**
 * @brief delete a file on host platform/os
 * 
 * delete a file on host platform/os
 * 
 * @param fileName The name of the file to delete
*/
  static void delete_file(const std::string &fileName);
};
