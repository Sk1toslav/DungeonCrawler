#pragma once

#include "Character.h"

class Enemy : public Character
{
private:
    int xpReward;

public:
    Enemy(std::string name, int hitpoints, int damage, int defense, int xpReward);

    int getXpReward();
};