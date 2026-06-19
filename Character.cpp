#include "Character.h"
#include "Game.h" // Pro MARGIN

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
    // Logy většinou nepotřebují margin, ty hráč běžně moc nevnímá
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
    std::cout << MARGIN << this->name << " drank a strange liquid and recovered some HP. (" << this->hitpoints << "/" << this->maxHitpoints << ")\n";
}

void Character::equipWeapon(int amount)
{
    this->weaponBonus = amount;
    std::cout << MARGIN << "You grip the new weapon. A cold shiver runs down your spine as you test its weight.\n";
}

void Character::equipArmor(int amount)
{
    this->armorBonus = amount;
    std::cout << MARGIN << "You strap the armor over your wounds. It feels suffocating, but it might just save your life.\n";
}