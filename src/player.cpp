#include "player.h"

namespace BattleFields {

Player::Player() {
    //ctor
    saldo = 5000;
}

Player::setPlayerName( std::string playerName ) {
    this->playerName = playerName;
    return 0;
}

std::string Player::getPlayerName( void ) {
    return playerName;
}

Player::setSaldo (int amount ) {
    this->saldo = amount;
    return 0;
}

int Player::getSaldo( void ) {
    return saldo;
}
};
