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

int Character::getDamage() { return this->damage + this->weaponBonus; }

int Character::getDefense() { return this->defense + this->armorBonus; }

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

void Character::equipWeapon(int amount)
{
    this->damage = this->damage + amount;

    std::cout << "You grip the new weapon. A cold shiver runs down your spine as you test its weight.\n";
}

void Character::equipArmor(int amount)
{
    this->defense = this->defense + amount;

    std::cout << "You strap the armor over your wounds. It feels suffocating, but it might just save your life.\n";
}
