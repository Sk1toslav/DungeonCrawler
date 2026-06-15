#include "Enemy.h"

Enemy::Enemy(std::string name, int hitpoints, int damage, int defense, int xpReward) : Character(name, hitpoints, damage, defense)
{
    this->xpReward = xpReward;
}

int Enemy::getXpReward()
{
    return this->xpReward;
}