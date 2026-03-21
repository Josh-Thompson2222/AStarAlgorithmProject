# C++ A* Pathfinding Project
Author: Josh Thompson

Student ID: G00422756

Module: C++ Programming

Lecturer: Michelle Lynch

Academic Year: 2025-2026

## Overview
 My project is a modern implementation of the C++ (C++ 11 or later),  A* Pathfinding algorithm built in Visual Studio 2022, to represent a programmer. The aim of the project is to search for the shortest path from a starting node to an end node on a 2D grid while avoiding blocked cells which I portray with a different symbol than the walkable path or path chosen. The solution was built using an object-oriented and modular design, which aligns with the project requirements to use modern C++, STL, containers and reusable components.
 My project supports both Manhattan and Euclidean heuristics, so it can run with or without diagonal movements. I have included multiple test cases to validate the algorithm under normal conditions and edge cases such as unreachable goals and identical start/end positions. 
## Features
 - A* pathfinding on a 10x10 cell, 2D grid
 - Obstacles and blocked cells
 - Manhattan and Euclidean heuristic
 - Diagonal movement (with the Euclidean heuristic)
 - Tracks number of explored Nodes
 - Prints the final path directlt in the console
 - Includes test scenarios for Manhattan heuristic, Euclidean heuristic, no path found and when the start point and the end point are the same node
## Demo
 The grid display uses:
 - 'S' to show the starting node - where the path starts
 - 'E' displays the end node - where the path ends
 - '*' for the chosen, discovered path
 - '.' shows the walkable, empty cells
 - 'O' cells are walls or obstacles, which makes these cells unwalkable
 
 Initially I had decided to use '#' to display the obstacles, however after running the code a few times and looking at the output on the console, I found it a bit hard on the eyes to distinguish very clearly between the chosen path, obstacles and walkable cells. This gave me the idea to use 'O' to display obstacles instead as they are easily distinguishable from the others at a quick glance. 
 
 <img width="693" height="625" alt="image" src="https://github.com/user-attachments/assets/2818327a-7475-469a-b704-097b11fecc23" />

I made the adjustment from the previous output to this one, as I feel this output is easier to understand which cells are blocked while following the path with your eyes.

 <img width="538" height="770" alt="image" src="https://github.com/user-attachments/assets/b8e99479-cbb5-4a7a-ac81-1114cb48cbcb" />

## How It Works
 I have used a priority queue as the open list, with nodes ordered by their 'fCost'. If two nodes have the same 'fCost', then the implementation uses a tie-breaker that prefers whichever node has the lower 'hCost'. This biases the search slightly closer to the goal. 
 
 <img width="262" height="61" alt="image" src="https://github.com/user-attachments/assets/85664ead-ab0e-4050-a4c1-0d2a7ee659dd" />

 <img width="902" height="230" alt="image" src="https://github.com/user-attachments/assets/f75ba648-b055-4c0c-bd14-96925ee05da7" />

Each node stores:
- It's grid position, which is stored as an integer
- A parent pointer to a null value when the path is first created and can be used later in the code for path reconstruction
- 'gCost'
- 'fCost'
- 'hCost'

How it works:
1. Add the starting node to the open list.
2. Repeatedly remove the node with the lowest 'fCost'.
3. If that node is the goal, reconstruct the path by following parent pointers backwards.
4. Otherwise, inspect all valid neighbours.
5. Update neighbour costs when a shorter path is found.
6. Continue this process until the goal is found or the open list is empty

The implementation supports both:
- Manhattan distance for non-diagonal movement
- Euclidean distance for diagonal movement
While Manhattan distance measures measures movement along a grid (like a taxi navigating streets), Euclidean distance represents the direct, straight-line distance between two points (like a crow flying from start to end).

## File Structure
 
## Setup and Run
 
## Sample Maps
 
## Results
 
## Lessons Learned
 
## Future Improvements
