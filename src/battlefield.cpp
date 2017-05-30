#include "battlefield.h"

#define SHOT 0
#define SOLDIER 1
#define TANK 2
#define RAILGUN 3
#define RADAR 4

namespace BattleFields {

BattleField::BattleField() {
    //ctor
}

BattleField::insertEntity(std::string coordinates, int entityID, int playerID) {
    int row = coordinates[0] - char('A');
    int col = coordinates[1] - char('0');

    switch( entityID ) {
    case SOLDIER:
        if(playerID ==1)
            arsenalP1.push_back(new Soldier(row, col));
        if(playerID ==2)
            arsenalP2.push_back(new Soldier(row, col));
        break;
    case TANK:
        if(playerID ==1)
            arsenalP1.push_back(new Tank(row, col));
        if(playerID ==2)
            arsenalP2.push_back(new Tank(row, col));
        break;
    case RAILGUN:
        if(playerID ==1)
            arsenalP1.push_back(new Railgun(row, col));
        if(playerID ==2)
            arsenalP2.push_back(new Railgun(row, col));
        break;
    case RADAR:
        if(playerID ==1)
            arsenalP1.push_back(new Radar(row, col));
        if(playerID ==2)
            arsenalP2.push_back(new Radar(row, col));
        break;
    default:
        std::cout << "This is not a valid item" << std::endl;
    }

    if(playerID == 1)
        field1.insertEntity(row, col, entityID);
    if(playerID == 2)
        field2.insertEntity(row, col, entityID);

    return 0;
}

bool BattleField::fire(int row, int col, int playerID) {
    bool isHit = false;

    if(playerID == 1) {
        for(Entity* e : arsenalP2) {
            if(e->checkHit(row, col)) {
                switch(e->getEntityID()) {
                case SOLDIER:
                    e->updateHealth(-100);
                    break;

                case TANK:
                    e->updateHealth(-100/6);
                    break;

                case RAILGUN:
                    e->updateHealth(-25);
                    break;

                case RADAR:
                    e->updateHealth(-25);
                    break;

                default:
                    std::cout << "This is not a valid item" << std::endl;
                    break;
                }
                field1.insertEntity(row, col, 0);
                field2.insertEntity(row, col, 0);
                isHit = true;
                goto end_fire_loop;
            } else {
                std::cout << "MISSED" << std::endl;
                field1.insertEntity(row, col, 5);
                isHit = false;
            }
        }
    }
    if (playerID == 2) {
        for(Entity* e : arsenalP1) {
            if(e->checkHit(row, col)) {
                switch(e->getEntityID()) {
                case SOLDIER:
                    e->updateHealth(-100);
                    break;

                case TANK:
                    e->updateHealth(-100/6);
                    break;

                case RAILGUN:
                    e->updateHealth(-25);
                    break;

                case RADAR:
                    e->updateHealth(-25);
                    break;

                default:
                    std::cout << "This is not a valid item" << std::endl;
                }
                field1.insertEntity(row, col, 0);
                field2.insertEntity(row, col, 0);
                isHit = true;
                goto end_fire_loop;
            } else {
                std::cout << "MISSED" << std::endl;
                field2.insertEntity(row, col, 5);
                isHit = false;
            }
        }
    }
end_fire_loop:
    return isHit;
}

bool BattleField::checkGameEnded(void) {
    bool game_is_ended = false;
    bool player1lost = true;
    bool player2lost = true;

    for(Entity* e : arsenalP1) {
        if(e->getAliveStatus()) {
            player1lost = false;
            break;
        }
    }

    for(Entity* d : arsenalP2) {
        if(d->getAliveStatus()) {
            player2lost = false;
            break;
        }
    }

    if( player1lost || player2lost ) {
        game_is_ended = true;
    }
    return game_is_ended;
}
};
