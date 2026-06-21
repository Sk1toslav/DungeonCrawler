#include "Hero.h"
#include "Game.h"

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
        std::cout << "\n"
                  << RED << "ERROR: Hero grabbed into an empty space in your backpack.\n"
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

int Hero::getUltiCount() const { return this->UltimateCount; }

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

int Hero::getX() const { return this->x; }
int Hero::getY() const { return this->y; }

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

    std::cout << "\n**********************************\n";
    std::cout << "Hero '" << this->name << "' has ascended to level " << this->level << "!\n";
    std::cout << "He feels more power surging through him.\n";
    std::cout << "**********************************\n\n";
}

int Hero::getFloor() const { return this->currentFloor; }
int Hero::setFloor(int floor)
{
    this->currentFloor = floor;
    return this->currentFloor;
}

int Hero::getXP() const { return this->experience; }
int Hero::getLVL() const { return this->level; }
void Hero::setLevel(int lvl) { this->level = lvl; }
void Hero::setXP(int xp) { this->experience = xp; }
void Hero::setMaxHP(int maxHP) { this->maxHitpoints = maxHP; }
int Hero::getInventorySize() const { return this->inventory.size(); }
Item *Hero::getItem(int index) const { return this->inventory[index].get(); }
void Hero::addItem(std::unique_ptr<Item> item) { inventory.push_back(std::move(item)); }