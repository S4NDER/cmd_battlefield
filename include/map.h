#pragma once

#include <iostream>
#include <conio.h>
#include <stdlib.h>

namespace BattleFields {

class Field {
    public:
        Field();

    public:
        char **battleMap;
        drawMap(void);
        insertEntity(int row, int col, int entityID);
        fillMap (void);
        setRowsCols(int rows, int cols);
        int getRow(void);
        int getCol(void);

    protected:

    private:
        int ROWS;
        int COLS;
    };
};
