

// v1.0-4-gdfe246a

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <ctype.h>


using namespace std;

void loadTextFile(const char* path, vector<std::string> &moves, vector<bool> &pushes){
    ifstream problemFile;
    problemFile.open(path);
    char output[10];

    if (problemFile.is_open()) {
        while (!problemFile.eof()) {
            problemFile >> output;
            if(output[0] == '-'){
                break;
            }
            moves.push_back(output);

            if(output[1] == 'P'){
                pushes.push_back(true);
            } else{
                pushes.push_back(false);
            }
        }
    }

    problemFile.close();
}

void writingSolutionToFile(const char* path, vector<char> moves){
    ofstream textFile;
    textFile.open(path);

    for(int i = 0; i < moves.size(); i++){
        textFile << moves[i];
    }

    textFile.close();
}

void rotateClockwise(char& orientation){
    switch(orientation){
        case 'U':
            orientation = 'R';
            break;
        case 'R':
            orientation = 'D';
            break;
        case 'D':
            orientation = 'L';
            break;
        case 'L':
            orientation = 'U';
            break;
    }
}

int main(int argc, char* argv[])
{
    std::string robot_solution_path = ("../../build/robot_solutions/robot_solution" + std::string(argv[1]) + ".txt");
    std::string solver_solution_path = ("../../build/solutions/solution" + std::string(argv[1]) + ".txt");

    vector<std::string> sokoban_moves;
    vector<bool> pushing_moves;
    vector<char> robot_moves;


    loadTextFile(solver_solution_path.c_str(), sokoban_moves, pushing_moves);

    char robot_orientation;

    // orientation of the robot depends on the first move
    robot_orientation = (char)sokoban_moves[0][0];
    int rotation_counter;
    for(int i = 0; i < sokoban_moves.size(); i++){
        rotation_counter = 0;
        while(sokoban_moves[i][0] != robot_orientation){
            rotateClockwise(robot_orientation);
            rotation_counter++;
        }

        if(rotation_counter != 0){
            switch(rotation_counter){
                case 1:
                    robot_moves.push_back('R');
                    break;
                case 2: // to be discussed? better to go backwards or rotate and go foward?
                    robot_moves.push_back('R');
                    robot_moves.push_back('R');
                    // can we even rotate in place?
                    break;
                case 3:
                    robot_moves.push_back('L');
                    break;
            }
        }

        robot_moves.push_back('F');

        if(pushing_moves[i]){
            robot_moves.push_back('Q');
            robot_moves.push_back('B');
        }
    }
    writingSolutionToFile(robot_solution_path.c_str(), robot_moves);

    return 0;
}
