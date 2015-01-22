/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 3 - Maps and Legends
Class           : ICS45C Fall 2014
File            : CommandParse.hpp
*/
#ifndef COMMANDPARSE_HPP
#define COMMANDPARSE_HPP

#include <string>
#include <sstream>
#include "UserAuth.hpp"

// This class takes in a line of text via getline, parses it and checks if it is
// a valid command.
// If the command IS valid, we see if it is "user-facing" or a "debug" command

// Once we find which command it is, we pass each string value through the relevant
// function in the relevant class

// Side note: We NEED to create some special cases
// For example "LOGIN COUNT password" should call the user-facing command as long
// as there is nothing after password. If we have "LOGIN COUNT" this is a debug
// command, and we should call the function there.

class CommandParse {

public:
    // constructor lets us use the functions
    CommandParse();
    ~CommandParse(); // destructor de-allocates User Auth service

    void inputCommand(const std::string& fullCommand); // take in an entire line of input
    bool quitProgram(const std::string& command) const;

private:
    UserAuth* ua;

    bool isValidUserCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const; // checks if the user-facing command is valid
    bool isValidDebugCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const; // checks if the debug command is valid
    void getUserCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const;
    void getDebugCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const;
    void getCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const;

};

#endif
