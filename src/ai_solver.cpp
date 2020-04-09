#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Eigen/Dense>
#include "Player.h"
#include "mapstate.h"
#include "mapstate.cpp"
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include <set>

using namespace std;
using namespace std::chrono;
using namespace Eigen;

int mapSizeX;
int mapSizeY;

#define EMPTY_SPACE 1
#define CRATE 5
#define DEPO 2
#define OBSTACLE 0
#define PLAYER 8
#define CRATE_ON_DEPO 6
#define PLAYER_ON_DEPO 9
#define DEADLOCK 3
#define PLAYER_ON_DEADLOCK 4
#define CRATE_ON_DEADLOCK 7

// for flood fill
#define VISITED 7

#define A_STAR 2
#define BREADTH_FIRST 1
#define DEPTH_FIRST 0

int searchingMethod = BREADTH_FIRST;
int number_of_depos;
vector<int> depoLocations;

// how can i detect more deadlocks?
// breadth first with some sorting?

struct direction {
    int x;
    int y;
    string movement;
} UP, DOWN, LEFT, RIGHT;

struct localization{
    int x;
    int y;
};

bool onGoingDeadlockDetector(MapState state);
void updateOpenList(MapState new_state);
void updatedVistedStates(MapState state);

// GLOBAL STATE VARIABLES
vector<MapState> openStates;
vector<MapState> closedStates;
MapState currentState(mapSizeX, mapSizeY);
std::set<std::string> closedStates_dictionary;
std::set<std::string> openStates_dictionary;

Player player;
vector<direction> directions;

void assignSearchingMethod(std::string methodName){
    if(methodName == "DF"){
        searchingMethod = DEPTH_FIRST;
    } else if(methodName == "BF"){
        searchingMethod = BREADTH_FIRST;
    } else{
        searchingMethod = A_STAR;
    }
}

void findDepos(){
    // find x and y position for all depos
    // depoLocations is only used in isWinState() function to optimize it
    number_of_depos = 0;
    for(int x = 1; x < mapSizeX - 1; x++){
        for(int y = 1; y < mapSizeY - 1; y++){
            if(currentState.map(y, x) == DEPO || currentState.map(y, x) == CRATE_ON_DEPO || currentState.map(y, x) == PLAYER_ON_DEPO){
                number_of_depos++;
                depoLocations.push_back(x);
                depoLocations.push_back(y);
            }
        }
    }
}

bool isWinState(){
    // returns 0 when at least one depo without a crate on it was found
    // returns 1 when all depos have crates on
    int x;
    int y;
    for(int i = 0; i < depoLocations.size()/2; i++){
        x = depoLocations[2*i];
        y = depoLocations[2*i + 1];
        if(currentState.map(y, x) == DEPO || currentState.map(y, x) == PLAYER_ON_DEPO){
            return 0; // free depo found - it's not a win state
        }
    }
    return 1; // no free depos found - game won
}

bool checkIfStateIsInOpen(MapState state){
    int size_before = openStates_dictionary.size();
    openStates_dictionary.insert(state.ID);
    int size_after = openStates_dictionary.size();
    if(size_after > size_before){
        return 0; //state was not in open
    } else{
        return 1; //size of open didnt increase so element like state was already there
    }

}

bool checkIfStateWasVisited(MapState state){
    //search through closed state dictionary to not be in the same state twice

    if(closedStates_dictionary.find(state.ID) != closedStates_dictionary.end()) {
        return 1; // yes, this state was visited before
    }
    else {
        return 0; // no, states was not visited yet
    }
}

