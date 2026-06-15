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
            Hero player(heroName, 100, 15, 5, 30);

            
            std::cout << "******************************\n";
            std::cout << "Hero " << heroName << " embarks fearlessly into the dungeon!\n";
            std::cout << "******************************\n";

            player.setPosition(1, 1);

            waitForEnter();
            dungeon(player, loadedMaps);
            break;
        }

        case 'S':
            /**/
            break;

        case 'L':
            /**/
            break;

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
