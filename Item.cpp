#include "Item.h"
#include "Character.h"

Item::Item(std::string name)
{
    this->name = name;
}

Item::~Item()
{
    std::cout << "LOG: Maze se predmet " << this->name << std::endl;
}

std::string Item::getName()
{
    return this->name;
}

// Potion

Potion::Potion(std::string name, int healAmount) : Item(name)
{
    this->healAmount = healAmount;
}

int Potion::getHealAmount()
{
    return this->healAmount;
}

void Potion::info()
{
    std::cout << "Strange red potion that gives off a healing aura.\n";
}

void Potion::use(Character &target)
{
    target.heal(healAmount);
};

// Weapon

Weapon::Weapon(std::string name, int weaponDMG) : Item(name)
{
    this->weaponDMG = weaponDMG;
}

int Weapon::getWeaponDMG()
{
    return this->weaponDMG;
}

void Weapon::info()
{
    std::cout << this->name << " which can be equipped to boost hero's attack power.\n";
}

void Weapon::use(Character &target)
{
    target.equipWeapon(weaponDMG);
};

// Accessory

Accessories::Accessories(std::string name, int AccDefense) : Item(name)
{
    this->AccDefense = AccDefense;
}

int Accessories::getAccessoryDEF()
{
    return this->AccDefense;
}

void Accessories::info()
{
    std::cout << this->name << " provides a helping hand in blocking attacks more easily.\n";
}

void Accessories::use(Character &target)
{
    target.equipArmor(AccDefense);
};