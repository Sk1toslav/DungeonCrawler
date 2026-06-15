#pragma once
#include <vector>
#include <string>
#include "Hero.h"
#include "Enemy.h"

std::vector<std::vector<std::string>> loadMaps(std::string filename);
void clearScreen();
void waitForEnter();
void mapvisual(Hero &player, std::vector<std::string> &map);
bool encounter(Hero &player, Enemy &enemy);
void dungeon(Hero &player, std::vector<std::vector<std::string>> &allMaps);