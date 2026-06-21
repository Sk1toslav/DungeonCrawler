#include "Game.h"
#include "SaveLoad.h"

#include <iostream>
#include <fstream>
#include <cctype>
#include <memory>

std::vector<std::vector<std::string>> loadMaps(std::string filename)
{
    std::vector<std::vector<std::string>> allMaps;
    std::vector<std::string> currentMap;

    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line == "-")
            {
                allMaps.push_back(currentMap);
                currentMap.clear();
            }
            else if (!line.empty())
            {
                currentMap.push_back(line);
            }
        }

        if (!currentMap.empty())
        {
            allMaps.push_back(currentMap);
        }

        file.close();
    }
    else
    {
        std::cout << RED << "ERROR: Nepodarilo se otevrit soubor " << filename << RESET << "\n";
    }

    return allMaps;
}

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

void waitForEnter()
{
    std::cout << "\n"
              << YELLOW << "[Press ENTER to continue...]\n"
              << RESET;
    std::cin.ignore(10000, '\n');
    std::cin.get();
}

void mapvisual(Hero &player, std::vector<std::string> &map)
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (x == player.getX() && y == player.getY())
                std::cout << GREEN << " H" << RESET;
            else
            {
                char tile = map[y][x];
                if (tile == 'E')
                    std::cout << RED << " " << tile << RESET;
                else if (tile == 'D')
                    std::cout << YELLOW << " " << tile << RESET;
                else
                    std::cout << " " << tile;
            }
        }
        std::cout << '\n';
    }
}

bool encounter(Hero &player, Enemy &enemy)
{
    clearScreen();
    std::cout << "\n\n"
              << RED << "============================================" << RESET << "\n";
    std::cout << RED << "! A MONSTER EMERGES FROM THE SHADOWS !      " << RESET << "\n";
    std::cout << RED << "============================================" << RESET << "\n\n";

    while (player.getHitpoints() > 0 && enemy.getHitpoints() > 0)
    {
        std::cout << "\n--------------------------------------------------\n";
        std::cout << GREEN << player << RESET << "   VS   " << RED << enemy << RESET << "\n";
        std::cout << "--------------------------------------------------\n\n";

        std::cout << "[A] Attack   |   [B] Blood Magic (" << RED << player.getUltiCount() << RESET << ")   |   [R] Flee\n";
        std::cout << "Action: ";

        char input;
        std::cin >> input;
        input = toupper(input);

        std::cout << "\n";

        switch (input)
        {
        case 'A':
            std::cout << GREEN << player.getName() << RESET << " attacks for " << YELLOW << player.getDamage() << RESET << " damage!\n";
            enemy.takeDamage(player.getDamage());

            if (enemy.getHitpoints() == 0)
            {
                std::cout << "\n"
                          << RED << enemy.getName() << YELLOW << " has been slain!\n"
                          << RESET;
                return true;
            }
            std::cout << RED << enemy.getName() << RESET << " strikes back for " << YELLOW << enemy.getDamage() - player.getDefense() << RESET << " damage!\n";
            player.takeDamage(enemy.getDamage());
            break;

        case 'B':
        {
            int UltDMG = player.getUltiDMG();

            if (UltDMG > 0)
            {
                std::cout << RED << "You slice open your own palm. Boiling blood erupts and strikes the enemy for " << UltDMG << " TRUE damage!\n"
                          << RESET;
                enemy.takeTrueDamage(UltDMG);
            }

            if (player.getHitpoints() <= 0)
            {
                std::cout << "\n"
                          << RED << "The blood loss was too great. You collapse into your own crimson pool...\n"
                          << RESET;
                return false;
            }
            else if (UltDMG <= 0)
            {
                std::cout << YELLOW << "Your veins feel dry. The dark magic demands a sacrifice you cannot make.\n"
                          << RESET;
            }

            if (enemy.getHitpoints() == 0)
            {
                std::cout << "\n"
                          << RED << "The abomination collapses, torn apart by your dark arts!\n"
                          << RESET;
                return true;
            }
            std::cout << RED << "The creature shrieks and strikes back for " << YELLOW << enemy.getDamage() - player.getDefense() << RESET << " damage!\n";
            player.takeDamage(enemy.getDamage());
            break;
        }

        case 'R':
            std::cout << "Nothing too shameful about running away and preserving your life..\n";
            return false;

        default:
            std::cout << YELLOW << "Hero's head got all messed up with the things he can do and wastes his turn.\n"
                      << RESET;
            std::cout << RED << enemy.getName() << RESET << " strikes confused hero for " << YELLOW << enemy.getDamage() - player.getDefense() << RESET << " damage!\n";
            player.takeDamage(enemy.getDamage());
            break;
        }
    }
    return false;
}

