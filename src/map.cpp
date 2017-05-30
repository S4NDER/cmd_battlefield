#include "map.h"

#define SHOT 0
#define SOLDIER 1
#define TANK 2
#define RAILGUN 3
#define RADAR 4
#define MISS 5

#define M_HIT 88
#define M_MISS 79
#define M_EMPTY 46
#define M_SOLDIER 83
#define M_TANK 84
#define M_RAILGUN 71
#define M_RADAR 82

namespace BattleFields {

Field::Field() {
    //ctor
}

Field::drawMap( void ) {
    system("cls");

    std::cout << "   ";
    for(int i = 0; i<ROWS; i++) {
        std::cout << char('0'+ i)  << " ";
    }

    for(int i = 0; i<ROWS; i++) {
        std::cout << "\n" << char('A'+ i) << " |";
        for(int k = 0; k<COLS; k++) {
            std::cout << battleMap[i][k] << "|";
        }
    }
    std::cout << std::endl;
    return 0;
}

Field::setRowsCols(int rows, int cols) {
    //Dynamic allocation
    this->ROWS = rows;
    this->COLS = cols;

    battleMap = new char*[rows];
    for(int i = 0; i < rows; ++i) {
        battleMap[i] = new char[cols];
    }
    return 0;
}

Field::insertEntity( int row, int col, int entityID) {
    switch( entityID ) {
    case SHOT:
        battleMap[row][col] = char(M_HIT);
        break;

    case SOLDIER:
        battleMap[row][col] = char(M_SOLDIER);
        break;

    case TANK:
        for(int i=0; i<3; i++) {
            battleMap[row+i][col] = char(M_TANK);
            battleMap[row+i][col+1] = char(M_TANK);
        }
        break;

    case RAILGUN:
        //Code
        for(int i=0; i<2; i++) {
            battleMap[row+i][col] = char(M_RAILGUN);
            battleMap[row+i][col+1] = char(M_RAILGUN);
        }
        break;

    case RADAR:
        //Code
        for(int i=0; i<2; i++) {
            battleMap[row+i][col] = char(M_RADAR);
            battleMap[row+i][col+1] = char(M_RADAR);
        }
        break;

    case MISS:
        battleMap[row][col] = char (M_MISS);
        break;

    default:
        std::cout << "This is not a valid item" << std::endl;
    }
    return 0;
}

Field::fillMap ( void ) {
    for(int a = 0; a<ROWS; a++) {
        for(int b = 0; b<COLS; b++) {
            battleMap[a][b] = char(M_EMPTY);
        }
    }
    return 0;
}
};
