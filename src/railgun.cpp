#include "railgun.h"

namespace BattleFields {

Railgun::Railgun(int row, int col) {
    this->setCost(5000);
    this->entityID = 3;
    mapLocationsSize = 4;
    this->setMapLocations(row, col, mapLocationsSize);
}
};
