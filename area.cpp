#ifndef CRAWL
#define CRAWL

#include <iostream>
#include "item.cpp"
#include "monster.cpp"
using namespace std;

class Area {
    //Variables
    string name;
    int numberOfRooms;
    string* areasFound;
    bool newArea;

    //Text blocks
    string entranceText;
    string battleText;
    string treasureText;

    //Encounter arrays

public:
    Area() {
        areasFound = new string[20];
    }

    //Initializes all variables to those of the desired area
    //Input is the name of the area
    //Assigning functions are at bottom of class
    bool NewArea(string id, int rooms) {
        newArea = true;
        if (id == "Gooberlin Camp") {GooberlinCamp();}
        else if (id == "") {}
        else {return false;}
        name = id;
        numberOfRooms = rooms;
        //Add to areasFound if it is new
        for (int i = 0; i < areasFound->length(); i++) {
            if (areasFound[i] == id) {newArea = false; break;}
            else if (areasFound[i].length() < 1) {areasFound[i] = id; break;}
        }
        return true;
    }

private:
    ///Assigning functions

    void GooberlinCamp() {

    }
};

#endif