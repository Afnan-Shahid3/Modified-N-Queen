#ifndef BFS_H
#define BFS_H

#include <queue>
#include <unordered_set>
#include <iostream>
#include "Utilities.h"

// Breadth-First Search (BFS)
// Explores states level by level
inline void BFS(State initial) {

    long long nodesExpanded = 0;

    // Queue for BFS exploration (FIFO)
    std::queue<State> Frontier;

    // Keeps track of visited states to avoid duplicates
    std::unordered_set<std::string> visited;

    Frontier.push(initial);
    visited.insert(encodeState(initial));

    while (!Frontier.empty()) {

        // Get next state in queue
        State current = Frontier.front();
        Frontier.pop();
        nodesExpanded++;

        // Check if goal state is reached
        if (isGoal(current)) {
            std::cout << "BFS Found Solution\n";
            std::cout << "Nodes Expanded: "
                      << nodesExpanded << "\n";
            std::cout << "Frontier Remaining: "
                      << Frontier.size() << "\n";
            return;
        }

        // Generate all possible moves
        auto actions = getActions(current);

        for (auto &a : actions) {

            // Apply move to get new state
            State next = applyAction(current, a);
            std::string key = encodeState(next);

            // Add to queue if not visited
            if (!visited.count(key)) {
                Frontier.push(next);
                visited.insert(key);
            }
        }
    }

    std::cout << "No Solution (BFS)\n";
}

#endif