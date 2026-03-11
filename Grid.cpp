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

#include "Grid.h"
#include "Node.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>

Grid::Grid(int r, int c)
{
    rows = r;
    cols = c;

    grid.resize(rows, std::vector<int>(cols, 0));

    std::srand(std::time(nullptr));

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            grid[y][x] = (std::rand() % 5 == 0) ? 1 : 0;
        }
    }
}

bool Grid::IsInside(int x, int y) const
{
    return x >= 0 && y >= 0 && x < cols && y < rows;
}

bool Grid::IsWalkable(int x, int y) const
{
    return grid[y][x] == 0;
}

int Grid::GetRows() const { return rows; }
int Grid::GetCols() const { return cols; }

const std::vector<std::vector<int>>& Grid::GetGrid() const
{
    return grid;
}

void Grid::Print(int startX, int startY, int endX, int endY) const
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            if (x == startX && y == startY)
                std::cout << "S ";
            else if (x == endX && y == endY)
                std::cout << "E ";
            else if (grid[y][x] == 1)
                std::cout << "O ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

void Grid::PrintWithPath(
    int startX,
    int startY,
    int endX,
    int endY,
    const std::vector<Node*>& path
) const
{
    std::set<std::pair<int, int>> pathCells;

    for (auto node : path)
        pathCells.insert({ node->x, node->y });

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            if (x == startX && y == startY)
                std::cout << "S ";
            else if (x == endX && y == endY)
                std::cout << "E ";
            else if (grid[y][x] == 1)
                std::cout << "O ";
            else if (pathCells.count({ x,y }))
                std::cout << "* ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}