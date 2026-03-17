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

#include "AStar.h"
#include <queue>
#include <cmath>
#include <algorithm>

struct CompareNode
{
    bool operator()(const Node* a, const Node* b) const
    {
        // Tie-breaker: if fCosts are equal, prefer the one closer to goal (lower hCost)
        if (a->fCost == b->fCost)
            return a->hCost > b->hCost;
        return a->fCost > b->fCost;
    }
};

AStar::AStar(const Grid& g, int sx, int sy, int ex, int ey, bool diagonals, HeuristicType hType)
    : grid(g), startX(sx), startY(sy), endX(ex), endY(ey),
    allowDiagonals(diagonals), heuristicType(hType), nodesExplored(0)
{
    // Initialize the reusable node grid
    nodeGrid.resize(grid.GetRows(), std::vector<Node>(grid.GetCols()));
    for (int y = 0; y < grid.GetRows(); y++) {
        for (int x = 0; x < grid.GetCols(); x++) {
            nodeGrid[y][x] = Node(x, y);
        }
    }
}

float AStar::GetHeuristic(int x1, int y1, int x2, int y2) const
{
    if (heuristicType == HeuristicType::Euclidean)
        return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));

    // Manhattan
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::vector<Node*> AStar::GetNeighbors(Node* node)
{
    std::vector<Node*> neighbors;

    // Use C++17 structured bindings for clearer direction arrays
    std::vector<std::pair<int, int>> directions = {
        {1,0}, {-1,0}, {0,1}, {0,-1}
    };

    if (allowDiagonals) {
        directions.insert(directions.end(), { {1,1}, {1,-1}, {-1,1}, {-1,-1} });
    }

    for (const auto& dir : directions)
    {
        int dx = dir.first;
		int dy = dir.second;

        int nx = node->x + dx;
        int ny = node->y + dy;

        // Prevent cutting corners through walls on diagonals here if needed in the future

        if (grid.IsInside(nx, ny) && grid.IsWalkable(nx, ny))
        {
            neighbors.push_back(&nodeGrid[ny][nx]);
        }
    }

    return neighbors;
}

std::vector<Node*> AStar::FindPath()
{
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;

    Node* start = &nodeGrid[startY][startX];
    Node* goal = &nodeGrid[endY][endX];

    start->isOpen = true;
    openList.push(start);

    while (!openList.empty())
    {
        Node* current = openList.top();
        openList.pop();
        current->isOpen = false;

        // If we popped a staler duplicate node from the queue, skip it
        if (current->isClosed) continue;

        current->isClosed = true;
        nodesExplored++;

        if (current == goal)
        {
            std::vector<Node*> path;
            while (current != nullptr)
            {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (Node* neighbor : GetNeighbors(current))
        {
            if (neighbor->isClosed) continue;

            // Movement cost: 1 for straight, 1.414 for diagonal
            float moveCost = (current->x != neighbor->x && current->y != neighbor->y) ? 1.414f : 1.0f;
            float tentativeGCost = current->gCost + moveCost;

            if (!neighbor->isOpen || tentativeGCost < neighbor->gCost)
            {
                neighbor->gCost = tentativeGCost;
                neighbor->hCost = GetHeuristic(neighbor->x, neighbor->y, goal->x, goal->y);
                neighbor->CalculateFCost();
                neighbor->parent = current;

                if (!neighbor->isOpen)
                {
                    neighbor->isOpen = true;
                    openList.push(neighbor); // std::priority_queue does not support update_key, duplicate pushes are handled by isClosed skip
                }
            }
        }
    }

    return {}; // No path found
}