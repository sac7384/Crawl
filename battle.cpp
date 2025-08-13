#ifndef BATTLE
#define BATTLE

#include <iostream>
#include "player.cpp"
#include "monster.cpp"
#include "item.cpp"
using namespace std;

class Battle {
    //Objects
    Player* player;
    Monster* monsters[3];
    Item* weapon;

    //Variables
    int input; int offset; int value; bool dead;

public:
    Battle(Player* p, Monster* m[]) {
        //Initialize objects
        player = p; monsters[0] = m[0]; monsters[1] = m[1]; monsters[2] = m[2];
        //Random number generator
        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> dist(0, 100);

        ///Player turn loop
        while (monsters[0]->Alive() || monsters[1]->Alive() || monsters[2]->Alive()) {
            cout << "New player turn\n";

            //Set monster intents
            for (int i = 0; i < 3; i++) {monsters[i]->NewIntent(dist(mt) % 3);}
            player->ResetStamina();

            ///Player actions loop
            while (player->GetStamina() > 0) {
                //Print monster and player info
                PrintBattleInfo();

            //Player action
                cout << "\nUse which item? ";
                cin >> input;
            if (input == -1) { return; }
                //End turn early
                if (input == 0) {break;}
                //Validate chosen item slot
                weapon = player->GetItem(input - 1);
                if (weapon->Empty()) {
                    cout << "There is no usable item in that slot\n";
                    continue;
                }
                if (weapon->IsTarget()) {
                    //Choose target
                    cout << "Which target? ";
                    cin >> input;
                    cout << "\n";
                    input--;

                    if (input > 2 || input < 0) {cout << "That is not a valid target\n";}
                    else if (monsters[input]->Alive()) {
                        if (weapon->IsWeapon()) {
                            value = weapon->use();
                            cout << "You attack the " << monsters[input]->getName() << " and deal " << value << " damage\n";
                            monsters[input]->TakeDamage(value);
                        } else {
                            value = weapon->use();
                            cout << "You use the " << weapon->GetName() << " to block some of " << monsters[input]->getName() << "'s attack\n";
                            monsters[input]->LowerAttack(value);
                        }
                        player->LoseStamina();
                    }
                }//End of single target
                else {  //Item has no specific target
                    cout << "\n";
                    if (weapon->IsWeapon()) {
                        value = weapon->use();
                        cout << "You use the " << weapon->GetName() << " to attack all enemies and deal " << value << " damage\n";
                        for (int i = 0; i < 3; i++) {monsters[i]->TakeDamage(value);}
                    }
                    else {
                        value = weapon->use();
                        cout << "You defend yourself and gain " << value << " block\n";
                        player->GainBlock(value);
                    }
                    player->LoseStamina();
                }

                //Monster killed message and replace with empty monster
                for (int i = 0; i < 3; i++) {
                    if (monsters[i]->Real() && !monsters[i]->Alive()) {
                        cout << "You killed the " << monsters[i]->getName() << "!\n";
                        if (!monsters[i]->GetDroppedItem()->Empty()) {
                            cout << "You got a " << monsters[i]->GetDroppedItem()->GetName() << "\n";
                            player->ObtainItem(monsters[i]->GetDroppedItem());
                        }
                        monsters[i] = new Monster();
                    }
                }
                cout << "\n";

                //Battle ends if player is dead, or all monsters are dead
                if (dead || !(monsters[0]->Alive() || monsters[1]->Alive() || monsters[2]->Alive())) {
                    return;
                }
            }///End of player turn loop

            //Monster actions
            for (int i = 0; i < 3; i++) {
                if (monsters[i]->Real()) {
                    if (monsters[i]->GetAttack() != 0) {
                        dead = player->LoseHealth(monsters[i]->GetAttack());
                        cout << "The " << monsters[i]->getName() << " attacks you and deals " << monsters[i]->GetAttack()
                             << " damage\n";
                    }
                    if (monsters[i]->GetMagic() != 0) {
                        dead = player->LoseHealth(monsters[i]->GetMagic());
                        cout << "The " << monsters[i]->getName() << " casts a spell and deals " << monsters[i]->GetMagic()
                             << " damage to you\n";
                    }
                    if (monsters[i]->GetDefend() != 0) {
                        monsters[i]->GainBlock(monsters[i]->GetDefend());
                        cout << "The " << monsters[i]->getName() << " defends themselves and gains "
                             << monsters[i]->GetDefend() << " block\n";
                    }
                    monsters[i]->GetIntent()->use();
                }
            }
            cout << "\n";

            //Checks if player died
            if (dead) {return;}

        }///End of battle loop
    }

