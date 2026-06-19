#include "Hero.h"
#include "Game.h" // Pro přístup k MARGIN

Hero::Hero(std::string name, int hitpoints, int damage, int defense, int UltimateAbility) : Character(name, hitpoints, damage, defense)
{
    this->UltimateAbility = UltimateAbility;
    this->UltimateCount = 3;
    this->level = 1;
    this->experience = 0;
    this->experienceNeeded = 100;
    this->currentFloor = 1;
}

void Hero::showInventory()
{
    if (inventory.empty())
    {
        std::cout << MARGIN << "You don't have any loot in your inventory..\n";
        return;
    }

    std::cout << MARGIN << "Your inventory contains:\n";
    for (int i = 0; i < inventory.size(); i++)
    {
        std::cout << MARGIN << i + 1 << ". ";
        inventory[i]->info(); // Odsazení už zajistilo číslo, item dodá text
    }
}

void Hero::useItemFromInventory(int index)
{
    int realIndex = index - 1;

    if (realIndex >= 0 && realIndex < inventory.size())
    {
        std::cout << "\n"
                  << MARGIN << "Using item: " << inventory[realIndex]->getName() << "...\n";
        inventory[realIndex]->use(*this);
        inventory.erase(inventory.begin() + realIndex);
    }
    else
    {
        std::cout << "\n"
                  << MARGIN << RED << "ERROR: Hero grabbed into an empty space in your backpack.\n"
                  << RESET;
    }
}

int Hero::getUltiDMG()
{
    if (this->UltimateCount > 0)
    {
        this->UltimateCount -= 1;
        int hpCost = 15 + (this->level * 5);
        this->hitpoints -= hpCost;
        return this->UltimateAbility;
    }
    return 0;
}

int Hero::getUltiCount() { return this->UltimateCount; }

void Hero::gainExp(int amount)
{
    this->experience += amount;
    std::cout << MARGIN << "Hero " << this->name << " gained " << amount << " XP\n";

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
    this->experienceNeeded += (50 * this->level);

    this->maxHitpoints += 10;
    this->hitpoints = this->maxHitpoints;
    this->damage += 5;
    this->defense += 2;
    this->UltimateCount = 3;
    this->UltimateAbility += 5;

    std::cout << "\n"
              << MARGIN << "**********************************\n";
    std::cout << MARGIN << "Hero '" << this->name << "' has ascended to level " << this->level << "!\n";
    std::cout << MARGIN << "He feels more power surging through him.\n";
    std::cout << MARGIN << "**********************************\n\n";
}

int Hero::getFloor() { return this->currentFloor; }
int Hero::setFloor(int floor)
{
    this->currentFloor = floor;
    return this->currentFloor;
}

int Hero::getXP() { return this->experience; }
int Hero::getLVL() { return this->level; }
void Hero::setLevel(int lvl) { this->level = lvl; }
void Hero::setXP(int xp) { this->experience = xp; }
int Hero::getInventorySize() { return this->inventory.size(); }
Item *Hero::getItem(int index) { return this->inventory[index].get(); }
void Hero::addItem(std::unique_ptr<Item> item) { inventory.push_back(std::move(item)); }