bool moveLegibilityCheck(direction dir){
    // checks if for the current state of a map, a move in a given direction is legit
    // returns 1 when a move is legit, 0 when it's not
    int x = currentState.getPlayerPosition().x_coord + dir.x;
    int y = currentState.getPlayerPosition().y_coord + dir.y;
    int object = currentState.getObjectFromMap(x, y);

    int objectBehindCrate;


    switch(object){
        case EMPTY_SPACE: //always a legit step
            return 1;

        case CRATE: //legit if there is nothing behind it
            objectBehindCrate = currentState.getObjectFromMap(x + dir.x, y + dir.y);
            if (objectBehindCrate == EMPTY_SPACE || objectBehindCrate == DEPO){
                return 1; //legit move, since there is nothing behind a crate
            } else{
                return 0; //illegal move, something is behind a crate
            }

        case DEPO: //always legit
            return 1;

        case OBSTACLE: //always illegal
            return 0;

        case CRATE_ON_DEPO: //depo with crate on; legit if there is nothing behind it
            objectBehindCrate = currentState.getObjectFromMap(x + dir.x, y + dir.y);
            if (objectBehindCrate == EMPTY_SPACE || objectBehindCrate == DEPO){
                return 1; //legit move, since there is nothing behind a crate
            } else{
                return 0; //illegal move, something is behind a crate
            }

        case DEADLOCK: //always legit
            return 1;
    }

}

MapState translateMapState(localization crate, direction push){
    int player_pos_x = currentState.getPlayerPosition().x_coord;
    int player_pos_y = currentState.getPlayerPosition().y_coord;

    int crate_object = currentState.getObjectFromMap(crate.x, crate.y);
    int push_destination_object = currentState.getObjectFromMap(crate.x + push.x, crate.y + push.y);
    int player_object = currentState.getObjectFromMap(player_pos_x, player_pos_y);

    MapState new_state(mapSizeX, mapSizeY);
    new_state.map = currentState.map;
    new_state.updatePlayerPosition(crate.x, crate.y);
    new_state.parent = currentState.ID;
    new_state.push_steps = currentState.push_steps + 1;
    new_state.movement = push.movement;

    if(player_object == push_destination_object){
        switch(push_destination_object){
            case PLAYER:
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE;
                break;

            case PLAYER_ON_DEPO:
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE_ON_DEPO;
                break;

            case EMPTY_SPACE:
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE;
                break;

            case DEPO:
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE_ON_DEPO;
                break;

            case DEADLOCK: // just for test, it is a wrong case, should be prevented but isnt
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE_ON_DEADLOCK;
                break;
        }
    } else{
        switch(player_object){
            case PLAYER:
                new_state.map(player_pos_y, player_pos_x) = EMPTY_SPACE;
                break;

            case PLAYER_ON_DEPO:
                new_state.map(player_pos_y, player_pos_x) = DEPO;
                break;

            case PLAYER_ON_DEADLOCK:
                new_state.map(player_pos_y, player_pos_x) = DEADLOCK;
                break;
        }

        switch(push_destination_object){
            case PLAYER:
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE;
                break;

            case PLAYER_ON_DEPO:
                new_state.map(crate.y + push.y, crate.x + push.x) = DEPO;
                break;

            case EMPTY_SPACE:
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE;
                break;

            case DEPO:
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE_ON_DEPO;
                break;

            case DEADLOCK: // just for test, it is a wrong case, should be prevented but isnt
                //cout << "THIS SHOULDN'T HAPPENEN!" << endl;
                new_state.map(crate.y + push.y, crate.x + push.x) = CRATE_ON_DEADLOCK;
                break;
        }
    }


    switch(crate_object){
        case CRATE:
            new_state.map(crate.y, crate.x) = PLAYER;
            break;

        case CRATE_ON_DEPO:
            new_state.map(crate.y, crate.x) = PLAYER_ON_DEPO;
            break;
    }

    if(searchingMethod == A_STAR){
        new_state.total_distance = currentState.total_distance;
    }
    new_state.generateID();
    return new_state;
}

void findAllCrates(vector<localization>& crates){
    for(int x = 1; x < currentState.map.cols() - 1; x++){
        for(int y = 1; y < currentState.map.rows() - 1; y++){
            if( currentState.map(y, x) == CRATE || currentState.map(y, x) == CRATE_ON_DEPO){
                localization crate;
                crate.x = x;
                crate.y = y;
                crates.push_back(crate);
            }
        }
    }
}

