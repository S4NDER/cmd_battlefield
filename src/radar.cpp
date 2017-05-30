#include "radar.h"

namespace BattleFields {

Radar::Radar(int row, int col) {
    this->setCost(1000);
    this->entityID = 4;
    mapLocationsSize = 4;
    this->setMapLocations(row, col, mapLocationsSize);
}
};
