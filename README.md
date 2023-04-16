# Othello

This is a chess game implemented in C++ using data structures, recursion, and alpha beta pruning algorithm to optimize the search of the game tree.

Alpha Beta Pruning

The function recursively searches the game tree, evaluating each node using a heuristic function that estimates the value of the position. The algorithm maintains two values, alpha and beta, that represent the best possible score that the maximizing player and minimizing player respectively can achieve given the current state of the game. It prunes the search when it is determined that a node cannot possibly yield a better score than another already evaluated node, significantly reducing the number of nodes explored.

