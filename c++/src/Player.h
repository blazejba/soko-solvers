#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
using namespace Eigen;

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player();
    void findPlayer(MatrixXd);
    void updateLocation(int, int);
    int x_coord, y_coord;
};

#endif

Player::Player(){
    // Constructor
}

void Player::findPlayer(MatrixXd map){
    int mapSizeX = map.cols();
    int mapSizeY = map.rows();

    for(int x = 0; x < mapSizeX; x++){
        for(int y = 0; y < mapSizeY; y++){
            if(map(y,x) == 8 || map(y,x) == 4 || map(y,x) == 9){
                x_coord = x;
                y_coord = y;
            }
        }
    }
}

void Player::updateLocation(int x, int y){
    x_coord = x;
    y_coord = y;
}
