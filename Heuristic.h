#ifndef IMPROVED_HEURISTIC_H
#define IMPROVED_HEURISTIC_H

#include <vector>
#include "Utilities.h"

/*
   Heuristic Selection Mode
*/

// Defines which heuristic function to use
enum HeuristicType {
    BASIC,
    IMPROVED
};

// Global variable to control heuristic selection
extern HeuristicType currentHeuristic;

/*
   BASIC HEURISTIC
   Counts pairwise conflicts
   Time Complexity: O(N^2)
*/

inline int basicHeuristic(const State &state)
{
    int conflicts = 0;

    // Check all pairs of queens
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            if (i != j)
            {
                // Count conflict between two queens
                if (isConflict(state.QueenPosition[i],
                               state.QueenPosition[j]))
                {
                    conflicts++;
                }
            }
        }
    }

    return conflicts;
}

/*
   IMPROVED HEURISTIC
   Counts conflicts using row and diagonal tracking
   Time Complexity: O(N)
*/

inline int improvedHeuristic(const State &state)
{
    // Track queen counts in rows and diagonals
    std::vector<int> rowCount(BoardSize, 0);
    std::vector<int> diag1(2 * BoardSize, 0);
    std::vector<int> diag2(2 * BoardSize, 0);

    // Count queens in each row and diagonal
    for (const auto &q : state.QueenPosition)
    {
        int r = q.first;
        int c = q.second;

        rowCount[r]++;
        diag1[r - c + BoardSize]++;
        diag2[r + c]++;
    }

    int conflicts = 0;

    // Count row conflicts
    for (int i = 0; i < BoardSize; i++)
    {
        if (rowCount[i] > 1)
            conflicts += rowCount[i] * (rowCount[i] - 1) / 2;
    }

    // Count diagonal conflicts
    for (int i = 0; i < 2 * BoardSize; i++)
    {
        if (diag1[i] > 1)
            conflicts += diag1[i] * (diag1[i] - 1) / 2;

        if (diag2[i] > 1)
            conflicts += diag2[i] * (diag2[i] - 1) / 2;
    }

    return conflicts;
}

/*
   Wrapper Heuristic Function
   Selects active heuristic
*/

inline int heuristic(const State &state)
{
    // Return selected heuristic value
    if (currentHeuristic == BASIC)
        return basicHeuristic(state);
    else
        return improvedHeuristic(state);
}

#endif