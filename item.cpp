#ifndef ITEM
#define ITEM

#include <iostream>
using namespace std;

class Item {
    //Variables
    string name;
    int value;
    int durability;
    int maxDurability;

    //Item type booleans
    bool weapon;
    bool magic;
    bool target;

public:
    //Empty item constructor
    Item() {
        name = ""; value = -1; durability = -1; maxDurability = -1;
        weapon = false; magic = false; target = false;
    }

    //Item constructor
    //Name, value, durability, isWeapon, isMagic, isTarget
    Item(string n, int val, int dur, bool w, bool m, bool t) {
        name = n; value = val, maxDurability = dur; durability = maxDurability;
        weapon = w; magic = m; target = t;
    }

    //Lower durability and return value of item
    int use() {
        if (durability < 1) {return -1;}
        else {
            durability--;
            if (durability < 1) {MakeEmpty();}
            return value;
        }
    }

    //Returns value if usable
    int GetValue() {
        if (durability < 1) {return -1;}
        return value;
    }
    string GetName() {return name;}

    //Returns true if this item does damage
    bool IsWeapon() {return weapon;}
    //Returns true if this item is magic
    bool IsMagic() {return magic;}
    //Returns true if item targets a specific enemy
    bool IsTarget() {return target;}

    //Returns true if this is an null item
    bool Empty() {
        if (name == "") {return true;}
        return false;
    }

    //Makes this into a null item
    void MakeEmpty() {
        name = ""; durability = -1; maxDurability = -1;
    }

    //Returns string with all of item's information
    //Format: Name(value) durability/max durability
    //Example: Knife(2) 3/10
    string toString() {
        if (value == -1) {return "";}
        string description = name+"("+to_string(value)+") "+to_string(durability)+"/"+to_string(maxDurability);
        return description;
    }

    //Returns string with basic information
    //Format: Name(value)
    string basicString() {
        if (value == -1) {return "";}
        string description = name+"("+to_string(value)+")";
        return description;
    }
};

#endif