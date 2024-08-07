/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License
*/

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#pragma once

#include <iostream>
#include <string>
#ifdef _WIN32
// #include <winsock2.h> already included from <boost/asio.hpp> so no need to include winsock twice
#else
#include <arpa/inet.h> // not included within <boost/asio.hpp> so necessary to include
#include <netinet/in.h> // not included within <boost/asio.hpp> so necessary to include
#endif
#include <boost/asio.hpp>
#include "Entity.hpp"
#include "WebserverHost.hpp"

/**
 * @brief Webserver Client class for game multiplayer
 *
 * Websocket functions for
 * 1. POST create account/login details await response from game website e.g, www.agnisamooh.com
 * 2. GET/POST Multiplayer details e.g. available games, friends. You can
 * create games, and join statefull games by quering the multiplayer game server e.g, AWS EC2 Ubuntu instance
 * connects to the associated files
 * Declarations: ./headers/WebserverHost.hpp - Cloud Instance multiplayer server to pass game state
 * Definitions: ./src/WebserverHost.cpp - Cloud Instance multiplayer server to pass game state
 * Declarations: ./headers/WebserverClient.hpp - this file declarations
 * Definitions: ./src/WebserverClient.cpp - this file definitions
 *
 *
 * REQUIREMENTS
 *
 * Boost is a framework of individual volunteers contributing their own libraries to expand
 * c++ as the stl is not good enough. e.g. C++23 still has no networking so some volunteers
 * created their own libraries to fill the gap e.g,
 * Boost.ASIO - for low level networking
 * Boost.Beast - for high level websocket networking
 *
 * To build, include, ling and setup Boost and it's following libraries e.g. Boost.ASIO follow
 * the steps below. The example demonstration shows building a simple REGEX BOOST software. Once working
 * simply swap out the lib with the boost.ASIO lib
 *
 * 1. Download the latest version of Boost to program files: https://www.boost.org/users/download/
 * 2. cd "C :\Program Files\boost"
 * 3. . \ bootstrap.bat --with-python="C :\Python\python.exe" --with-toolset=mingw
 * 4. . \ b2 toolset=gcc
 * 5. search the contents of the below lib folder to find the exact library you need for your compiler. Note mt is the release version
 * choose this if you're unsure. And remove the "lib" and ".a" from the front and back of the lib when linking see the args for the example
 * ls "C :/Program Files/boost/stage/lib"
 * > libboost_regex-mgw13-mt-x64-1_85.a
 * therefore use: "-lboost_regex-mgw13-mt-x64-1_85"
 * For VScode tasks.json add the below args. Note: boost.asio uses: system e.g, libboost_system-mgw13-mt-x64-1_85.a
 * "args": [
 *              "-fdiagnostics-color=always",
 *              "-I C:/Program Files/boost",
 *              "-g",
 *              "${file}",
 *              "-o",
 *              "${fileDirname}/${fileBasenameNoExtension}.exe",
 *              "-LC :/Program Files/boost/stage/lib",
 *              "-lboost_regex-mgw13-mt-x64-1_85"
 *         ],
 * 7. Include the required headers
 * include <boost/regex.hpp>
 * 8. Build and Run sample code below to test it's all working
 * include <boost/regex.hpp>
 * include < iostream>
 * include < string>
 * # ifdef _WIN32
 * include <winsock2.h>
 * # else
 * include <arpa/inet.h>
 * include <netinet/in.h>
 * # endif
 *
 * int main() {
 *  // The string to search
 *  std::string text = "Hello, world! This is an example string.";
 *
 *  // The regular expression pattern
 *  boost::regex pattern("\\bexample\\b");
 *
 *  // Search for the pattern in the text
 *  boost::smatch matches;
 *  if (boost::regex_search(text, matches, pattern)) {
 *      std::cout << "Found the word 'example' at position " << matches.position() << std::endl;
 *  } else {
 *      std::cout << "The word 'example' was not found." << std::endl;
 *  }
 *
 *  return 0;
 * }
 *
 *
 * EXAMPLE
 *
 * 1. Construct the class object
 *
 */
class WebserverClient
{
private:
    bool successResponse{};                              /**< Response from webserver */
    std::string queryURL{};                              /**< the url to query e.g. www.example.com */
    std::string queryProtocol{};                         /**< the protocol to follow url query e.g. http*/
    boost::asio::io_context io_context{};                /**< provides a context for I/O services e.g. sockets, timers, asynchronous functions */
    boost::asio::ip::tcp::resolver resolver{io_context}; /**< resolve string address to endpoints. Same as a DNS/Domain name server */
    boost::asio::ip::tcp::socket socket{io_context};     /**< socket for server being queried. Resolver passes the webaddress to use */
public:
    /**
     * @brief WebserverClient constructor
     *
     * EXAMPLE
     *
     * 1. query (similar to curl) example.com website to get response
     *
     * WebserverClient webserverClient("www.example.com", "http");
     */
    WebserverClient()
    {
        std::cout << "Constructed: WebserverClient" << std::endl;
    }
    /**
     * @brief WebserverClient deconstructor
     */
    ~WebserverClient()
    {
        std::cout << "Deconstructed: WebserverClient" << std::endl;
    }

    /** 
     * @brief return response success bool triggered from this class functions e.g. create_account succeeded
     * */
    bool response_success() const {
        return successResponse;
    }

