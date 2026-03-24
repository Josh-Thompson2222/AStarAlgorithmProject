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
While Manhattan distance measures measures movement along a grid (like a taxi navigating streets), Euclidean distance represents the direct, straight-line distance between two points (like a bird flying from start to end). In general, Euclidean distance is always less than or equal to Manhattan distance, because it takes the shortest possible path rather than following the axes of the grid.
Movement cost is '1.0' for straight moves and '1.414' for diagonal moves.

## File Structure
 I am using six files, each with separate responsibilities assigned to grid creation and management, node state, and pathfinding logic.

 <img width="266" height="302" alt="image" src="https://github.com/user-attachments/assets/c2f7966e-b51a-438b-ac92-8f31c99b9194" />

- Grid.h and Grid.cpp: These files manage the 2D map environment. It tracks the size of the board, handles adding/clearing obstacles, checks boundary limits, and prints the visual representation of the grid and the path. Sets the start, end, walkable and unwalkable X and Y coordinates.

- Node.h: Defines the data structure for a single space on the grid. It stores coordinates, pathfinding scores (gCost, hCost, fCost), and a parent pointer used to trace the final path backwards.

- AStar.h and AStar.cpp: Contains the core A* pathfinding logic. It evaluates neighbours to find the shortest path to the end goal, calculates distances (heuristics) using the GetHeuristic() function which uses two different formulas, depending on which 'HeuristicType' is chosen (Manhattan or Euclidean). They also manage the open/closed lists, and processes the most efficient route from the start point to the goal.

- main.cpp: This is the execution entry point. It creates the grid and runs a series of different test scenarios. The first test uses only the Manhattan Heuristic method. This moves only in straight lines either up, down, left or right, 1 step at a time. The second test method uses the Euclidean heuristic which can move diagonally to find a shorter path from start to end, however the cost of each movement is slightly higher. Both of these tests include obstacles, the location of each is set out inside the main function using "grid.SetWalkable(2, 3, false);". The third test case does not have a possible path. It explores all possible nodes until it realises it cannot find a path when it then outputs "No path found" to the console. Final test case experiments with the start and end node being equal to one another. This case only explores one node.

## Setup and Run
- Visual Studio 2022
- Modern C++ (C++ 11 or later)

- Download & Installation
  
  Download the zipped project folder submission. "Extract all" to your downloads folder. Open Visual Studio 2022 and on the right-hand side, click "Open a project or solution". Navigate to the solution file inside the project folder and open this solution. 

- Clean Solution:

  Once the solution is open, hover over the "Build" menu on the navigation bar at the top and click on "clean solution". 
  <img width="1918" height="1018" alt="image" src="https://github.com/user-attachments/assets/609bd507-866f-43fa-925f-a0cf948821bd" />

- Build Solution:

  Once the solution has been cleaned, hover over the "Build" menu again and click "Build Solution". 
  <img width="1913" height="1020" alt="image" src="https://github.com/user-attachments/assets/5a2db8f5-aa73-41e1-826c-c9e3d07d71cf" />

- Debugging/Running solution:

  When the solution has finished building, click the play button outlined in green at the top to start without debugging.
  <img width="1917" height="1022" alt="image" src="https://github.com/user-attachments/assets/ead8d418-6c45-46a6-bfcf-bafcc24a6dbc" />

 
## Sample Maps
 I have chosen to use a 10x10 grid in this test programme. I chose this size as I started wih a 6x6 grid size and thought it was too small to really demonstrate the capability of the algorithm. A 10x10 grid gives the algorithm more room to show how well it works.

 I am placing obstacles manually in the main.cpp file instead of how I was previously doing randomly generated walls as I feel it can give me more control over the test environments.

 Test environments are as follows:
 
 - A standard obstacle layout (Manhattan)
 - A denser map with diagonal movement allowed (Euclidean)
 - A blocked goal
 - A case where start equals goal

