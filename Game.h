#pragma once
#include <vector>
#include <string>
#include "Hero.h"
#include "Enemy.h"

const std::string RESET = "\033[0m";
const std::string RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";
const std::string YELLOW = "\033[1;33m";

std::vector<std::vector<std::string>> loadMaps(std::string filename);
void clearScreen();
void waitForEnter();
void mapvisual(Hero &player, std::vector<std::string> &map);
bool encounter(Hero &player, Enemy &enemy);
void dungeon(Hero &player, std::vector<std::vector<std::string>> &allMaps, std::vector<std::string> savedMap = {});