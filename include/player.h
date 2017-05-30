#pragma once

#include <iostream>

namespace BattleFields {

class Player {
    public:
        Player();

    public:
        setPlayerName( std::string playerName );
        setSaldo( int amount );

    public:
        int getSaldo( void );
        std::string getPlayerName( void );

    private:
        std::string playerName;
        int saldo;
    };
};