bool crateMoveLegibilityCheck(localization crate, direction dir){
    // check what is staying on the push destination field
    if(currentState.map(crate.y + dir.y, crate.x + dir.x) == EMPTY_SPACE || currentState.map(crate.y + dir.y, crate.x + dir.x) == DEPO || currentState.map(crate.y + dir.y, crate.x + dir.x) == PLAYER || currentState.map(crate.y + dir.y, crate.x + dir.x) == PLAYER_ON_DEPO){
        // check if something is behind the object
        if(currentState.map(crate.y - dir.y, crate.x - dir.x) == EMPTY_SPACE || currentState.map(crate.y - dir.y, crate.x - dir.x) == DEADLOCK || currentState.map(crate.y - dir.y, crate.x - dir.x) == DEPO || currentState.map(crate.y - dir.y, crate.x - dir.x) == PLAYER_ON_DEPO || currentState.map(crate.y - dir.y, crate.x - dir.x) == PLAYER ||  currentState.map(crate.y - dir.y, crate.x - dir.x) == PLAYER_ON_DEADLOCK){

            if(currentState.map(crate.y + dir.y, crate.x + dir.x) == CRATE){
                cout << "WHAT THA FUCK?" << endl;
            }
            return true; // move legit
        }
    }
    return false; // move not legit
}

void findAllPushes(localization crate, vector<direction>& pushes){
    if(crateMoveLegibilityCheck(crate, UP)){
        pushes.push_back(UP);
    }
    if(crateMoveLegibilityCheck(crate, DOWN)){
        pushes.push_back(DOWN);
    }
    if(crateMoveLegibilityCheck(crate, LEFT)){
        pushes.push_back(LEFT);
    }
    if(crateMoveLegibilityCheck(crate, RIGHT)){
        pushes.push_back(RIGHT);
    }
}


struct floodplayer{
    int x;
    int y;
    int steps;
};

void checkFieldForExpansion(MatrixXd& map, floodplayer player, direction dir, vector<floodplayer>& open){
    if(map(player.y + dir.y, player.x + dir.x) == EMPTY_SPACE || map(player.y + dir.y, player.x + dir.x) == DEPO || map(player.y + dir.y, player.x + dir.x) == DEADLOCK){
        map(player.y + dir.y, player.x + dir.x) = VISITED;
        floodplayer new_player;
        new_player.x = player.x + dir.x;
        new_player.y = player.y + dir.y;
        new_player.steps = player.steps + 1;
        open.push_back(new_player);
    }
}

bool checkIfPlayerCanPush(localization crate, direction push, int& steps){
    //flood fill
    //amount of steps needed to reach the point
    MatrixXd map = currentState.map;
    Player player = currentState.player;
    vector<floodplayer> open;
    floodplayer start;
    start.x = player.x_coord;
    start.y = player.y_coord;
    start.steps = 0;
    open.push_back(start);
    localization destination;
    destination.x = crate.x - push.x;
    destination.y = crate.y - push.y;

    while(open.size() > 0){
        if(destination.x == open[0].x && destination.y == open[0].y){
            steps = open[0].steps;
            return 1; //reachable for player
        }

        checkFieldForExpansion(map, open[0], UP, open);
        checkFieldForExpansion(map, open[0], DOWN, open);
        checkFieldForExpansion(map, open[0], LEFT, open);
        checkFieldForExpansion(map, open[0], RIGHT, open);

        open.erase(open.begin());
    }

    return 0; //player can't push this crate from his current position
}

