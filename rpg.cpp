#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <memory>

#include "Item.h"
#include "Character.h"
#include "Hero.h"
#include "Enemy.h"
#include "Game.h"

void saveGame(Hero &player)
{
    // Otevřeme soubor pro zápis (pokud neexistuje, C++ ho vytvoří)
    std::ofstream file("savegame.txt");

    if (file.is_open())
    {
        // Zapisujeme data pod sebe na samostatné řádky
        file << player.getName() << "\n";
        file << player.getHitpoints() << "\n";
        file << player.getDamage() << "\n";
        file << player.getDefense() << "\n";
        file << player.getFloor() << "\n";

        file.close();
        std::cout << GREEN << "Game successfully saved." << RESET << "\n";
    }
    else
    {
        std::cout << RED << "ERROR: Nepodarilo se vytvorit soubor savegame.txt" << RESET << "\n";
    }
}

std::unique_ptr<Hero> loadGame()
{
    std::ifstream file("savegame.txt");

    if (file.is_open())
    {
        std::string loadedName;
        int loadedHP, loadedDMG, loadedDEF, loadedFloor;

        file >> loadedName;
        file >> loadedHP;
        file >> loadedDMG;
        file >> loadedDEF;
        file >> loadedFloor;

        file.close();

        auto loadedHero = std::make_unique<Hero>(loadedName, loadedHP, loadedDMG, loadedDEF, 30);

        loadedHero->setFloor(loadedFloor);

        std::cout << GREEN << "Game successfully loaded! Welcome back, " << loadedName << "." << RESET << "\n";

        return loadedHero;
    }
    else
    {
        std::cout << RED << "ERROR: No save file found." << RESET << "\n";
        return nullptr;
    }
}

int main()
{
    std::cout << "******************************\n";
    std::cout << "Welcome to Dungeon Crawler #1\n";
    std::cout << "******************************\n";

    std::vector<std::vector<std::string>> loadedMaps = loadMaps("maps.txt");

    if (loadedMaps.empty())
    {
        std::cout << "ERROR: Mapa nenactena, zkontroluj maps.txt\n";
        return 1;
    }

    std::unique_ptr<Hero> activeHero = nullptr;

    bool run = true;
    while (run)
    {
        char volba;
        std::cout << "Start new run (N) | Save game (S) | Load save (L) | Exit game (E)\n";
        std::cin >> volba;

        switch (toupper(volba))
        {
        case 'N':
        {
            std::cout << "******************************\n";
            std::cout << "What is your name Crawler?\n";
            std::cout << "******************************\n";

            std::string heroName;
            std::cin >> heroName;

            activeHero = std::make_unique<Hero>(heroName, 100, 15, 5, 30);

            std::cout << "******************************\n";
            std::cout << "Hero " << heroName << " embarks fearlessly into the dungeon!\n";
            std::cout << "******************************\n";

            activeHero->setPosition(1, 1);

            waitForEnter();
            dungeon(*activeHero, loadedMaps);
            break;
        }

        case 'S':
            if (activeHero != nullptr)
            {
                saveGame(*activeHero);
            }
            else
            {
                std::cout << RED << "ERROR: No active hero to save. Start a new run first.\n"
                          << RESET;
            }
            break;

        case 'L':
        {
            std::unique_ptr<Hero> loadedPlayer = loadGame();

            if (loadedPlayer != nullptr)
            {
                activeHero = std::move(loadedPlayer);

                activeHero->setPosition(1, 1);
                waitForEnter();
                dungeon(*activeHero, loadedMaps);
            }
            break;
        }
        case 'E':
            std::cout << "Exiting game..\n";
            run = false;
            break;

        default:
            std::cout << "ERROR: Wrong input. Try again.\n\n";
            break;
        }
    }

    return 0;
}
