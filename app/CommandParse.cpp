/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 3 - Maps and Legends
Class           : ICS45C Fall 2014
File            : CommandParse.cpp
*/

#include <iostream>
#include "CommandParse.hpp"
#include "UserAuth.hpp"

namespace {

    // methods that validate strings before parsing them into istringstream
    // check if the user just entered spaces or newline as input (ie. they didn't enter a space)
    // If the user hits enter, getline discards the \n character, meaning amount of spaces is 0
    // and our string length is 0.
    // true means everything is entered as spaces or a newline
    // false means we have actual letters
    bool validateString(const std::string& input) {
        unsigned int amountOfSpaces = 0;
        for(unsigned int i = 0; i < input.length(); i++) {
            if(isspace(input.at(i))) // check at each char if its a space
                amountOfSpaces++; // increment the amount we have
        }
        return (input.length() == amountOfSpaces);
    }
}

CommandParse::CommandParse()
{
    ua = new UserAuth();
}

CommandParse::~CommandParse()
{
    // deallocate the user authentication service
    delete ua;
}

// input a full line of text in here
// parse it and preform basic tests on it
// 1. if fullCommand < zero words, return INVALID
// 2. if fullCommand > three words, return INVALID
// put it through another function to correctly get the command
void CommandParse::inputCommand(const std::string& fullCommand)
{
    if(validateString(fullCommand) == true) {
        std::cout << "INVALID" << std::endl;
        return;
    }

    std::string tempCheck; // if we have a value in here other than empty, invalid
    // use istringstream to grab the words, max of 3
    std::istringstream parse{fullCommand}; // parse command into words

    std::string command, actionOne, actionTwo;
    parse >> command; // stores first word (the command)
    parse >> actionOne; // stores second word as parameter
    parse >> actionTwo; // stores third word as parameter
    parse >> tempCheck;

    if(!tempCheck.empty()) { // if we have more than 3 words total
        std::cout << "INVALID" << std::endl;
        return;
    }
    // get correct command & apply
    getCommand(command, actionOne, actionTwo);
}

void CommandParse::getCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const
{
    // if we want a user-facing command
    if((isValidUserCommand(command, actionOne, actionTwo) == true) && (isValidDebugCommand(command, actionOne, actionTwo) == false)) {
        // assume input is valid
        getUserCommand(command, actionOne, actionTwo);
    } else if((isValidUserCommand(command, actionOne, actionTwo) == false) && (isValidDebugCommand(command, actionOne, actionTwo) == true)) {
        // assume input is valid
        getDebugCommand(command, actionOne, actionTwo);
    } else {
        std::cout << "INVALID" << std::endl;
    }
}

// since we passed the isValid, assumed we can do the action
void CommandParse::getUserCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const
{
    if(command == "CREATE") { // call create user
        ua->createUser(actionOne, actionTwo);
    } else if(command == "LOGIN") {
        ua->login(actionOne, actionTwo);
    } else if(command == "REMOVE") {
        ua->removeUser(actionOne);
    } else if(command == "CLEAR") {
        ua->clearAll();
    }
}

// assume we have valid input
void CommandParse::getDebugCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const
{
    if(ua->getDebugStatus() == true) { // valid to do these things
        if((command == "DEBUG") && (actionOne == "ON")) {
            ua->debugOn(); // on again
        } else if((command == "DEBUG") && (actionOne == "OFF")) {
            ua->debugOff();
        } else if((command == "LOGIN") && (actionOne == "COUNT")) {
            std::cout << ua->loginCount() << std::endl;
        } else if((command == "BUCKET") && (actionOne == "COUNT")) {
            std::cout << ua->getBucketCount() << std::endl;
        } else if((command == "LOAD") && (actionOne == "FACTOR")) {
            std::cout << ua->getLoadFactor() << std::endl;
        } else if((command == "MAX") && (actionOne == "BUCKET") && (actionTwo == "SIZE")) {
            std::cout << ua->getMaxBucketSize() << std::endl;
        }
    } else if((ua->getDebugStatus() == false) && (command == "DEBUG") && (actionOne == "ON")) { // if debug is off
        ua->debugOn();
    } else if((ua->getDebugStatus() == false) && (command == "DEBUG") && (actionOne == "OFF")) { // debug is already off
        ua->debugOff();
    } else {
        std::cout << "INVALID" << std::endl;
    }
}

// we use this in isValidCommand
// helper functions to parse commands
// check for valid commands and return true
// otherwise return false
bool CommandParse::isValidUserCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const
{

    if((command == "CREATE") && ((!actionOne.empty() && actionOne != "COUNT")) && (!actionTwo.empty())) { // CREATE
        return true;
    } else if ((command == "LOGIN") && (actionOne != "COUNT") && (!actionOne.empty()) && (!actionTwo.empty())) { // LOGIN
        return true;
    } else if ((command == "REMOVE") && (!actionOne.empty()) && (actionTwo.empty())) { // REMOVE
        return true;
    } else if ((command == "CLEAR") && (actionOne.empty()) && (actionTwo.empty())) { // CLEAR
        return true;
    } else if ((command == "QUIT") && (actionOne.empty()) && (actionTwo.empty())) { // QUIT
        return true;
    } else {
        return false;
    }
}

bool CommandParse::isValidDebugCommand(const std::string& command, const std::string& actionOne, const std::string& actionTwo) const {
    if((command == "DEBUG") && (actionOne == "ON") && (actionTwo.empty())) { // DEBUG ON
        return true;
    } else if((command == "DEBUG") && (actionOne == "OFF") && (actionTwo.empty())) { // DEBUG OFF
        return true;
    } else if((command == "LOGIN") && (actionOne == "COUNT") && (actionTwo.empty())) { // LOGIN COUNT
        return true;
    } else if((command == "BUCKET") && (actionOne == "COUNT") && (actionTwo.empty())) { // BUCKET COUNT
        return true;
    } else if((command == "LOAD") && (actionOne == "FACTOR") && (actionTwo.empty())) { // LOAD FACTOR
        return true;
    } else if((command == "MAX") && (actionOne == "BUCKET") && (actionTwo == "SIZE")) { // MAX BUCKET SIZE
        return true;
    }
    return false;
}

/* Special cases: QUIT */
bool CommandParse::quitProgram(const std::string& command) const {
    return (command == "QUIT");
}
