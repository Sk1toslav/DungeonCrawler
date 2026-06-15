#pragma once

#include <string>
#include <iostream>

class Character;

class Item
{
protected:
    std::string name;

public:
    Item(std::string name);

    virtual ~Item();

    std::string getName();

    virtual void info() = 0;

    virtual void use(Character &target) = 0;
};

class Potion : public Item
{
private:
    int healAmount;

public:
    Potion(std::string name, int healAmount);

    int getHealAmount();

    void info() override;

    void use(Character &target) override;
};

class Weapon : public Item
{
private:
    int weaponDMG;

public:
    Weapon(std::string name, int weaponDMG);

    int getWeaponDMG();

    void info() override;

    void use(Character &target) override;
};

class Accessories : public Item
{
private:
    int AccDefense;
public:
    Accessories(std::string name, int AccDefense);

    int getAccessoryDEF();

    void info() override;

    void use(Character &target) override;

};