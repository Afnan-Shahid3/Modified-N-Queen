#ifndef ASTAR_H
#define ASTAR_H

#include <queue>
#include <unordered_set>
#include <iostream>
#include "Heuristic.h"
#include <unordered_map>

// Comparator for priority queue
// States with smaller (g + h) have higher priority
struct CompareAStar {
    bool operator()(const State& a,
                    const State& b) const {
        return (a.g_cost + heuristic(a)) >
               (b.g_cost + heuristic(b));
    }
};

// A* Search Algorithm
// Finds solution using g(n) + h(n)
inline void AStar(State initial) {

    long long nodesExpanded = 0;

    // Priority queue (Frontier) ordered by f = g + h
    std::priority_queue<State,
        std::vector<State>,
        CompareAStar> Frontier;

    // Stores best g-cost found for each state
    std::unordered_map<std::string, int> bestG;

    // Start node has zero cost
    initial.g_cost = 0;

    Frontier.push(initial);

    while (!Frontier.empty()) {

        // Get state with lowest f-cost
        State current = Frontier.top();
        Frontier.pop();

        std::string key = encodeState(current);

        // Skip if a better path to this state exists
        if (bestG.count(key) &&
            bestG[key] < current.g_cost)
            continue;

        nodesExpanded++;

        // Check goal condition
        if (isGoal(current)) {
            std::cout << "A* Found Solution\n";
            std::cout << "Nodes Expanded: "
                      << nodesExpanded << "\n";
            std::cout << "Frontier Remaining: "
                      << Frontier.size() << "\n";
            return;
        }

        // Generate possible moves
        auto actions = getActions(current);

        for (auto &a : actions) {

            // Apply action to get new state
            State next = applyAction(current, a);

            std::string nextKey = encodeState(next);

            // Add to frontier if it improves g-cost
            if (!bestG.count(nextKey) ||
                next.g_cost < bestG[nextKey]) {

                bestG[nextKey] = next.g_cost;
                Frontier.push(next);
            }
        }
    }

    std::cout << "No Solution (A*)\n";
}

#endif