void findNewMoves(){
    //cout <<"Open size before finding new moves: " << openStates.size() << endl;

    vector<localization> crates;
    findAllCrates(crates);
    vector<direction> pushes;
    MapState new_state(mapSizeX, mapSizeY);
    int steps;
    for(int i = 0; i < crates.size(); i++){

        findAllPushes(crates[i], pushes);
        for(int j = 0; j < pushes.size(); j++){
            new_state = translateMapState(crates[i], pushes[j]);

            if(checkIfStateWasVisited(new_state) == 0){
                if(checkIfPlayerCanPush(crates[i], pushes[j], steps)){
                    if(onGoingDeadlockDetector(new_state) == 0){
                        new_state.player_steps = steps;
                        new_state.calculateScore(number_of_depos, depoLocations);
                        updateOpenList(new_state);
                    } else{
                        updatedVistedStates(new_state);
                    }
                }
            }
        }
        pushes.clear();

    }
}

void updateOpenList(MapState new_state){
    if(checkIfStateIsInOpen(new_state)){
        goto end_of_loop;
    }

    if(searchingMethod == DEPTH_FIRST) {
        openStates.insert(openStates.begin(), new_state);

    } else if(searchingMethod == BREADTH_FIRST){
        openStates.push_back(new_state);

    } else if(searchingMethod == A_STAR){ // A*
        //cout << "A_STAR " << new_state.score << endl;

        if(openStates.size() == 0){ // || openStates.back().score >= new_state.score
            openStates.push_back(new_state);
        } else{
            for(int i = 0; i < openStates.size();){
                if(new_state.score >= openStates[i].score){
                    //cout << "new state score: " << new_state.score << endl;
                    i++;
                } else {
                    // insert before the i element
                    openStates.insert(openStates.begin() + i, new_state);

                    goto end_of_loop;
                }
            }

        }
        openStates.push_back(new_state);
    }
    end_of_loop: ;
}

bool onGoingDeadlockDetector(MapState state){
    //return 1 when deadlock is detected in a state
    vector<int> kernel(4);
    int crate_counter = 0;
    int crate_on_depo_counter = 0;
    int obstacle_counter = 0;
    int deadlock_counter = 0;
    MatrixXd map = state.map;

    for(int y = 0; y < map.rows() - 1; y++){
        for(int x = 0; x < map.cols() - 1; x++){
            kernel[0] = map(y, x);
            kernel[1] = map(y, x + 1);
            kernel[2] = map(y + 1, x);
            kernel[3] = map(y + 1, x + 1);

            for(int i = 0; i < kernel.size(); i++){
                if(kernel[i] == CRATE){
                    crate_counter++;

                } else if(kernel[i] == CRATE_ON_DEPO){
                    crate_on_depo_counter++;

                } else if(kernel[i] == DEADLOCK || kernel[i] == PLAYER_ON_DEADLOCK){
                    deadlock_counter++;

                } else if (kernel[i] == OBSTACLE){
                    obstacle_counter++;
                }
            }

            switch(crate_counter){
                case 1:
                    if(obstacle_counter == 1 && crate_on_depo_counter == 2){
                        return 1;

                    } else if(deadlock_counter == 1 && crate_on_depo_counter == 2){
                        return 1;

                    } else if(crate_on_depo_counter == 3){
                        return 1;

                    } else if(obstacle_counter == 2 && crate_on_depo_counter == 1){
                        return 1;
                    }

                    crate_counter = 0;
                    obstacle_counter = 0;
                    deadlock_counter = 0;
                    crate_on_depo_counter = 0;

                    break;

                case 2:
                    if(obstacle_counter == 2){
                        return 1;

                    } else if (obstacle_counter == 1 && crate_on_depo_counter == 1){
                        return 1;

                    } else if (crate_on_depo_counter == 2){
                        return 1;
                    }
                    crate_counter = 0;
                    obstacle_counter = 0;
                    deadlock_counter = 0;
                    crate_on_depo_counter = 0;

                    break;

                case 3:
                    if(obstacle_counter == 1 || deadlock_counter == 1 || crate_on_depo_counter == 1){
                        return 1;
                    }
                    crate_counter = 0;
                    obstacle_counter = 0;
                    deadlock_counter = 0;
                    crate_on_depo_counter = 0;

                    break;

                case 4:
                    return 1;

                default:
                    crate_counter = 0;
                    obstacle_counter = 0;
                    deadlock_counter = 0;
                    crate_on_depo_counter = 0;

                    break;
            }
        }
    }

    return 0;
}


