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

    std::cout << "\n\n**********************************\n";
    std::cout << "  Welcome to Dungeon Crawler \n";
    std::cout << "**********************************\n\n";

    std::vector<std::vector<std::string>> loadedMaps = loadMaps("maps.txt");

    if (loadedMaps.empty())
    {
        std::cout << RED << "ERROR: Mapa nenactena, zkontroluj maps.txt\n"
                  << RESET;
        return 1;
    }

    std::unique_ptr<Hero> activeHero = nullptr;

    bool run = true;
    while (run)
    {
        std::string volbaInput;
        std::cout << "\nStart new run (N) | Load save (L) | Graveyard (G) | Exit game (E)\n";
        std::cout << "Action: ";
        std::cin >> volbaInput;

        if (volbaInput.length() > 1)
        {
            std::cout << "\n"
                      << RED << "ERROR: Input only one character!\n"
                      << RESET;
            continue;
        }

        char volba = volbaInput[0];
        switch (toupper(volba))
        {
        case 'N':
        {
            std::cout << "\n**********************************\n";
            std::cout << "What is your name Crawler?\n";
            std::cout << "**********************************\n";
            std::cout << "Name: ";

            std::string heroName;
            std::cin >> heroName;

            activeHero = std::make_unique<Hero>(heroName, 100, 15, 5, 30);

            std::cout << "\n**********************************\n";
            std::cout << "Hero " << heroName << " embarks fearlessly into the dungeon!\n";
            std::cout << "**********************************\n";

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
        case 'G':
            showGraveyard();
            waitForEnter();
            break;
        case 'E':
            std::cout << "\nExiting game..\n";
            run = false;
            break;

        default:
            std::cout << "\n"
                      << RED << "ERROR: Wrong input. Try again.\n\n"
                      << RESET;
            break;
        }
    }

    return 0;
}