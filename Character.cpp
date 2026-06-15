#include "Character.h"

Character::Character(std::string name, int hitpoints, int damage, int defense)
{
    this->name = name;
    this->hitpoints = hitpoints;
    this->maxHitpoints = hitpoints;
    this->damage = damage;
    this->defense = defense;
}

Character::~Character()
{
    std::cout << "LOG: Maze se postava: " << name << std::endl;
}

std::string Character::getName() { return this->name; }

int Character::getHitpoints() { return this->hitpoints; }

int Character::getDamage() { return this->damage; }

int Character::getDefense() { return this->defense; }

void Character::takeDamage(int dmg)
{
    int actualDamage = dmg - this->defense;
    if (actualDamage < 0)
        actualDamage = 0;

    this->hitpoints -= actualDamage;
    if (this->hitpoints < 0)
        this->hitpoints = 0;
}

void Character::heal(int amount)
{
    this->hitpoints += amount;
    if (this->hitpoints > this->maxHitpoints)
    {
        this->hitpoints = this->maxHitpoints;
    }

    std::cout << this->name << " drank a strange liquid and recovered some HP. (" << this->hitpoints << "/" << this->maxHitpoints << ")\n";
}

void Character::increaseDMG(int amount)
{
    this->damage += amount;

    std::cout << this->name << "'s smart move to use this weapon increased his damage slightly. +" << amount << " DMG\n";
}

void Character::increaseDEF(int amount)
{
    this->defense += amount;

    std::cout << this->name << "'s idea to equip armor boosted his defense by small amount. +" << amount << " DEF\n";
}