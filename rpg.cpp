#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <memory>
#include <ctime>
#include <cstdlib>

#include "Item.h"
#include "Character.h"
#include "Hero.h"
#include "Enemy.h"
#include "Game.h"
#include "SaveLoad.h"

int main()
{
    srand(time(NULL));

    std::cout << "\n\n"
              << MARGIN << "**********************************\n";
    std::cout << MARGIN << "  Welcome to Dungeon Crawler #1\n";
    std::cout << MARGIN << "**********************************\n\n";

    std::vector<std::vector<std::string>> loadedMaps = loadMaps("maps.txt");

    if (loadedMaps.empty())
    {
        std::cout << MARGIN << RED << "ERROR: Mapa nenactena, zkontroluj maps.txt\n"
                  << RESET;
        return 1;
    }

    std::unique_ptr<Hero> activeHero = nullptr;

    bool run = true;
    while (run)
    {
        char volba;
        std::cout << "\n"
                  << MARGIN << "Start new run (N) | Load save (L) | Exit game (E)\n";
        std::cout << MARGIN << "Action: ";
        std::cin >> volba;

        switch (toupper(volba))
        {
        case 'N':
        {
            std::cout << "\n"
                      << MARGIN << "**********************************\n";
            std::cout << MARGIN << "What is your name Crawler?\n";
            std::cout << MARGIN << "**********************************\n";
            std::cout << MARGIN << "Name: ";

            std::string heroName;
            std::cin >> heroName;

            activeHero = std::make_unique<Hero>(heroName, 100, 15, 5, 30);

            std::cout << "\n"
                      << MARGIN << "**********************************\n";
            std::cout << MARGIN << "Hero " << heroName << " embarks fearlessly into the dungeon!\n";
            std::cout << MARGIN << "**********************************\n";

            activeHero->setPosition(1, 1);

            waitForEnter();
            dungeon(*activeHero, loadedMaps);
            break;
        }
        case 'L':
        {
            std::vector<std::string> savedMap;
            std::unique_ptr<Hero> loadedPlayer = loadGame(savedMap);

            if (loadedPlayer != nullptr)
            {
                activeHero = std::move(loadedPlayer);
                waitForEnter();
                dungeon(*activeHero, loadedMaps, savedMap);
            }
            break;
        }
        case 'E':
            std::cout << "\n"
                      << MARGIN << "Exiting game..\n";
            run = false;
            break;

        default:
            std::cout << "\n"
                      << MARGIN << RED << "ERROR: Wrong input. Try again.\n\n"
                      << RESET;
            break;
        }
    }

    return 0;
}