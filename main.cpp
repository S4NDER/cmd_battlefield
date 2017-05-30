#include <iostream>
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "battlefield.h"

using namespace BattleFields;

#define PRICE_TANK 2500
#define PRICE_SODLIER 100
#define PRICE_RAILGUN 5000
#define PRICE_RADAR 1000

#define SOLDIER 1
#define TANK 2
#define RAILGUN 3
#define RADAR 4

init() {
    //Get the window console handle(is not the right code but works for these sample)
    HWND consoleWindow;
    consoleWindow = GetForegroundWindow();

    //Getting the desktop handle and rectangle
    HWND hwndScreen;
    RECT rectScreen;
    hwndScreen = GetDesktopWindow();
    GetWindowRect( hwndScreen, &rectScreen );

    //Set windows size(see the width problem)
    SetWindowPos( consoleWindow, NULL, 0, 0, 1000, 500, SWP_SHOWWINDOW );

    //Get the current width and height of the console
    RECT rConsole;
    GetWindowRect( consoleWindow, &rConsole );
    int width = rConsole.left = rConsole.right;
    int height = rConsole.bottom - rConsole.top;

    //Calculate the window console to center of the screen
    int consolePosX;
    int consolePosY;
    consolePosX = ( (rectScreen.right-rectScreen.left)/2 - width/2 );
    consolePosY = ( (rectScreen.bottom-rectScreen.top)/2 - height/2 );
    SetWindowPos( consoleWindow, NULL, consolePosX, consolePosY, width, height, SWP_SHOWWINDOW || SWP_NOSIZE);

    std::cout<< "88                                     88               ad88 88            88           88" << std::endl;
    std::cout<< "88                       ,d      ,d    88              d8\"   ""              88           88" << std::endl;
    std::cout<< "88                       88      88    88              88                  88           88" << std::endl;
    std::cout<< "88,dPPYba,  ,adPPYYba, MM88MMM MM88MMM 88  ,adPPYba, MM88MMM 88  ,adPPYba, 88   ,adPPYb,88" << std::endl;
    std::cout<< "88P'    \"8a \"\"     `Y8   88      88    88 a8P_____88   88    88 a8P_____88 88  a8\"    `Y88 " << std::endl;
    std::cout<< "88       d8 ,adPPPPP88   88      88    88 8PP\"\"\"\"\"\"\"   88    88 8PP\"\"\"\"\"\"\" 88  8b       88" << std::endl;
    std::cout<< "88b,   ,a8\" 88,    ,88   88,     88,   88 \"8b,   ,aa   88    88 \"8b,   ,aa 88  \"8a,   ,d88" << std::endl;
    std::cout<< "8Y\"Ybbd8\"'  `\"8bbdP\"Y8   \"Y888   \"Y888 88  `\"Ybbd8\"'   88    88  `\"Ybbd8\"' 88   `\"8bbdP\"Y8" << std::endl;
    std::cout << std::endl;



    return 0;
}

int generateRandomNumber(int maximum, int minimum) {
    int output;
    time_t result = time(NULL);
    output = minimum + (rand() % (int)(maximum - minimum + 1));
    srand((uintmax_t)result);
    std::this_thread::sleep_for (std::chrono::seconds(1));
    return output;
}

