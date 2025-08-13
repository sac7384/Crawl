#ifndef CRAWL
#define CRAWL

#include <iostream>
#include "game.cpp"
using namespace std;

//Main cpp file
//Holds main menu and settings
int main() {
    bool running = true;
    int input;
    Game* game;

    cout << "Hello! Welcome to Crawl, a endless dungeon crawl game.\n";
    cout << "Check out the tutorial if you're new, or jump right in if you know what you're doing!\n";

    while (running) {
        cout << "\nEnter a number to navigate the menu\n";
        cout << "1) Start New Run\n2) Tutorial\n3) Settings\n4) Exit\nInput: ";
        cin >> input;
        switch (input) {
            case 1:
                game = new Game();
                break;
            case 2:
                cout << "Sorry there is no tutorial right now!\n";
                break;
            case 3:
                cout << "Sorry there is no settings menu right now!\n";
                break;
            case 4:
                return 0;
        }
    }
    return 0;
}

#endif