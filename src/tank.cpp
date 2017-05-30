#include "tank.h"

namespace BattleFields {

Tank::Tank(int row, int col) {
    this->setCost(2500);
    this->entityID = 2;
    mapLocationsSize = 6;
    this->setMapLocations(row, col, mapLocationsSize);
}
};
