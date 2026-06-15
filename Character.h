#pragma once

#include <iostream>
#include <string>

class Character
{

protected:
    std::string name;
    int hitpoints;
    int damage;
    int defense;
    int maxHitpoints;

public:
    Character(std::string name, int hitpoints, int damage, int defense);

    virtual ~Character();

    std::string getName();
    int getHitpoints();
    int getDamage();
    int getDefense();

    void takeDamage(int dmg);

    void heal(int amount);

    void increaseDMG(int amount);

    void increaseDEF(int amount);
};
