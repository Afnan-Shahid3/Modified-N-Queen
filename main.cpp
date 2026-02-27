#include <iostream>
#include "State.h"
#include "Utilities.h"
#include "Heuristic.h"
#include "BFS.h"
#include "UCS.h"
#include "AStar.h"

int BoardSize;

int main() {

    std::cout << "Enter N: ";
    std::cin >> BoardSize;

    State initial;

    for (int col = 0; col < BoardSize; col++)
        initial.QueenPosition.push_back({0,col});

   
    if(BoardSize < 6){    
         BFS(initial);
        UCS(initial);
    }
    AStar(initial);
    return 0;

}