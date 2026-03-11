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

struct Compare
{
    bool operator()(Node* a, Node* b)
    {
        return a->fCost > b->fCost;
    }
};

AStar::AStar(Grid& g, int sx, int sy, int ex, int ey)
    : grid(g)
{
    startX = sx;
    startY = sy;
    endX = ex;
    endY = ey;
}

float AStar::Heuristic(int x1, int y1, int x2, int y2)
{
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::vector<Node*> AStar::GetNeighbors(Node* node)
{
    std::vector<Node*> neighbors;

    int directions[4][2] =
    {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1}
    };

    for (auto& d : directions)
    {
        int nx = node->x + d[0];
        int ny = node->y + d[1];

        if (grid.IsInside(nx, ny) && grid.IsWalkable(nx, ny))
        {
            neighbors.push_back(new Node(nx, ny));
        }
    }

    return neighbors;
}

std::vector<Node*> AStar::FindPath()
{
    std::priority_queue<Node*, std::vector<Node*>, Compare> openList;

    Node* start = new Node(startX, startY);
    Node* goal = new Node(endX, endY);

    openList.push(start);

    while (!openList.empty())
    {
        Node* current = openList.top();
        openList.pop();

        if (current->x == goal->x && current->y == goal->y)
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

        auto neighbors = GetNeighbors(current);

        for (Node* n : neighbors)
        {
            n->gCost = current->gCost + 1;
            n->hCost = Heuristic(n->x, n->y, goal->x, goal->y);

            n->CalculateFCost();

            n->parent = current;

            openList.push(n);
        }
    }

    return {};
}