/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 3 - Maps and Legends
Class           : ICS45C Fall 2014
File            : driver.cpp
*/

#include "driver.hpp"

void runDriver() {
    CommandParse user; // what ends up running
    bool quit = false; // indication of when we quit
    // run the main program here
    while(quit != true){

        std::string command; // command user enters
        getline(std::cin, command); // user input here
        user.inputCommand(command); // store the command
        // check for quit
        if(user.quitProgram(command) == true) {
            std::cout << "GOODBYE" << std::endl;
            quit = true;
        } // end if
    } // end while
} // end runDriver()
