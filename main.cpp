/*
*
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣉⣁⣤⣤⣶⣾⣿⣿⣶⡄⢲⣯⢍⠁⠄⢀⢹⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⢯⣾⣿⣿⣏⣉⣹⠿⠇⠄⠽⠿⢷⡈⠿⠇⣀⣻⣿⡿⣻
⣿⣿⡿⠿⠛⠛⠛⢛⡃⢉⢣⡤⠤⢄⡶⠂⠄⠐⣀⠄⠄⠄⠄⠄⡦⣿⡿⠛⡇⣼
⡿⢫⣤⣦⠄⠂⠄⠄⠄⠄⠄⠄⠄⠄⠠⠺⠿⠙⠋⠄⠄⠄⠢⢄⠄⢿⠇⠂⠧⣿
⠁⠄⠈⠁⠄⢀⣀⣀⣀⣀⣠⣤⡤⠴⠖⠒⠄⠄⠄⠄⠄⠄⠄⠄⠄⠘⢠⡞⠄⣸
⡀⠄⠄⠄⠄⠄⠤⠭⠦⠤⠤⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣂⣿
⣷⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢳⠄⠄⢀⠈⣠⣤⣤⣼⣿
⣿⣿⣷⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣴⣶⣶⣶⣄⡀⠄⠈⠑⢙⣡⣴⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿


Josh Thompson
19/01/26
*/

#include <iostream>
#include "Grid.h"
#include "AStar.h"

void RunTest(const std::string& testName, Grid& grid, int sx, int sy, int ex, int ey, bool diagonals, HeuristicType hType)
{
    std::cout << "--- " << testName << " ---\n";

    AStar astar(grid, sx, sy, ex, ey, diagonals, hType);
    auto path = astar.FindPath();

    if (path.empty()) {
        std::cout << "Result: No path found.\n";
    }
    else {
        std::cout << "Result: Path found! Length: " << path.size() << " steps.\n";
        grid.PrintWithPath(sx, sy, ex, ey, path);
    }

    std::cout << "Nodes explored: " << astar.GetNodesExploredCount() << "\n\n";
}

int main()
{
    Grid grid(10, 10);

    // Test 1: Normal Path
    grid.ClearObstacles();
    // Add a wall to test Manhattan pathfinding around an obstacle
    grid.SetWalkable(0, 2, false); grid.SetWalkable(2, 3, false);
    grid.SetWalkable(7, 4, false); grid.SetWalkable(9, 5, false);
    grid.SetWalkable(5, 6, false); grid.SetWalkable(5, 7, false);
    grid.SetWalkable(2, 0, false); grid.SetWalkable(4, 2, false);

    RunTest("Test 1: Normal Path with obstacles (No Diagonals)", grid, 0, 0, 9, 9, false, HeuristicType::Manhattan);

    // Test 2: Dense Obstacles with Diagonals
    grid.SetWalkable(4, 0, false); grid.SetWalkable(4, 1, false);
    grid.SetWalkable(4, 2, false); grid.SetWalkable(4, 3, false);
    grid.SetWalkable(4, 4, false); grid.SetWalkable(5, 4, false);
    grid.SetWalkable(6, 4, false); grid.SetWalkable(7, 4, false);
    RunTest("Test 2: Dense Obstacles (With Diagonals)", grid, 1, 1, 8, 8, true, HeuristicType::Euclidean);

    // Test 3: Unreachable Goal
    grid.ClearObstacles();
    // Wall around the goal (8,8)
    grid.SetWalkable(8, 7, false); grid.SetWalkable(7, 7, false);
    grid.SetWalkable(7, 8, false); grid.SetWalkable(7, 9, false);
    grid.SetWalkable(8, 9, false); grid.SetWalkable(9, 7, false);
    grid.SetWalkable(9, 9, false);
    RunTest("Test 3: Unreachable Goal", grid, 1, 1, 8, 8, true, HeuristicType::Euclidean);

    // Test 4: Start == Goal
    grid.ClearObstacles();
    RunTest("Test 4: Start == Goal", grid, 5, 5, 5, 5, true, HeuristicType::Euclidean);

    return 0;
}