void updatedVistedStates(MapState state){
    closedStates_dictionary.insert(state.ID);
    closedStates.push_back(state);
}

void defineDirectionConstants(){
    UP.x = 0;
    UP.y = -1;
    UP.movement = "U";
    DOWN.x = 0;
    DOWN.y = 1;
    DOWN.movement = "D";
    LEFT.x = -1;
    LEFT.y = 0;
    LEFT.movement = "L";
    RIGHT.x = 1;
    RIGHT.y = 0;
    RIGHT.movement = "R";

    directions.push_back(UP);
    directions.push_back(DOWN);
    directions.push_back(LEFT);
    directions.push_back(RIGHT);
}

void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);

    matrix.conservativeResize(numRows,numCols);
}

void initialDeadlockDetector(MatrixXd& map){
    // find all corners;
    MatrixXd kernel(2,2);
    for(int y = 0; y < map.rows() - 1; y++){
        for(int x = 0; x < map.cols() - 1; x++){
            kernel << map(y, x), map(y, x + 1), map(y + 1, x),  map(y + 1, x + 1);
            if (kernel.sum() == 1){
                if( map(y, x) == 1 ){
                    map(y, x) = DEADLOCK;
                } else if( map(y, x + 1) == 1 ){
                    map(y, x + 1) = DEADLOCK;
                } else if( map(y + 1, x) == 1){
                    map(y + 1, x) = DEADLOCK;
                } else{
                    map(y + 1, x + 1) = DEADLOCK;
                }
            } else if(kernel.sum() == 8){
                if( map(y, x) == 8 ){
                    map(y, x) = PLAYER_ON_DEADLOCK;
                } else if( map(y, x + 1) == 8 ){
                    map(y, x + 1) = PLAYER_ON_DEADLOCK;
                } else if( map(y + 1, x) == 8){
                    map(y + 1, x) = PLAYER_ON_DEADLOCK;
                } else if( map(y + 1, x + 1) == 8) {
                    map(y + 1, x + 1) = PLAYER_ON_DEADLOCK;
                }
            }
            // deadlock is when there are exactly 3 obstacles around and one empty space;
        }
    }
}



void loadProblemFromTxtFile(const char* path){
    ifstream problemFile;
    problemFile.open(path);
    char output[100];
    int sizeCounter = 0;
    MatrixXd initMap(1,1);
    if (problemFile.is_open()) {
        while (!problemFile.eof()) {
            problemFile >> output;
            if(sizeCounter == 0){
                mapSizeX = strlen(output);
                initMap.conservativeResize(1, mapSizeX);
            } else{
                initMap.conservativeResize(initMap.rows() + 1, initMap.cols());
            }
            for(int i = 0; i < mapSizeX; i++){
               initMap(sizeCounter, i) = (int)output[i] - 48;
            }
            sizeCounter++;
        }
        mapSizeY = sizeCounter - 1;
        cout << "Map size X: " << mapSizeX << endl;
        cout << "Map size Y: " << mapSizeY << endl;
    }
    problemFile.close();
    removeRow(initMap, mapSizeY - 1);
    initialDeadlockDetector(initMap);

    // Assiging initial state to current state
    currentState.total_distance = 0;
    currentState.map = initMap;
    currentState.player.findPlayer(initMap);
    currentState.generateID();
    currentState.parent = currentState.ID;
    currentState.push_steps = 0;
    currentState.calculateScore(number_of_depos, depoLocations);

    cout << currentState.map << endl;
    cout << "Map loaded\n" << endl;
}

bool destinationIsReached(Player player, localization destination){
    if(player.x_coord != destination.x || player.y_coord != destination.y){
        return 0; //destination not reached
    }
    return 1; //destination reached
}

