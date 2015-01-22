/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 3 - Maps and Legends
Class           : ICS45C Fall 2014
File            : UserAuth.cpp
*/

#include <iostream>
#include "UserAuth.hpp"

UserAuth::UserAuth()
    : username{""}, password{""}, isDebugOn{false}
{
    hm = new HashMap(); // initialize hash map in constructor
}

UserAuth::~UserAuth()
{
    // deallocate the hash map
    delete hm;
}

// as a note, I dont believe I should implement a copy constructor or overloaded
// assignment operator. This is because UserAuth is not meant to be copied
// or assigned to another user authentication program. Instead it should only
// be initialized once (when we first start our program) and should store the
// information in the hashmap data structure

/* USER-FACING COMMANDS */

// create a username/password, store in hash map
bool UserAuth::createUser(const std::string& user, const std::string& password)
{
    if(hm->contains(user) == true){
        std::cout << "EXISTS" << std::endl;
        return false;
    } else {
        hm->add(user, password);
        std::cout << "CREATED" << std::endl;
        return true;
    }
}

bool UserAuth::login(const std::string& user, const std::string& password)
{
    // 1. check if username exists
    // 2. check if password is associated with username
    // if it works, output SUCCEEDED
    // otherwise, if either 1 or 2 fails, output FAILED
    if(hm->contains(user) != true) {
        std::cout << "FAILED" << std::endl;
        return false;
    }
    if(checkPassword(user, password) == false) {
        std::cout << "FAILED" << std::endl;
        return false;
    } else {
        std::cout << "SUCCEEDED" << std::endl;
        return true;
    }
}

bool UserAuth::removeUser(const std::string& user)
{
    if(hm->contains(user) == false) { // they don't exist
        std::cout << "NONEXISTENT" << std::endl;
        return false;
    } else {
        hm->remove(user);
        std::cout << "REMOVED" << std::endl;
        return true;
    }
}

void UserAuth::clearAll()
{
    hm->clearTable();
    std::cout << "CLEARED" << std::endl;
}

bool UserAuth::userExists(const std::string& user) const {
    if(hm->contains(user) == true) {
        return true;
    } else {
        return false;
    }
}

bool UserAuth::checkPassword(const std::string& user, const std::string& givenPass) const
{
    // Fix compiler warning for right now
    if(hm->value(user) != givenPass)
        return false;
    return true;
}

/* DEBUG COMMANDS */

// used by our Command Parse class
bool UserAuth::getDebugStatus() const
{
    if(isDebugOn == true)
        return true;
    else
        return false;
}

void UserAuth::debugOn()
{
    if(isDebugOn == true) {
        std::cout << "ON ALREADY" << std::endl;
    } else if(isDebugOn == false) {
        std::cout << "ON NOW" << std::endl;
        isDebugOn = true;
    }
}

void UserAuth::debugOff()
{
    if(isDebugOn == true) {
        std::cout << "OFF NOW" << std::endl;
        isDebugOn = false;
    } else if(isDebugOn == false) {
        std::cout << "OFF ALREADY" << std::endl;
    }
}

unsigned int UserAuth::loginCount() const // amt of user/pw combinations
{
    return hm->size();
}

unsigned int UserAuth::getBucketCount() const // amount of buckets in hash table
{
    return hm->bucketCount();
}

double UserAuth::getLoadFactor() const // load factor of hash table
{
    return hm->loadFactor();
}

unsigned int UserAuth::getMaxBucketSize() const // list that has most buckets
{
    return hm->maxBucketSize();
}
