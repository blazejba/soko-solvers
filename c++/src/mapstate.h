#ifndef MAPSTATE_H
#define MAPSTATE_H
#include <vector>


class MapState
{
public:
    MapState(int mapSizeX, int mapSizeY);
    void updatePlayerPosition(int posX, int posY);
    int getObjectFromMap(int coordX, int coordY);
    Player getPlayerPosition();
    MatrixXd getMap();
    MatrixXd map;
    Player player;
    std::string parent;
    int score;
    int player_steps;
    int push_steps;

    int total_distance;
    void calculateScore(int number_of_depos, std::vector<int> depoLocations);
    void generateID();
    std::string movement;
    std::string ID;
};

#endif // MAPSTATE_H
