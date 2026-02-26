#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <unordered_set>
#include <set>
#include <cmath>
#include "State.h"

// Size of the chess board
extern int BoardSize;

/*
Encoding
*/

// Converts state into a string representation
// Used for hashing and duplicate detection
inline std::string encodeState(const State &state) {
    std::string s;
    for (auto &q : state.QueenPosition) {
        s += std::to_string(q.first) + "," +
             std::to_string(q.second) + "|";
    }
    return s;
}

/*
Board checks
*/

// Checks whether a position is inside the board
inline bool isInside(int r, int c) {
    return (r >= 0 && r < BoardSize && c >= 0 && c < BoardSize);
}

// Checks whether a cell is already occupied by a queen
inline bool isOccupied(const State &state, int r, int c) {
    for (auto &q : state.QueenPosition)
        if (q.first == r && q.second == c)
            return true;
    return false;
}

/*
Conflict Detection
*/

// Checks if two queens attack each other
inline bool isConflict(std::pair<int,int> a,
                       std::pair<int,int> b) {

    // Same row
    if (a.first == b.first) return true;

    // Same column
    if (a.second == b.second) return true;

    // Same diagonal
    if (abs(a.first - b.first) ==
        abs(a.second - b.second))
        return true;

    return false;
}

/*
Goal Test
*/

// Checks if the state is a valid solution
inline bool isGoal(const State &state) {

    // Ensure all queens are placed in different rows
    std::set<int> rows;
    for (auto &q : state.QueenPosition)
        rows.insert(q.first);

    if ((int)rows.size() != BoardSize)
        return false;

    // Ensure no two queens attack each other
    for (int i = 0; i < BoardSize; i++)
        for (int j = i + 1; j < BoardSize; j++)
            if (isConflict(state.QueenPosition[i],
                           state.QueenPosition[j]))
                return false;

    return true;
}

/*
Action Generation
*/

// Generates all valid moves for all queens
inline std::vector<Action> getActions(const State &state) {

    std::vector<Action> actions;

    for (int i = 0; i < BoardSize; i++) {

        int r = state.QueenPosition[i].first;
        int c = state.QueenPosition[i].second;

        // Possible movement directions
        std::vector<std::pair<char,
            std::pair<int,int>>> moves = {
            {'U',{r-1,c}},
            {'D',{r+1,c}},
            {'L',{r,c-1}},
            {'R',{r,c+1}}
        };

        // Add move if it is valid
        for (auto &m : moves) {
            int nr = m.second.first;
            int nc = m.second.second;

            if (isInside(nr,nc) &&
                !isOccupied(state,nr,nc))
                actions.push_back({i, m.first});
        }
    }

    return actions;
}

/*
State Transition
*/

// Applies an action and returns the new state
inline State applyAction(const State &state,
                         const Action &action) {

    State newState = state;

    int i = action.QueenID;
    int r = newState.QueenPosition[i].first;
    int c = newState.QueenPosition[i].second;

    // Update position based on direction
    if (action.MoveDirection == 'U') r--;
    if (action.MoveDirection == 'D') r++;
    if (action.MoveDirection == 'L') c--;
    if (action.MoveDirection == 'R') c++;

    // Apply move only if valid
    if (isInside(r,c) &&
        !isOccupied(newState,r,c)) {
        newState.QueenPosition[i] = {r,c};
        newState.g_cost++;
    }

    return newState;
}

#endif