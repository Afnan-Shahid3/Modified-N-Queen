#ifndef UCS_H
#define UCS_H

#include <queue>
#include <unordered_set>
#include <iostream>
#include "Utilities.h"

// Comparator for Priority Queue
// Expands state with lowest g_cost first
struct CompareUCS {
    bool operator()(State a, State b) {
        return a.g_cost > b.g_cost;
    }
};

// Uniform Cost Search (UCS)
// Expands nodes based on path cost only
inline void UCS(State initial) {

    long long nodesExpanded = 0;

    // Priority queue ordered by lowest g_cost
    std::priority_queue<State,
        std::vector<State>,
        CompareUCS> Frontier;

    // Stores visited states to prevent revisiting
    std::unordered_set<std::string> visited;

    Frontier.push(initial);

    while (!Frontier.empty()) {

        // Get state with lowest cost
        State current = Frontier.top();
        Frontier.pop();
        nodesExpanded++;

        std::string key = encodeState(current);

        // Skip if state was already processed
        if (visited.count(key)) continue;
        visited.insert(key);

        // Check goal condition
        if (isGoal(current)) {
            std::cout << "UCS Found Solution\n";
            std::cout << "Nodes Expanded: "
                      << nodesExpanded << "\n";
            std::cout << "Frontier Remaining: "
                      << Frontier.size() << "\n";
            return;
        }

        // Generate possible moves
        auto actions = getActions(current);

        for (auto &a : actions) {

            // Apply action to generate new state
            State next = applyAction(current, a);

            // Add to frontier for exploration
            Frontier.push(next);
        }
    }

    std::cout << "No Solution (UCS)\n";
}

#endif