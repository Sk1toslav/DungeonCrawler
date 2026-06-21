#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Character.h"
#include "Item.h"

class Hero : public Character
{
private:
    int UltimateAbility;
    int UltimateCount;
    int level;
    int experience;
    int experienceNeeded;
    int x;
    int y;
    int currentFloor;
    std::vector<std::unique_ptr<Item>> inventory;

public:
    Hero(std::string name, int hitpoints, int damage, int defense, int UltimateAbility);

    void showInventory();

    void useItemFromInventory(int index);

    int getUltiDMG();

    int getUltiCount() const;

    void gainExp(int amount);

    void setPosition(int startX, int startY);

    int getX() const;
    int getY() const;

    int getFloor() const;

    int setFloor(int floor);

    int getXP() const;
    int getLVL() const;

    void setLevel(int lvl);
    void setXP(int xp);
    void setMaxHP(int maxHP);

    int getInventorySize() const;
    Item *getItem(int index) const;
    void addItem(std::unique_ptr<Item> item);

private:
    void levelup();
};