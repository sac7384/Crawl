#ifndef GAME
#define GAME

#include <random>
#include <iostream>
#include "player.cpp"
#include "battle.cpp"
using namespace std;

//Game class
//Runs each game of Crawl
//Holds instances of player, item, and monster classes
class Game {
    //Objects
    Player* player; //Player, stats, inventory of items
    Monster* monsterArray[]; //Holds monsters to be passed to Battle class
    //Areas, lists of monsters, possible items, possible events

    //Variables
    //int difficulty; //

public:
    Game() {
        //Local variables
        char input; int counter = 1;
        int low; int high;
        bool running = true;
        player = new Player();
        //Random number generator
        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> dist(0, 100);

        while (running) {
            cout << "\nStart battle " << counter << "?\n";
            cin >> input;
            if (input == 'n') {running = false; continue;}

            cout << "Starting battle " << counter << "\n\n";
            //Choosing monsters
            int temp;
            for (int i = 0; i < 3; i++) {
                temp = dist(mt) % counter + 1;
                cout << temp << "\n";
                //Zombie starts round 10
                if (temp >= 10) {
                    monsterArray[i] = new Monster("Zombie", dist(mt) % 10 + 4, new Item("Rotten Claws", 3, 100, true, false, true), new Item("Infected Bite", 2, 100, true, false, true), new Item("Stoneskin Potion", 5, 2, false, true, false));
                    //Zombie can drop - stoneskin potion (2)
                    monsterArray[i]->SetOneDroppedItem(2);
                }
                //Cultist starts round 4
                else if (temp >= 4) {
                    monsterArray[i] = new Monster("Cultist Mage", dist(mt) % 3 + 4, new Item("Frostbite tome", 2, 5, true, true, false), new Item("Shield Scroll", 4, 1, false, true, false), new Item("Firebolt", 1, 10, true, true, true));
                    //Cultist Mage can drop - frost tome, shield scroll (0, 1)
                    monsterArray[i]->SetOneDroppedItem(dist(mt) % 2);
                }
                //Skeleton starts round 2
                else if (temp >=2) {
                    monsterArray[i] = new Monster("Skeleton", dist(mt) % 2 + 2, new Item("Sword", 2, 5, true, false, true), new Item("Buckler", 2, 5, false, false, true), new Item("Bomb", 5, 1, true, false, true));
                    //Skeleton can drop - sword, buckler, bomb
                    monsterArray[i]->SetOneDroppedItem(dist(mt) % 3);
                }
                //Gooberlin starts round 1
                else {
                    monsterArray[i] = new Monster("Gooberlin", dist(mt) % 2 + 1, new Item("Sharp Rock", 1, 2, true, false, true), new Item("Broken Spear", 1, 5, true, false, true), new Item("Firecracker", 2, 2, true, false, true));
                    //Gooberlin can drop - sharp rock, broken spear, firecracker
                    monsterArray[i]->SetOneDroppedItem(dist(mt) % 3);
                }
            }

            Battle* battle = new Battle(player, monsterArray);
            if (player->GetHealth() < 1) {cout << "You died and lost battle " << counter << "!\n"; running = false;}
            else {cout << "You won the battle!\n";}
            counter++;
        }
    }//End of constructor
};

#endif