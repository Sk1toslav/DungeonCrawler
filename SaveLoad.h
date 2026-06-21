#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Hero.h"

void saveGame(Hero &player, std::vector<std::string> &currentMap);

std::unique_ptr<Hero> loadGame(std::vector<std::string> &loadedMap);

void recordDeath(Hero &player);

void showGraveyard();