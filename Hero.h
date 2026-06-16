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

    int getUltiCount();

    void gainExp(int amount);

    void setPosition(int startX, int startY);

    int getX();
    int getY();

    int getFloor();

    int setFloor(int floor);

    int getXP();
    int getLVL();

private:
    void levelup();
};