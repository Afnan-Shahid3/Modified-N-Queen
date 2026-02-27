CSE307 - Introduction to Artificial Intelligence
Assignment #1
Modified N-Queens Problem
Team Members: Syed Afnan (30224) , Faraz Ahmed (30503)
----------
RESULTS
----------
N = 4

BFS
Nodes Expanded : 1025
Frontier Remaining : 1346

UCS
Nodes Expanded : 3085
Frontier Remaining : 6586

A*
Nodes Expanded : 20
Frontier Remaining : 135
----------
N = 5

BFS
Nodes Expanded : 67119
Frontier Remaining : 65829

UCS
Nodes Expanded : 475452
Frontier Remaining : 770263

A*
Nodes Expanded : 20
Frontier Remaining : 184
----------
N = 6

Note:
BFS and UCS were computationally expensive and took excessive time.
Only A* results are reported.

A*
Nodes Expanded : 231
Frontier Remaining : 2875
----------
N = 7

A*
Nodes Expanded : 3081
Frontier Remaining : 50055
----------
N = 8

A*
Nodes Expanded : 93080
Frontier Remaining : 1743991
----------
HEURISTIC USED

The basic conflict-count heuristic was used for all A* runs.
The heuristic counts the total number of attacking queen pairs
(double counted as specified in the assignment).

An improved heuristic was tested but resulted in higher
computation time compared to the basic heuristic.
Therefore, the basic heuristic was retained.
----------
OBSERVATIONS

BFS and UCS exhibit exponential growth as N increases.

A* significantly reduces node expansions using heuristic guidance.

For N >= 6, uninformed search becomes impractical.

A* remains feasible up to N = 8 using the basic heuristic.
----------