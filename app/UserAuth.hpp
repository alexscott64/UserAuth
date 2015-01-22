/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 3 - Maps and Legends
Class           : ICS45C Fall 2014
File            : UserAuth.hpp
*/

#ifndef USERAUTH_HPP
#define USERAUTH_HPP

#include <string>
#include "HashMap.hpp"

class UserAuth{

// USER-FACING COMMANDS
public:
    UserAuth();
    ~UserAuth();

    bool createUser(const std::string& user, const std::string& password); // CREATE username password
    bool login(const std::string& user, const std::string& password); // LOGIN username password
    bool removeUser(const std::string& user); // REMOVE username
    void clearAll(); // CLEAR
    // the userExists() function calls contains() on hash map, this is used
    // for debugging clear all, and seeing if everything was actually removed
    bool userExists(const std::string& user) const;

private:
    HashMap* hm;
    std::string username;
    std::string password;
    bool checkPassword(const std::string& user, const std::string& givenPass) const;

// DEBUG MODE COMMANDS
// Check if the debug commands are valid inside the UserAuth class
public:
    void debugOn(); // DEBUG ON
    void debugOff(); // DEBUG OFF
    unsigned int loginCount() const; // LOGIN COUNT
    unsigned int getBucketCount() const; // BUCKET COUNT
    double getLoadFactor() const; // LOAD FACTOR
    unsigned int getMaxBucketSize() const; // MAX BUCKET SIZE
    bool getDebugStatus() const; // true if DEBUG ON, false if DEBUG OFF

private:
    bool isDebugOn; // should be initialized to false
};

#endif
