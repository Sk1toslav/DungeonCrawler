#include "Hero.h"

Hero::Hero(std::string name, int hitpoints, int damage, int defense, int UltimateAbility) : Character(name, hitpoints, damage, defense)
{
    this->UltimateAbility = UltimateAbility;
    this->UltimateCount = 3;
    this->level = 1;
    this->experience = 0;
    this->experienceNeeded = 100;

    this->inventory.push_back(std::make_unique<Potion>("Minor Health Potion", 30)); /* TEST PRO SHOW INVENTARE */

    this->inventory.push_back(std::make_unique<Weapon>("Rusty sword", 5)); /* TEST PRO SHOW INVENTARE */

    this->inventory.push_back(std::make_unique<Accessories>("Worn-out cape", 3)); /* TEST PRO SHOW INVENTARE */
}

void Hero::showInventory()
{

    if (inventory.empty())
    {
        std::cout << "You don't have any loot in your inventory..\n";
        return;
    }

    std::cout << "Your inventory contains:\n";
    for (int i = 0; i < inventory.size(); i++)
    {
        std::cout << i + 1 << ". ";
        inventory[i]->info();
    }
}

void Hero::useItemFromInventory(int index)
{
    int realIndex = index - 1;

    if (realIndex >= 0 && realIndex < inventory.size())
    {
        std::cout << "\nUsing item: " << inventory[realIndex]->getName() << "...\n";

        inventory[realIndex]->use(*this);

        inventory.erase(inventory.begin() + realIndex);
    }
    else
    {
        std::cout << "\nERROR: Hero grabbed into an empty space in your backpack.\n";
    }
}

int Hero::getUltiDMG()
{
    if (this->UltimateCount > 0)
    {
        this->UltimateCount -= 1;
        return this->UltimateAbility;
    }
    return 0;
}

int Hero::getUltiCount()
{
    return this->UltimateCount;
}

void Hero::gainExp(int amount)
{
    this->experience += amount;
    std::cout << "Hero " << this->name << " gained " << amount << " XP\n";

    if (this->experience >= experienceNeeded)
    {
        levelup();
    }
}

void Hero::setPosition(int startX, int startY)
{
    this->x = startX;
    this->y = startY;
}

int Hero::getX() { return this->x; }
int Hero::getY() { return this->y; }

void Hero::levelup()
{
    this->level++;
    this->experience -= this->experienceNeeded;
    this->experienceNeeded += 50;

    this->maxHitpoints += 10;
    this->hitpoints = this->maxHitpoints;
    this->damage += 5;
    this->defense += 2;

    std::cout << "******************************\n";
    std::cout << "Hero '" << this->name << "' has ascended to level " << this->level << "!\n";
    std::cout << "He feels more power surging through him.\n";
    std::cout << "******************************\n\n";
}