struct state{
    MatrixXd map;
    string ID;
    string parent;
    string move;
    Player player;
};

bool checkIfPathMoveIsLegit(direction dir, state currentState){
    int object = currentState.map(currentState.player.y_coord + dir.y, currentState.player.x_coord + dir.x);

    switch(object){
        case EMPTY_SPACE:
            return 1; // legit

        case DEADLOCK:
            return 1; // legit

        case DEPO:
            return 1; // legit

        default:
            return 0; // illegal
    }
}

bool checkIfMoveWasTried(state new_state, vector<state> closedList){
    for(int i = 0; i < closedList.size(); i++){
        if(new_state.ID == closedList[i].ID){
            return 1; // yes, this state was visited before
        }
    }

    return 0; // no, state was not visited
}

string generateID(MatrixXd map){
    int object;
    char c;
    string ID;
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
    return ID;
}

state translateState(direction dir, state currentState){
    state new_state;
    new_state.player.x_coord = currentState.player.x_coord + dir.x;
    new_state.player.y_coord = currentState.player.y_coord + dir.y;
    new_state.map = currentState.map;
    new_state.move = dir.movement;
    new_state.parent = currentState.ID;

    int object = currentState.map(new_state.player.y_coord, new_state.player.x_coord);

    switch(object){
        case EMPTY_SPACE:

        case DEADLOCK:

        case DEPO:
            new_state.map(new_state.player.y_coord, new_state.player.x_coord) = PLAYER;
            new_state.map(currentState.player.y_coord, currentState.player.x_coord) = EMPTY_SPACE;
            break;

        default:
            cout << "Translate state for pathfinding: shouldn't be here, something is wrong!" << endl;
            break; // illegal
    }

    //cout << "map after: " << new_state.map << endl;

    new_state.ID = generateID(new_state.map);
    return new_state;
}

void findNewPathMoves(vector<state>& openList, vector<state> closedList, state currentState){
    state new_state;
    for(int i = 0; i < directions.size(); i++){
        if(checkIfPathMoveIsLegit(directions[i], currentState)){
            new_state = translateState(directions[i], currentState);
            if(checkIfMoveWasTried(new_state, closedList) == false){
                openList.push_back(new_state);
            }
        }
    }
}

void pathfinding(MapState state_A, MapState state_B, vector<std::string>& moves){
    //cout << "State A map: \n" << state_A.map << endl;
    //cout << "State B map: \n" << state_B.map << endl;

    localization destination;
    if(state_B.movement == UP.movement){
        destination.x = state_B.player.x_coord;
        destination.y = state_B.player.y_coord + 1;
    } else if(state_B.movement == DOWN.movement){
        destination.x = state_B.player.x_coord;
        destination.y = state_B.player.y_coord - 1;
    } else if(state_B.movement == LEFT.movement){
        destination.x = state_B.player.x_coord + 1;
        destination.y = state_B.player.y_coord;
    } else {
        destination.x = state_B.player.x_coord - 1;
        destination.y = state_B.player.y_coord;
    }

    vector<state> closedList;
    vector<state> openList;

    state currentState;
    currentState.map = state_A.map;
    currentState.ID = state_A.ID;
    currentState.parent = state_A.parent;
    currentState.player = state_A.player;

    while(destinationIsReached(currentState.player, destination) == 0){

        //updated visited
        if(checkIfMoveWasTried(currentState, closedList) == 0){

            closedList.push_back(currentState);

            //find new moves
            findNewPathMoves(openList, closedList, currentState);
        }

        //new current state
        currentState = openList.front();

        //erase front from open
        openList.erase(openList.begin());

    }

    string stepId = currentState.ID;
    string parentId = currentState.parent;
    moves.push_back(state_B.movement + 'P');

    while(stepId != state_A.ID){
        for(int i = 0; i < closedList.size(); i++){
            if(closedList[i].ID == parentId){
                //cout << currentState.map << endl;
                moves.push_back(currentState.move);

                currentState = closedList[i];
                parentId = currentState.parent;
                stepId = currentState.ID;
                goto end_of_loop;
            }
        }
    end_of_loop: ;
    }

}

