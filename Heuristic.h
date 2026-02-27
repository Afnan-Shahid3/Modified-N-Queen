#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "Utilities.h"

// Heuristic function for A*.
// Counts total number of conflicts between queens.
// If Queen A conflicts with Queen B,
// it is counted twice (as required in assignment).

inline int heuristic(const State &state) {

    int conflicts = 0;

    // Compare every queen with every other queen
    for (int i = 0; i < BoardSize; i++)
        for (int j = 0; j < BoardSize; j++)
            if (i != j)
                // Increment if two queens are in conflict
                if (isConflict(state.QueenPosition[i],
                               state.QueenPosition[j]))
                    conflicts++;

    // Goal state will have 0 conflicts
    return conflicts;
}

#endif