void dungeon(Hero &player, std::vector<std::vector<std::string>> &allMaps, std::vector<std::string> savedMap)
{
    bool inDungeon = true;
    char moveChoice;

    while (inDungeon)
    {
        std::vector<std::string> currentMap;

        if (!savedMap.empty())
        {
            currentMap = savedMap;
            savedMap.clear();
        }
        else
        {
            currentMap = allMaps[(player.getFloor() - 1) % allMaps.size()];
        }

        bool floorCleared = false;

        while (!floorCleared && inDungeon)
        {
            clearScreen();

            std::cout << "\n\nx=x=x=x=x=x=x=x=x=x=x=x=x=x=x\n";
            std::cout << "   DUNGEON (FLOOR " << player.getFloor() << "/100) \n";
            std::cout << "x=x=x=x=x=x=x=x=x=x=x=x=x=x=x\n\n";

            mapvisual(player, currentMap);

            std::cout << "\n--------------------------------------------------\n";
            std::cout << "[W/A/S/D] Move  |  [I] Inventory  |  [V] Save  |  [Q] Quit\n";
            std::cout << "--------------------------------------------------\n";
            std::cout << "Action: ";

            std::cin >> moveChoice;

            moveChoice = toupper(moveChoice);

            int targetX = player.getX();
            int targetY = player.getY();

            if (moveChoice == 'W')
                targetY--;
            else if (moveChoice == 'S')
                targetY++;
            else if (moveChoice == 'A')
                targetX--;
            else if (moveChoice == 'D')
                targetX++;
            else if (moveChoice == 'I')
            {
                clearScreen();
                std::cout << "\n\n";
                player.showInventory();
                std::cout << "\nWhich item do you intend to use? (0 to Cancel) \n";
                std::cout << "Action: ";

                int itemChoice;
                std::cin >> itemChoice;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "\n"
                              << RED << "ERROR: Invalid number\n"
                              << RESET;
                    waitForEnter();
                }
                else if (itemChoice > 0)
                {
                    player.useItemFromInventory(itemChoice);
                    waitForEnter();
                }
                continue;
            }
            else if (moveChoice == 'V')
            {
                std::cout << "\n";
                saveGame(player, currentMap);
                waitForEnter();
                continue;
            }
            else if (moveChoice == 'Q')
            {
                std::cout << "\nReturning to main menu.\n";
                inDungeon = false;
                continue;
            }
            else
            {
                std::cout << "\n"
                          << RED << "ERROR: Wrong input. Try again.\n"
                          << RESET;
                waitForEnter();
                continue;
            }

            if (currentMap[targetY][targetX] == '*')
            {
                std::cout << "\n"
                          << YELLOW << "Your clumsy feet stumbled upon a wall. Try another way.\n"
                          << RESET;
                waitForEnter();
            }
            else if (currentMap[targetY][targetX] == 'C')
            {
                std::cout << "\n"
                          << YELLOW << "You force open a rotting, ancient chest...\n"
                          << RESET;

                int roll = rand() % 3;

                std::string itemName;
                int itemStat;

                if (roll == 0)
                {
                    itemName = "Vial of Crimson Blood";
                    itemStat = 25 + (player.getFloor() * 5);
                    player.addItem(std::make_unique<Potion>(itemName, itemStat));
                    std::cout << "Inside lies a '" << itemName << "'. It smells faintly of iron.\n";
                }
                else if (roll == 1)
                {
                    itemName = "Rusted Iron Blade";
                    itemStat = 3 + (player.getFloor() * 2);
                    player.addItem(std::make_unique<Weapon>(itemName, itemStat));
                    std::cout << "You pull out a '" << itemName << "'. It looks heavy and cruel.\n";
                }
                else if (roll == 2)
                {
                    itemName = "Tattered Leather Rags";
                    itemStat = 1 + (player.getFloor() * 1);
                    player.addItem(std::make_unique<Accessories>(itemName, itemStat));
                    std::cout << "You find '" << itemName << "'. It's still stained from its previous owner.\n";
                }

                currentMap[targetY][targetX] = '.';
                player.setPosition(targetX, targetY);
                waitForEnter();
            }
            else if (currentMap[targetY][targetX] == 'E')
            {

                std::unique_ptr<Enemy> foughtEnemy = nullptr;

                if (player.getFloor() == 2)
                {
                    clearScreen();
                    std::cout << "\n";
                    std::cout << RED << "The air turns to scorching ash. A colossal pair of reptilian eyes opens in the dark...\n"
                              << RESET;
                    waitForEnter();

                    foughtEnemy = std::make_unique<Enemy>("Carnage, THE RED DRAGON", 750, 60, 25, 5000);
                }
                else
                {
                    clearScreen();
                    std::cout << "\n"
                              << RED << "A grotesque shape emerges from the shadows. There is no turning back now.\n"
                              << RESET;
                    waitForEnter();

                    int enemyHP = 25 + (player.getFloor() * 5);
                    int enemyDMG = 6 + (player.getFloor() * 2);
                    int enemyDEF = 1 + (player.getFloor() * 1);
                    int enemyXP = 40 + (player.getFloor() * 10);

                    foughtEnemy = std::make_unique<Enemy>("Monster (F" + std::to_string(player.getFloor()) + ")", enemyHP, enemyDMG, enemyDEF, enemyXP);
                }

                bool won = encounter(player, *foughtEnemy);

                if (won)
                {
                    std::cout << "\n"
                              << GREEN << "You won the battle!\n"
                              << RESET;
                    player.gainExp(foughtEnemy->getXpReward());
                    currentMap[targetY][targetX] = '.';
                    player.setPosition(targetX, targetY);
                    waitForEnter();

                    if (player.getFloor() == 100)
                    {
                        clearScreen();
                        std::cout << "\n"
                                  << GREEN << "==================================================\n";
                        std::cout << "THE RED DRAGON COLLAPSES. THE DUNGEON FALLS SILENT.\n";
                        std::cout << "YOU HAVE CONQUERED THE DEPTHS AND WON THE GAME!\n";
                        std::cout << "==================================================\n"
                                  << RESET;
                        waitForEnter();
                        inDungeon = false;
                    }
                }
                else if (player.getHitpoints() <= 0)
                {
                    std::cout << "\n"
                              << RED << "Your vision fades to black. Another soul claimed by the depths...\n"
                              << RESET;
                    recordDeath(player);
                    waitForEnter();
                    inDungeon = false;
                }
            }
            else if (currentMap[targetY][targetX] == '.')
            {
                player.setPosition(targetX, targetY);
            }
            else if (currentMap[targetY][targetX] == 'D')
            {
                std::cout << "\n"
                          << YELLOW << "You push through the heavy doors, descending deeper into the suffocating darkness...\n"
                          << RESET;
                waitForEnter();

                player.setFloor(player.getFloor() + 1);
                floorCleared = true;

                if (player.getFloor() > 100)
                {
                    std::cout << "\n"
                              << GREEN << "Congratulations! You have conquered all levels of the dungeon and emerged victorious!\n"
                              << RESET;
                    waitForEnter();
                    inDungeon = false;
                }
                else
                {
                    player.setPosition(1, 1);
                }
            }
        }
    }
}