    /**
     * @brief complete POST and create await thread to read response
     *
     *
     * POST create account details. Thread is created to listen for response. Control is given
     * back to program (asynchronous), when response recieved callback is triggered
     * e.g. you will be notified account login successfull
     *
     *
     * EXAMPLE
     *
     * webserverClient.login_account(username, email, password);
     *
     */
    void login_account(std::string username, std::string password)
    {
        try
        {
            // Form data
            std::string queryURL = "agnisamooh.com";
            std::string queryProtocol = "http";

            // Form request payload
            std::string POSTData = "login-username=" + username +
                                   "&login-password=" + password;

            // Create request
            std::string request = "POST /website/signup.html HTTP/1.1\r\n"
                                  "Host: agnisamooh.com\r\n"
                                  "Content-Type: application/x-www-form-urlencoded\r\n"
                                  "Content-Length: " +
                                  std::to_string(POSTData.length()) + "\r\n\r\n" +
                                  POSTData;

            // Connect to endpoint
            boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(queryURL, queryProtocol);
            boost::asio::connect(socket, endpoints);

            // Send the request
            boost::asio::write(socket, boost::asio::buffer(request.data(), request.size()));

            // Read the response
            boost::asio::streambuf response;
            boost::asio::read_until(socket, response, "\r\n");

            // Output the response
            std::istream responseStream(&response);
            std::string httpVersion{};
            responseStream >> httpVersion;
            int statusCode{};
            responseStream >> statusCode;
            std::string statusMessage{};
            std::getline(responseStream, statusMessage);
            if (!responseStream || httpVersion.substr(0, 5) != "HTTP/")
            {
                std::cerr << "Error: Invalid server response" << std::endl;
                return;
            }
            if (statusCode != 200)
            {
                std::cerr << "Error: Incorrect response code " << statusCode << std::endl;
                return;
            }

            // Search for the word "pass" or "fail" in the response line by line
            std::string line;
            bool success = false;
            while (std::getline(responseStream, line))
            {
                std::cout << line << std::endl; // Print the response line
                if (line.find("pass") != std::string::npos)
                {
                    successResponse = true; 
                    break;
                }
                else if (line.find("fail") != std::string::npos)
                {
                    successResponse = false;
                    break;
                }
            }
            socket.close();
        }
        catch (std::exception &e)
        {
            std::cerr << "Error: Exception: " << e.what() << std::endl;
        }
    }

    /**
     * @brief complete POST and create await thread to read response
     *
     *
     * POST create account details. Thread is created to listen for response. Control is given
     * back to program (asynchronous), when response recieved callback is triggered
     * e.g. you will be notified account created successfull, then proceed to be able to login
     *
     *
     * EXAMPLE
     *
     * webserverClient.create_account(username, email, password);
     *
     */
    void create_account(std::string username, std::string email, std::string password)
    {
        try
        {
            // Form data
            std::string queryURL = "agnisamooh.com";
            std::string queryProtocol = "http";

            // Form request payload
            std::string POSTData = "register-username=" + username +
                                   "&register-email=" + email +
                                   "&register-password=" + password;

            // Create request
            std::string request = "POST /website/signup.html HTTP/1.1\r\n"
                                  "Host: agnisamooh.com\r\n"
                                  "Content-Type: application/x-www-form-urlencoded\r\n"
                                  "Content-Length: " +
                                  std::to_string(POSTData.length()) + "\r\n\r\n" +
                                  POSTData;

            // Connect to endpoint
            boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(queryURL, queryProtocol);
            boost::asio::connect(socket, endpoints);

            // Send the request
            boost::asio::write(socket, boost::asio::buffer(request.data(), request.size()));

            // Read the response
            boost::asio::streambuf response;
            boost::asio::read_until(socket, response, "\r\n");

            // Output the response
            std::istream responseStream(&response);
            std::string httpVersion{};
            responseStream >> httpVersion;
            int statusCode{};
            responseStream >> statusCode;
            std::string statusMessage{};
            std::getline(responseStream, statusMessage);
            if (!responseStream || httpVersion.substr(0, 5) != "HTTP/")
            {
                std::cerr << "Error: Invalid server response" << std::endl;
                return;
            }
            if (statusCode != 200)
            {
                std::cerr << "Error: Incorrect response code " << statusCode << std::endl;
                return;
            }

            // Search for the word "pass" or "fail" in the response line by line
            std::string line;
            bool success = false;
            while (std::getline(responseStream, line))
            {
                std::cout << line << std::endl; // Print the response line
                if (line.find("pass") != std::string::npos)
                {
                    successResponse = true; 
                    break;
                }
                else if (line.find("fail") != std::string::npos)
                {
                    successResponse = false;
                    break;
                }
            }
            socket.close();
        }
        catch (std::exception &e)
        {
            std::cerr << "Error: Exception: " << e.what() << std::endl;
        }
    }

    /**
     * @brief POST serialised data to webserver
     * @param entities the serialised entity vector from client
    */
    void POST_entity_vector_to_server(WebserverHost &webserverHostContext, std::vector<Entity *> entities)
    {
        webserverHostContext.webserver_process_entity_vector(entities);
    }
    /**
     * @brief POST serialised data to webserver
     * @param entities the serialised entity vector from client
    */
    void POST_player_movement(int playerID, int x, int y, const std::string &direction, WebserverHost &webserverHostContext)
    {
        webserverHostContext.webserver_process_player_handle(playerID, x, y, direction);
    }
    /**
     * @brief POST serialised data to webserver
     * @param entities the serialised entity vector from client
    */
    void POST_bot_movement(int playerID, int x, int y, const std::string &direction, WebserverHost &webserverHostContext)
    {
        webserverHostContext.webserver_process_player_handle(playerID, x, y, direction);
    }
    /**
     * @brief in game engine/sdl update loop call this if multiplayer game to sync
     * entities vector with webservers serverEntitites vector
    */
    void GET_network_messages(std::vector<Entity *> &entities, WebserverHost &webserverHostContext)
    {
        entities = webserverHostContext.get_entities();
    }
};

#pragma clang diagnostic pop