#include "SaveLoad.h"

#include <vector>
#include <string>
#include <fstream>

#include "Hero.h"
#include "Game.h"

void saveGame(Hero &player, std::vector<std::string> &currentMap)
{
    std::ofstream file("savegame.txt");

    if (file.is_open())
    {
        file << player.getName() << "\n";
        file << player.getHitpoints() << "\n";
        file << player.getDamage() << "\n";
        file << player.getDefense() << "\n";
        file << player.getFloor() << "\n";
        file << player.getLVL() << "\n";
        file << player.getXP() << "\n";
        file << player.getX() << "\n";
        file << player.getY() << "\n";

        file << currentMap.size() << "\n";
        for (int i = 0; i < currentMap.size(); i++)
        {
            file << currentMap[i] << "\n";
        }

        file.close();
        std::cout << GREEN << "Game successfully saved." << RESET << "\n";
    }
    else
    {
        std::cout << RED << "ERROR: Nepodarilo se vytvorit soubor savegame.txt" << RESET << "\n";
    }
}

std::unique_ptr<Hero> loadGame(std::vector<std::string> &loadedMap)
{
    std::ifstream file("savegame.txt");

    if (file.is_open())
    {
        std::string loadedName;
        int loadedHP, loadedDMG, loadedDEF, loadedFloor, loadedlvl, loadedxp, loadedX, loadedY;

        file >> loadedName;
        file >> loadedHP;
        file >> loadedDMG;
        file >> loadedDEF;
        file >> loadedFloor;
        file >> loadedlvl;
        file >> loadedxp;
        file >> loadedX;
        file >> loadedY;

        file.close();

        auto loadedHero = std::make_unique<Hero>(loadedName, loadedHP, loadedDMG, loadedDEF, 30);

        loadedHero->setLevel(loadedlvl);
        loadedHero->setXP(loadedxp);
        loadedHero->setFloor(loadedFloor);
        loadedHero->setPosition(loadedX, loadedY);

        int mapSize;
        file >> mapSize;
        loadedMap.clear();

        for (int i = 0; i < mapSize; i++)
        {
            std::string row;
            file >> row;
            loadedMap.push_back(row);
        }

        std::cout << GREEN << "Game successfully loaded! Welcome back, " << loadedName << "." << RESET << "\n";

        return loadedHero;
    }
    else
    {
        std::cout << RED << "ERROR: No save file found." << RESET << "\n";
        return nullptr;
    }
}