## Results

 Test 1: Normal path with obstacles (Manhattan heuristic)

 Uses Manhattan heuristic and no diagonal movement. The algorithm successfully routes around walls to find a valid path.

 <img width="693" height="302" alt="image" src="https://github.com/user-attachments/assets/af257d71-16fa-4eee-a5e6-18a689494425" />

 From this image we can see that the algorithm explored 33 possible nodes to find the shortest path. The shortest path found was 19 steps from start to end. That means that the path chsen was the one with the lowest fCost, and if this was equal to another path's fCost, then their hCost was compared to find the lowest.

 Test 2: Dense obstacles with diagonal movement (Euclidean heuristic)

 This test case uses Euclidean distance nd diagonal movements are allowed to find the shortest path from start to finsh. This shows that the algorithm can still find a path efficiently in a more constrained environment with such dense obstacles.

 <img width="595" height="302" alt="image" src="https://github.com/user-attachments/assets/36ff3f9a-9267-4f49-9add-04c1083dcd06" />

 The image shows how a path was discovered using only 9 steps. As Euclidean heuristic uses less than half the total steps the Manhattan heuristic does. I think this reinforces our prior knowledge, that the Eucliden method is more efficient when the two are compared. The fCost of diagonal movement is 1.414 for diagonal movements and only 1.0 for straight line movements, the final cost of the Euclidean mathod is 10.484 ((1.414 x 6) + 2), and the final cost of the Manhattan method is 18 (18 x 1.0).

 Test 3: Unreachable goal

 In this scenario, the goal is completely surrounded by obstacles. This demonstrates that the algorithm correctly reports that no path exists. This is an important validation case, as it shows us that the algorithm is not making false predictions on where paths can be made. It has searched 91 nodes and found no possible way from start to    end.

 <img width="403" height="77" alt="image" src="https://github.com/user-attachments/assets/18e4cea1-a811-47cd-bedb-0e8e0eff7f38" />

 Test 4: Start equals goal

 The algorithm handles the edge case where the start node and end node are the same location. 

 <img width="437" height="306" alt="image" src="https://github.com/user-attachments/assets/c999948c-0c8f-4170-b9dd-450949831070" />

## Lessons Learned
 I feel that this project really helped me to both learn new, important C++ algorithm design concepts, while also reinforcing my existing knowledge of the Object Oriented design I was taught in class.

 Skills developed:

 - How the A* Algorithm uses gCost, fCost and hCost to guide search.
 - How heuristic choice affects behaviour and efficiency. For example, using the Euclidean heuristic may find a shorter path from start to end than the Manhattan heuristic but if the path contains a lare amount of diagonal movements, the total cost of the shorter        Euclidean path may be higher than the cost of the Manhattan path which only moves up-down-left-right.
 - STL containers such as std::vector and std::priority_queue can support graph search.
 - Modular design improves readability and maintainability as each file has a single responsibility, so you don't need to understand the entire project at once. I have found this design a great help to me when debugging issues as it is easily navigable to find where a   problem has occurred and where the root cause is from there.
 
   My project is divided into 4 sections making it easy to follow:

   Node - data structure

   Grid - environment representation

   AStar - algorithm logic

   Main - execution/testing

 - Why edge-case testing is necessary. This is important as it allows me to ensure the algorithm handles the failure conditions correctly. In my tests, I included a situation where navigating a path from start to finish was not possible. This method explored 91 nodes    and proved that the algorithm will not run indefinitely or crash due to invalid access.

 - Understanding why it's so important to add human input to AI code in modern times. AI code can often be a great tool for engineers, but it does not completely replace us. From working on this project I have seen first-hand how useful AI code can be, but it also       makes quite a few mistakes which need to be fixed/edited by the engineer in control. One example from my code would be when AI autocompleted the creation of my grid, it made the obstacles using the '#' symbol. Reading this on a graph from a human perspective, this was  difficult to differentiate at a quick glance from the walkable path '.' and the path chosen '*'. All of these symbols blended together very much making it hard to tell where the actual path went, so I changed the wall symbol from '#' to 'O'.
     
## Future Improvements
