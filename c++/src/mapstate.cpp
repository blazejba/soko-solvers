#include "mapstate.h"
#include <string>

MapState::MapState(int mapSizeX, int mapSizeY)
{
    map = MatrixXd(mapSizeY, mapSizeX);
}

void MapState::updatePlayerPosition(int posX, int posY){
    player.x_coord = posX;
    player.y_coord = posY;
}

Player MapState::getPlayerPosition(){
    return player;
}

MatrixXd MapState::getMap(){
    return map;
}

int MapState::getObjectFromMap(int coordX, int coordY){
    return map(coordY, coordX);
}

void MapState::calculateScore(int number_of_depos, std::vector<int> depoLocations){
    int free_depos = 0;
    total_distance = total_distance + player_steps;
    for(int i = 0; i < number_of_depos; i++){
        int x = depoLocations[2*i];
        int y = depoLocations[2*i + 1];
        if(map(y, x) == 2 || map(y, x) == 9 ){
            free_depos++;
        }
    }
score = /*push_steps + free_depos +*/ total_distance;


}

void MapState::generateID(){
    // scans through the map, excluding the edges (since there are always filled with zeros)
    // generates an unique id based on the map state, storing all numbers exluding 0 [zeros are obstacles]
    int object;
    char c;
    for(int x = 1; x < map.cols() - 1; x++){
        for(int y = 1; y < map.rows() - 1; y++){
            object = map(y, x);
            if(object != 0){
            if(object == 1){
                c = '1';
            } else if (object == 2){
                c = '2';
            } else if (object == 3){
                c = '3';
            } else if (object == 4){
                c = '4';
            } else if (object == 5){
                c = '5';
            } else if (object == 6){
                c = '6';
            } else if (object == 8){
                c = '8';
            } else if (object == 9){
                c = '9';
            }
            ID.push_back(c);
            }

        }
    }
}
