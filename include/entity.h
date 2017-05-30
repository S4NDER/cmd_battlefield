#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <conio.h>

namespace BattleFields {

class Entity {
    public:
        Entity();

    public:
        double getHealth(void);
        int getCost (void);
        int getEntityID (void);
        std::string mapLocations[6];
        bool getAliveStatus(void);
        bool checkHit (int row, int col);

    public:
        setMapLocations (int initRow, int initCol, int mapLocationsSize);
        setHealth (double health);
        setCost (int cost);
        updateHealth(int updatedHealth);

    protected:
        int cost;
        int entityID;
        int mapLocationsSize;
        double health;
        bool alive;

    protected:
        setDeath(void);
    };
};
