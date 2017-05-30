#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include "player.h"
#include "soldier.h"
#include "tank.h"
#include "radar.h"
#include "railgun.h"
#include "entity.h"
#include "map.h"

namespace BattleFields {

class BattleField {
    public:
        BattleField();
        Field field1;
        Field field2;
        Player player1;
        Player player2;
        std::vector<Entity*> arsenalP1;
        std::vector<Entity*> arsenalP2;

    public:
        insertEntity(std::string coordinates, int entityID, int playerID);
        bool fire(int row, int col, int playerID);
        bool checkGameEnded(void);
    };
};