vector<std::string> findAllMoves(){
    MapState current_map_state(mapSizeX, mapSizeY);
    vector<string> moves;
    current_map_state = currentState;
    std::string stepId = currentState.ID;
    std::string parentId = currentState.parent;
    while(stepId != parentId){
        // this for loop looks for a parent of a current state and generates moves connecting these two states
        for(int i = 0; i < closedStates.size(); i++){
            if(closedStates[i].ID == current_map_state.parent){
                pathfinding(closedStates[i], current_map_state, moves);
                current_map_state = closedStates[i];
                parentId = current_map_state.parent;
                stepId = current_map_state.ID;
                goto end_of_loop;
            }
        }
    end_of_loop: ;
    }

    cout << "Number of steps in total: " << moves.size() << endl;
    return moves;
}

void writingSolutionToFile(const char* path, int mins, int secs, int millisecs){
    ofstream textFile;
    textFile.open(path);

    vector<std::string> moves = findAllMoves();

    for(int i = moves.size() - 1; i >= 0; i--){
        textFile << moves[i] << "\n";
    }

    textFile << "-" << "\n";

    textFile << "\nmap size: " << mapSizeX << " x " << mapSizeY << "\n";
    textFile << "steps in total: " << moves.size() << "\n";
    textFile << "execution time: " << mins << " m " << secs << " s " << millisecs << " ms" << "\n";
    textFile << "states visited: " << closedStates_dictionary.size() << "\n";

    textFile.close();
}

int main(int argc, char *argv[])
{
    // time probing for calculting execution time
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    // path to problem and solution files
    std::string problem_path = ("problems/problem" + std::string(argv[1]) + ".txt");
    std::string solution_path = ("solutions/solution" + std::string(argv[1]) + ".txt");
    std::string searchMethod = std::string(argv[2]);

    // initialization
    assignSearchingMethod(searchMethod);
    loadProblemFromTxtFile(problem_path.c_str());
    defineDirectionConstants();

    // find depos to make veryfing the win state faster;
    findDepos();
    //int counter = 1;

    while(isWinState() == 0){
        // if(checkIfStateWasVisited(currentState) == 0){
        // since currentState is not a winning state, insert it to closedStates

        updatedVistedStates(currentState);

        // finding new moves; legit states are inserted into openState
        findNewMoves();
//            if(counter >= 5000){
//                cout << "open size: " << openStates.size() << endl;
//                cout << "close size: " << closedStates_dictionary.size() << endl;

//                if(searchingMethod == A_STAR){
//                    cout << "Score: " << currentState.score << endl;
//                }
//                cout << "Steps: " << currentState.steps << endl;
//                cout << currentState.map << "\n" << endl;

//                counter = 1;
//            } else{
//                counter++;
//            }
//          }

        // pick the first element of openStates and make it a current state
        currentState = openStates.front();

        // erase the current state from openState
        openStates.erase(openStates.begin());

    }

    // calculation the execution time
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto millisecs = duration_cast<milliseconds>( t2 - t1 ).count();
    auto secs = duration_cast<seconds>( t2 - t1 ).count();
    auto mins = duration_cast<minutes>( t2 - t1 ).count();
    secs = secs - mins*60;
    millisecs = millisecs - secs*1000;

    // write solution to txt file
    writingSolutionToFile(solution_path.c_str(), mins, secs, millisecs);

    // print out
    cout << "Game solved!" << endl;
    cout << "in " << mins << " m, " << secs << " s, " << millisecs << " ms" << endl;
    cout << currentState.map << endl;
    cout << "open size: " << openStates.size() << ", closed size: " <<  closedStates_dictionary.size() << endl;


    return 0;
}
