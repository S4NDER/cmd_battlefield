#include "soldier.h"

namespace BattleFields {

Soldier::Soldier(int row, int col) {
    this->setCost(100);
    this->entityID = 1;
    mapLocationsSize = 1;
    this->setMapLocations(row, col, mapLocationsSize);
}
};