    //Prints stats and gear for monsters and player
    void PrintBattleInfo() {
        ///Print monster info
        int maxChar = 32;
        string* constants1 = monsters[0]->getStrings();
        string* constants2 = monsters[1]->getStrings();
        string* constants3 = monsters[2]->getStrings();
        cout << "****************************************************************************************************\n";
        ///Names
        cout << constants1[0];
        for (int i = constants1[0].length(); i < maxChar; i++) {cout << " ";}
        cout << constants2[0];
        for (int i = constants2[0].length(); i < maxChar; i++) {cout << " ";}
        cout << constants3[0];
        for (int i = constants3[0].length(); i < maxChar; i++) {cout << " ";}
        cout << "\n";

        ///Health/MaxHP + Block
        offset = 0;
        if (monsters[0]->Real()) {
            cout << constants1[1] << "/" << constants1[2];
            offset = constants1[1].length() + constants1[2].length() + 1;
            if (constants1[3].compare("0") != 0) {
                cout << " + " << constants1[3];
                offset += 3 + constants1[3].length();
            }
        }
        for (int i = offset; i < maxChar; i++) {cout << " ";}

        offset = 0;
        if (monsters[1]->Real()) {
            cout << constants2[1] << "/" << constants2[2];
            offset = constants2[1].length() + constants2[2].length() + 1;
            if (constants2[3].compare("0") != 0) {
                cout << " + " << constants2[3];
                offset += 3 + constants2[3].length();
            }
        }
        for (int i = offset; i < maxChar; i++) {cout << " ";}

        offset = 0;
        if (monsters[2]->Real()) {
            cout << constants3[1] << "/" << constants3[2];
            offset = constants3[1].length() + constants3[2].length() + 1;
            if (constants3[3].compare("0") != 0) {
                cout << " + " << constants3[3];
                offset += 3 + constants3[3].length();
            }
        }
        for (int i = offset; i < maxChar; i++) {cout << " ";}
        cout << "\n";

        ///Item Intent
        cout << monsters[0]->GetIntent()->basicString();
        for (int i = monsters[0]->GetIntent()->basicString().length(); i < maxChar; i++) {cout << " ";}
        cout << monsters[1]->GetIntent()->basicString();
        for (int i = monsters[1]->GetIntent()->basicString().length(); i < maxChar; i++) {cout << " ";}
        cout << monsters[2]->GetIntent()->basicString();
        for (int i = monsters[2]->GetIntent()->basicString().length(); i < maxChar; i++) {cout << " ";}
        cout << "\n";

        ///Type of Intent (attack, magic, defend)
        //Bug where extra line is printed because while loop has to finish counting
        //May need to redesign this whole section, or might be able to just add 2D array to this
        //Or just live with it!
        offset = 0;
        int counter[3] = {0, 0, 0};
        if (!monsters[0]->Real()) {counter[0] = 3;}
        if (!monsters[1]->Real()) {counter[1] = 3;}
        if (!monsters[2]->Real()) {counter[2] = 3;}
        //Intent print loop
        while (counter[0] < 3 || counter[1] < 3 || counter[2] < 3) {
            //Monster 1
            offset = 0;
            switch (counter[0]) {
                case 0:
                    counter[0]++;
                    if (monsters[0]->GetAttack() != 0) {
                        cout << "Attack: " << monsters[0]->GetAttack();
                        offset = 8 + to_string(monsters[0]->GetAttack()).length();
                        input = 0; break;
                    }
                case 1:
                    counter[0]++;
                    if (monsters[0]->GetMagic() != 0) {
                        cout << "Magic: " << monsters[0]->GetMagic();
                        offset = 7 + to_string(monsters[0]->GetMagic()).length();
                        input = 0; break;
                    }
                case 2:
                    counter[0]++;
                    if (monsters[0]->GetDefend() != 0) {
                        cout << "Defend: " << monsters[0]->GetDefend();
                        offset = 8 + to_string(monsters[0]->GetDefend()).length();
                        input = 0; break;
                    }
            }
            for (int i = offset; i < maxChar; i++) {cout << " ";}

            //Monster 2
            offset = 0;
            switch (counter[1]) {
                case 0:
                    counter[1]++;
                    if (monsters[1]->GetAttack() != 0) {
                        cout << "Attack: " << monsters[1]->GetAttack();
                        offset = 8 + to_string(monsters[1]->GetAttack()).length();
                        input = 0; break;
                    }
                case 1:
                    counter[1]++;
                    if (monsters[1]->GetMagic() != 0) {
                        cout << "Magic: " << monsters[1]->GetMagic();
                        offset = 7 + to_string(monsters[1]->GetMagic()).length();
                        input = 0; break;
                    }
                case 2:
                    counter[1]++;
                    if (monsters[1]->GetDefend() != 0) {
                        cout << "Defend: " << monsters[1]->GetDefend();
                        offset = 8 + to_string(monsters[1]->GetDefend()).length();
                        input = 0; break;
                    }
            }
            for (int i = offset; i < maxChar; i++) {cout << " ";}

            //Monster 3
            offset = 0;
            switch (counter[2]) {
                case 0:
                    counter[2]++;
                    if (monsters[2]->GetAttack() != 0) {
                        cout << "Attack: " << monsters[2]->GetAttack();
                        offset = 8 + to_string(monsters[2]->GetAttack()).length();
                        input = 0; break;
                    }
                case 1:
                    counter[2]++;
                    if (monsters[2]->GetMagic() != 0) {
                        cout << "Magic: " << monsters[2]->GetMagic();
                        offset = 7 + to_string(monsters[2]->GetMagic()).length();
                        input = 0; break;
                    }
                case 2:
                    counter[2]++;
                    if (monsters[2]->GetDefend() != 0) {
                        cout << "Defend: " << monsters[2]->GetDefend();
                        offset = 8 + to_string(monsters[2]->GetDefend()).length();
                        input = 0; break;
                    }
            }
            for (int i = offset; i < maxChar; i++) {cout << " ";}

            cout << "\n";
        }//End of intent print loop

        ///Effects

        cout << "****************************************************************************************************\n";
        //100 *'s

        ///Print player info
        //Stats
        cout << "Health: " << player->GetHealth() << "/" << player->GetMaxHP();
        if (player->GetBlock() > 0) {cout << " + " << player->GetBlock();}
        cout << "\n";
        cout << "Stamina: " << player->GetStamina() << "/" << player->GetMaxStamina() << "\n";

        //Inventory
        cout << "Inventory:\n";
        player->printInventory();
    }//End of PrintBattleInfo()
};

#endif