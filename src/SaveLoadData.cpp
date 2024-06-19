/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++17
    Purpose: Class Definition file
    License: MIT License
*/

#include "../headers/SaveLoadData.hpp"

#include <fstream>
#include <filesystem>


void SaveLoadData::save_settings(const std::string &fileName, const std::string &language)
{
    std::fstream file(fileName, std::ios::in | std::ios::out); // Open file for reading and writing
    if (!file)
    {
        std::cerr << "Error: Unable to open save file." << std::endl;
        return;
    }

    std::stringstream fileContents;
    fileContents << file.rdbuf(); // Read the entire file into a stringstream

    size_t pos_language = fileContents.str().find("Language: ");
    if (pos_language != std::string::npos)
    {
        size_t end_language = fileContents.str().find("\n", pos_language);
        fileContents.str().replace(pos_language, end_language - pos_language, "Language: " + language);
    }
    else
    {
        fileContents << "Language: " << language << '\n'; // Add language if not found
    }

    file.seekp(0);                // Move write position to the beginning of the file
    file << fileContents.rdbuf(); // Write modified contents back to the file
    file.close();
    std::cout << "Settings saved successfully" << std::endl;
}

void SaveLoadData::load_settings(const std::string &fileName, std::string &language, std::vector<int> &unlockedAchievements)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cerr << "Error: Unable to open save file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.find("Language: ") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string word;
            if (iss >> word)
            {
                language = word;
            }
        }
        else if (line.find("unlockedAchievements: ") != std::string::npos)
        {
            // Parse unlockedAchievements if needed
        }
    }
    std::cout << "Settings loaded successfully" << std::endl;
}

void SaveLoadData::save_file(const std::string &fileName, const std::vector<int> &unlockedAchievements)
{
    std::ofstream savefileObject(fileName, std::ios::app); // Open file for appending
    if (!savefileObject)
    {
        std::cerr << "Error: Unable to open save file." << std::endl;
        return;
    }

    savefileObject << "\nunlockedAchievements: ";
    for (size_t i = 0; i < unlockedAchievements.size(); ++i)
    {
        savefileObject << unlockedAchievements[i];
        if (i != unlockedAchievements.size() - 1)
        {
            savefileObject << ",";
        }
    }
    savefileObject << "\n";
    std::cout << "Game saved" << std::endl;
}

void SaveLoadData::load_file(const std::string &fileName, std::vector<int> &unlockedAchievements)
{
    std::ifstream savefileObject(fileName);
    if (!savefileObject)
    {
        std::cerr << "Error: Unable to open save file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(savefileObject, line))
    {
        if (line.find("unlockedAchievements: ") != std::string::npos)
        {
            std::istringstream iss(line.substr(line.find(":") + 1)); // Extract values after colon
            int achievement;
            while (iss >> achievement)
            {
                unlockedAchievements.push_back(achievement);
                if (iss.peek() == ',') // Skip comma
                    iss.ignore();
            }
        }
    }
    std::cout << "Game loaded" << std::endl;
}

bool SaveLoadData::does_file_exist(const std::string &fileName)
{
    return std::filesystem::exists(fileName);
}

void SaveLoadData::delete_file(const std::string &fileName)
{
    if (std::remove(fileName.c_str()) != 0)
    {
        std::cerr << "Error deleting file" << std::endl;
    }
    else
    {
        std::cout << "File successfully deleted" << std::endl;
    }
}
