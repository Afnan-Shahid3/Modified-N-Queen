#ifndef STATE_H
#define STATE_H

#include <vector>
#include <utility>

// Represents a board state in the N-Queens problem
struct State {

    // Stores the position of each queen (row, column)
    std::vector<std::pair<int,int>> QueenPosition;

    // Cost from the initial state (used in search algorithms)
    int g_cost = 0;
};

// Represents a possible move for a queen
struct Action {

    // ID of the queen to move
    int QueenID;

    // Direction of movement:
    // 'U' = Up, 'D' = Down, 'L' = Left, 'R' = Right
    char MoveDirection;
};

#endif