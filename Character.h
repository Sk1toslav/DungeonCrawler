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

    int weaponBonus = 0;
    int armorBonus = 0;

public:
    Character(std::string name, int hitpoints, int damage, int defense);

    virtual ~Character();

    std::string getName() const;
    int getHitpoints() const;
    int getDamage() const;
    int getDefense() const;

    void takeDamage(int dmg);
    void takeTrueDamage(int dmg);

    void heal(int amount);

    void equipWeapon(int amount); 
    void equipArmor(int amount);
};
