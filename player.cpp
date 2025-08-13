#ifndef PLAYER
#define PLAYER

#include <iostream>
#include "item.cpp"
using namespace std;

//Player object class
//Holds info for health, stamina, inventory
class Player {
    //Variables
    int health;
    int maxHP;
    int stamina;
    int maxStamina;
    int block;
    Item* inventory[20];

public:

    Player() {
        maxHP = 20; health = maxHP; maxStamina = 3; stamina = maxStamina;
        for (int i = 0; i < 20; i++) {
            inventory[i] = new Item();
        }
        inventory[0] = new Item("Knife", 1, 10, true, false, true);
        inventory[1] = new Item("Small shield", 2, 10, false, false, true);
        inventory[2] = new Item("Ward Vial", 2, 2, false, true, false);
        //inventory[19] = new Item("Shhhh", 10, 100, true, true, false);
    }

    //Adds item to player inventory
    void ObtainItem(Item* item) {
        for (int i = 0; i < 20; i++) {
            if (inventory[i]->Empty()) {inventory[i] = item; return;}
        }
    }

    //Makes the player take damage
    //Removes block first, then health if block is 0
    //Returns true if health is zero and player dies
    bool LoseHealth(int damage) {
        if (damage < 0) {return false;}
        if (block > 0) {
            if (damage > block) {damage -= block; block = 0;}
            else {block -= damage; damage = 0;}
        }
        health -= damage;
        if (health <= 0) {return true;}
        else {return false;}
    }

    //Adds to the player's block
    void GainBlock(int blk) {block += blk;}

    void ResetStamina() {stamina = maxStamina;}
    void LoseStamina() {stamina--;}
    void LoseStamina(int val) {stamina -= val;}

    int GetHealth() {return health;}
    int GetMaxHP() {return maxHP;}
    int GetStamina() {return stamina;}
    int GetMaxStamina() {return maxStamina;}
    int GetBlock() {return block;}

    Item* GetItem(int i) {return inventory[i];}

    //Prints inventory line by line
    void printInventory() {
        for (int i = 0; i < 20; i++) {
            if (inventory[i]->Empty()) {continue;}
            cout << i + 1 << ") " << inventory[i]->toString() << "\n";
        }
    }

};

#endif