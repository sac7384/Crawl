#ifndef MONSTER
#define MONSTER

#include <iostream>
#include "item.cpp"
using namespace std;

class Monster {
    //Stats
    string name;
    int maxHP; int health; int block;

    //Gear and abilities
    Item* inventory[3]; int dropItem;
    int intent; int attack; int magic; int defend;

public:
    //Empty monster constructor
    Monster() {
        srand(time(0));
        name = ""; maxHP = -1; health = -1;
        inventory[0] = new Item(); inventory[1] = new Item(); inventory[2] = new Item(); dropItem = -1;
        block = 0; attack = 0; magic = 0; defend = 0;
    }

    //Monster constructor
    //Name, max hp, inv1, inv2
    Monster(string n, int hp, Item* one, Item* two, Item* three) {
        srand(time(0));
        name = n; maxHP = hp; health = maxHP;
        inventory[0] = one; inventory[1] = two; inventory[2] = three;
        block = 0; attack = 0; magic = 0; defend = 0;
    }

    //Changes intent of the monster
    //Updates intent values based on new item (attack, magic, defend)
    void NewIntent(int rand) {
        if (!Real() || !Alive()) {return;}
        //Reset values and choose a valid item
        attack = 0; magic = 0; defend = 0;
        intent = rand;
        if (inventory[intent]->Empty()) {intent++; if (intent >= 3) {intent = 0;}}
        if (inventory[intent]->Empty()) {intent++; if (intent >= 3) {intent = 0;}}
        if (inventory[intent]->Empty()) {return;}
        //Update new values
        if (inventory[intent]->IsWeapon()) {
            if (!inventory[intent]->IsMagic()) {attack = inventory[intent]->GetValue();}
            else {magic = inventory[intent]->GetValue();}
        }
        else {defend = inventory[intent]->GetValue();}
    }

    //Sets index of inventory that will drop when killed
    void SetOneDroppedItem(int newDrop) {dropItem = newDrop;}
    void SetNoDroppedItem() {dropItem = -1;}
    Item* GetDroppedItem() {if (dropItem == -1) {return new Item();} return inventory[dropItem];}

    //Lowers intent values
    void LowerAttack(int val) {attack -= val; if (attack < 0) {attack = 0;}}
    void LowerMagic(int val) {magic -= val; if (magic < 0) {magic = 0;}}
    void LowerDefend(int val) {defend -= val; if (defend < 0) {defend = 0;}}

    //Returns item/ability monster intends to use
    Item* GetIntent() {return inventory[intent];}
    int GetAttack() {return attack;}
    int GetMagic() {return magic;}
    int GetDefend() {return defend;}

    string getName() {return name;}

    void TakeDamage(int dam) {
        if (dam < 0) {return;}
        if (block > 0) {
            if (dam > block) {dam -= block; block = 0;}
            else {block -= dam; dam = 0;}
        }
        health -= dam;
    }
    void GainBlock(int blk) {block += blk;}
    void ResetBlock() {block = 0;}

    bool Alive() {
        if (health > 0) {return true;}
        return false;
    }

    //Returns false if monster is an empty placeholder
    bool Real() {
        if (name == "") {return false;}
        return true;
    }

    //Returns array of all constant monster values as strings
    //Name, health, maxHP, block
    string* getStrings() {
        string* stats = new string[4];
        stats[0] = name;
        stats[1] = to_string(health);
        stats[2] = to_string(maxHP);
        stats[3] = to_string(block);
        return stats;
    }
};

#endif