int main() {
    init();

    std::string entityMessage = "Select entity: 1[Soldier](100), 2[Tank](2500), 3[Railgun](5000), 4[Radar](1000)";
    std::string playerName;
    std::string coordinate;
    int playerCount = 0;
    int rows = 10;
    int cols = 10;
    int entityID;
    std::vector <std::string> usedTargets;
    std::vector <std::string> usedEntities;

    BattleField * game = new BattleField();

    std::cout << "Enter map dimensions (size of the square):" << std::endl;
    std::cin >> rows;
    cols = rows;

    int minimum = 0;
    int maximum = cols;

    std::cout << "Enter amount of players: [1]YOU vs. AI or [2]PvP." << std::endl;
    std::cin >> playerCount;

    if(playerCount == 1) {
        std::cout << "Player 1, enter your name" << std::endl;
        std::cin >> playerName;
        game->player1.setPlayerName( playerName );
    } else if(playerCount == 2) {
       std::cout << "Player 1, enter your name" << std::endl;
        std::cin >> playerName;
        game->player1.setPlayerName( playerName );

        std::cout << "Player 2, enter your name" << std::endl;
        std::cin >> playerName;
        game->player2.setPlayerName( playerName );
    }

    game->field1.setRowsCols(rows, cols);
    game->field2.setRowsCols(rows, cols);
    game->field1.fillMap();
    game->field2.fillMap();
    game->field1.drawMap();

    if(playerCount == 1) {
        while(game->player1.getSaldo() > 0) {
            std::cout << game->player1.getPlayerName() << std::endl;
            std::cout << entityMessage << std::endl;
            std::cin >> entityID;
            std::cout << "Enter coordinate" << std::endl;
            std::cin >> coordinate;
            std::transform(coordinate.begin(), coordinate.end(),coordinate.begin(), ::toupper);
            game->insertEntity(coordinate, entityID, 1);

            switch( entityID ) {
            case SOLDIER:
                game->player1.setSaldo(game->player1.getSaldo()- PRICE_SODLIER);
                break;
            case TANK:
                game->player1.setSaldo(game->player1.getSaldo()- PRICE_TANK);
                break;
            case RAILGUN:
                game->player1.setSaldo(game->player1.getSaldo()- PRICE_RAILGUN);
                break;
            case RADAR:
                game->player1.setSaldo(game->player1.getSaldo()- PRICE_RADAR);
                break;
            default:
                std::cout << "This is not a valid item" << std::endl;
            }
            std::cout << game->player1.getPlayerName() << " ,your current saldo: " << game->player1.getSaldo() << std::endl;
            game->field1.drawMap();
        }

        while(game->player2.getSaldo() > 0) {
            entityID = generateRandomNumber(4, 1);
regenerate_entity_location:
            std::ostringstream oss2;
            std::string coordinates;
            if (entityID == 1) {
                oss2 << char(generateRandomNumber(maximum-1, minimum) + 'A') << generateRandomNumber(maximum-1, minimum);
            } else if(entityID == 2) {
                oss2 << char(generateRandomNumber(maximum-3, minimum) + 'A') << generateRandomNumber(maximum-2, minimum);
            } else if(entityID == 3 || entityID == 4) {
                oss2 << char(generateRandomNumber(maximum-2, minimum) + 'A') << generateRandomNumber(maximum-2, minimum);
            }
            coordinates = oss2.str();

            for(unsigned int i = 0; i < game->arsenalP2.size(); i++) {
                if(game->arsenalP2[i]->checkHit((int)(coordinates[0]-'A'), (int)(coordinates[1]-'0'))) {
                    std::cout << "This place is already filled" << std::endl;
                    coordinates = "";
                    oss2.clear();
                    goto regenerate_entity_location;
                }
            }
            oss2.clear();

            game->insertEntity(coordinates, entityID, 2);

            switch( entityID ) {
            case SOLDIER:
                game->player2.setSaldo(game->player2.getSaldo()- PRICE_SODLIER);
                break;
            case TANK:
                game->player2.setSaldo(game->player2.getSaldo()- PRICE_TANK);
                break;
            case RAILGUN:
                game->player2.setSaldo(game->player2.getSaldo()- PRICE_RAILGUN);
                break;
            case RADAR:
                game->player2.setSaldo(game->player2.getSaldo()- PRICE_RADAR);
                break;
            default:
                std::cout << "This is not a valid item" << std::endl;
            }
            game->field2.drawMap();
        }

    } else if(playerCount == 2) {
        while(game->player1.getSaldo() > 0) {
            game->field1.drawMap();
            std::cout << game->player1.getPlayerName() << std::endl;
            std::cout << entityMessage << std::endl;
            std::cin >> entityID;
            std::cout << "Enter coordinate" << std::endl;
            std::cin >> coordinate;
            std::transform(coordinate.begin(), coordinate.end(),coordinate.begin(), ::toupper);
            game->insertEntity(coordinate, entityID, 1);

            switch( entityID ) {
            case SOLDIER:
                game->player1.setSaldo(game->player1.getSaldo()- PRICE_SODLIER);
                break;
            case TANK:
                game->player1.setSaldo(game->player1.getSaldo()- PRICE_TANK);
                break;
            case RAILGUN:
                game->player1.setSaldo(game->player1.getSaldo()- PRICE_RAILGUN);
                break;
            case RADAR:
                game->player1.setSaldo(game->player1.getSaldo()- PRICE_RADAR);
                break;
            default:
                std::cout << "This is not a valid item" << std::endl;
            }
            std::cout << game->player1.getPlayerName() << " ,your current saldo: " << game->player1.getSaldo() << std::endl;
            game->field1.drawMap();
        }

        while(game->player2.getSaldo() > 0) {
            game->field2.drawMap();
            std::cout << game->player2.getPlayerName() << std::endl;
            std::cout << entityMessage << std::endl;
            std::cin >> entityID;
            std::cout << "Enter coordinate" << std::endl;
            std::cin >> coordinate;
            std::transform(coordinate.begin(), coordinate.end(),coordinate.begin(), ::toupper);
            game->insertEntity(coordinate, entityID, 2);
            switch( entityID ) {
            case SOLDIER:
                game->player2.setSaldo(game->player2.getSaldo()- PRICE_SODLIER);
                break;
            case TANK:
                game->player2.setSaldo(game->player2.getSaldo()- PRICE_TANK);
                break;
            case RAILGUN:
                game->player2.setSaldo(game->player2.getSaldo()- PRICE_RAILGUN);
                break;
            case RADAR:
                game->player2.setSaldo(game->player2.getSaldo()- PRICE_RADAR);
                break;
            default:
                std::cout << "This is not a valid item" << std::endl;
            }
            std::cout << game->player2.getPlayerName() << " ,your current saldo: " << game->player2.getSaldo() << std::endl;
            game->field2.drawMap();
        }
    }

    if (playerCount == 1) {
        while (true) {
            do {
                game->field1.drawMap();
                if(game->checkGameEnded()) {
                    goto game_has_ended;
                }
                std::cout << game->player1.getPlayerName() <<", enter launch coordinate" << std::endl;
                std::cin >> coordinate;
                std::transform(coordinate.begin(), coordinate.end(),coordinate.begin(), ::toupper);
            } while(game->fire(coordinate[0] - char('A'), coordinate[1] - char('0'), 1));

            do {
                game->field2.drawMap();
                std::cout << "AI's turn" << std::endl;
                if(game->checkGameEnded()) {
                    goto game_has_ended;
                }
                std::ostringstream oss;
regenerate:
                oss.clear();
                oss << char(generateRandomNumber(maximum-1, minimum) + 'A') << generateRandomNumber(maximum, minimum);
                coordinate = oss.str();

                for(unsigned int i = 0; i < usedTargets.size(); i++) {
                    std::cout << usedTargets[i] << std::endl;
                    if(usedTargets[i] == coordinate) {
                        goto regenerate;
                    }
                }
                usedTargets.push_back(coordinate);
                oss.clear();
            } while(game->fire(coordinate[0] - char('A'), coordinate[1] - char('0'), 2));
        }
    } else if(playerCount == 2) {
        while(true) {
            do {
                game->field1.drawMap();
                if(game->checkGameEnded()) {
                    goto game_has_ended;
                }
                std::cout << game->player1.getPlayerName() <<", enter launch coordinate" << std::endl;
                std::cin >> coordinate;
                std::transform(coordinate.begin(), coordinate.end(),coordinate.begin(), ::toupper);
            } while(game->fire(coordinate[0] - char('A'), coordinate[1] - char('0'), 1));
            do {
                game->field2.drawMap();
                if(game->checkGameEnded()) {
                    goto game_has_ended;
                }
                std::cout << game->player2.getPlayerName() <<", enter launch coordinate" << std::endl;
                std::cin >> coordinate;
                std::transform(coordinate.begin(), coordinate.end(),coordinate.begin(), ::toupper);
            } while(game->fire(coordinate[0] - char('A'), coordinate[1] - char('0'), 2));
        }
    }
game_has_ended:
    std::cout << "Game is finished" << std::endl;
    //Cleanup
    delete game;
    return 0;
}
