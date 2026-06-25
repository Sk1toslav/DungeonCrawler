#include "Character.h"
#include "Game.h"

Character::Character(std::string name, int hitpoints, int damage, int defense)
{
    this->name = name;
    this->hitpoints = hitpoints;
    this->maxHitpoints = hitpoints;
    this->damage = damage;
    this->defense = defense;
    this->weaponBonus = 0;
    this->armorBonus = 0;
}

Character::~Character()
{
    std::cout << "LOG: Maze se postava: " << name << std::endl;
}

std::string Character::getName() const { return this->name; }
int Character::getHitpoints() const { return this->hitpoints; }
int Character::getMaxHitpoints() const { return this->maxHitpoints; }
int Character::getDamage() const { return this->damage + this->weaponBonus; }
int Character::getDefense() const { return this->defense + this->armorBonus; }

int Character::takeDamage(int dmg)
{
    int actualDamage = dmg - this->defense;
    if (actualDamage < 0)
        actualDamage = 0;

    this->hitpoints -= actualDamage;
    if (this->hitpoints < 0)
        this->hitpoints = 0;

    return actualDamage;
}

void Character::takeTrueDamage(int dmg)
{
    this->hitpoints -= dmg;
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
    this->weaponBonus = amount;
    std::cout << "You grip the new weapon. A cold shiver runs down your spine as you test its weight.\n";
}

void Character::equipArmor(int amount)
{
    this->armorBonus = amount;
    std::cout << "You strap the armor over your wounds. It feels suffocating, but it might just save your life.\n";
}

std::ostream &operator<<(std::ostream &os, const Character &c)
{
    os << c.name << " (HP: " << c.hitpoints << "/" << c.maxHitpoints << ")";
    return os;
}
