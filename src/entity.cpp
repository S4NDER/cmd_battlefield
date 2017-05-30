#include "entity.h"

namespace BattleFields {

Entity::Entity() {
    this->setHealth(100);
    this->alive = true;
}

Entity::setHealth (double health) {
    //Sets the health of an entity
    this->health = health;
    return 0;
}

Entity::setCost (int cost) {
    //Sets the cost of an entity
    this->cost = cost;
    return 0;
}

double Entity::getHealth(void) {
    //Returns the health of an entity
    return health;
}

int Entity::getCost (void) {
    //Returns the cost of an entity
    return cost;
}

Entity::setMapLocations(int initRow, int initCol, int mapLocationsSize) {
    // Locations is stored as "5 4" (row col)
    for(int i = 0; i < mapLocationsSize; i++) {
        std::ostringstream oss;
        std::ostringstream oss2;

        oss << initRow << initCol;
        mapLocations[i] = oss.str();
        oss.clear();

        oss2 << initRow << initCol+1;
        mapLocations[i+1] = oss2.str();
        oss2.clear();

        initRow += 1;
        i++;
    }
    return 0;
}

bool Entity::checkHit(int row, int col) {
    bool isHit = false;

    std::ostringstream oss;
    oss << row << col;

    std::string targetLocation = oss.str();
    oss.clear();
    for(unsigned int i = 0; i < (sizeof(mapLocations)/sizeof(*mapLocations)); i++) {
        if(mapLocations[i] == targetLocation ) {
            isHit = true;
            std::cout << "HIT" << std::endl;
            break;
        }
    }
    return isHit;
}

Entity::updateHealth(int updatedHealth) {
    this->health += updatedHealth;
    if (health <= 5) {
        this->setDeath();
        std::cout << "MAN DOWN, MAN DOWN!!!" << std::endl;
        system("pause");
    }
    return 0;
}

bool Entity::getAliveStatus(void){
    return alive;
}

Entity::setDeath(void){
    this->alive = false;
    return 0;
}

int Entity::getEntityID(void) {
    return entityID;
}
};
