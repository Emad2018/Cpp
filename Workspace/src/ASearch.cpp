/**
 * @file ASearch.cpp
 * @author Abdelrahman Emad (a.emad02018@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-12-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ASearch.hpp"
static std::vector<State> ParseLine(std::string line);
static std::string CellString(State cell);
static int Heuristic(int x1, int y1, int x2, int y2);
static void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &openNodes, std::vector<std::vector<State>> &grid);
static void CellSort(std::vector<std::vector<int>> &openNodes);
static bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid);
static void ExpandNeighbors(std::vector<int> currNode, int goalNode[2], std::vector<std::vector<int>> &openNodes, std::vector<std::vector<State>> &grid);
static void printopenNode(std::vector<std::vector<int>> &openNodes);
/**
 * @name PrintBoard
 * @brief
 *
 * @param board
 */
void PrintBoard(std::vector<std::vector<State>> board)
{
  int row, col, n_col, n_row;

  n_col = board.size();
  n_row = board[0].size();

  for (col = 0; col < n_col; ++col)
  {
    for (row = 0; row < n_row; ++row)
    {
      std::cout << std::format("{}", CellString(board[col][row]));
    }
    std::cout << "\n";
  }
}
/**
 * @name
 * @brief
 *
 * @param boardFile
 * @return std::vector<std::vector<int>>
 */
std::vector<std::vector<State>> ReadBoardFile(std::string boardFile)
{
  // Create an input file stream object named 'file' and
  std::ifstream file(boardFile);

  std::vector<std::vector<State>> board;
  // String to store each line of the file.
  std::string line;
  if (file.is_open())
  {
    // Read each line from the file and store it in the
    // 'line' variable.
    while (getline(file, line))
    {
      board.push_back(ParseLine(line));
    }

    // Close the file stream once all lines have been
    // read.
    file.close();
  }
  else
  {
    // Print an error message to the standard error
    // stream if the file cannot be opened.
    std::cerr << "Unable to open file!" << std::endl;
  }
  return board;
}
/**
 * @name
 * @brief
 *
 * @param line
 * @return std::vector<int>
 */
static std::vector<State> ParseLine(std::string line)
{
  std::istringstream my_stream(line);
  std::vector<State> row;
  State cell;
  int n;
  char comma;
  while (my_stream >> n >> comma)
  {
    if (true == n)
    {
      cell = State::kObstacle;
    }
    else
    {
      cell = State::kEmpty;
    }
    row.push_back(cell);
  }
  return row;
}
/**
 * @name
 * @brief
 *
 * @param cell
 * @return std::string
 */
static std::string CellString(State cell)
{
  std::string ret;
  switch (cell)
  {
  case State::kObstacle:
    ret = "⛰️   ";
    break;
  case State::kStart:
    ret = "🚦   ";
    break;
  case State::kFinish:
    ret = "🏁   ";
    break;
  case State::kPath:
    ret = "🚗   ";
    break;
  default:
    ret = "0    ";
    break;
  }
  return ret;
}

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, int startNode[2], int endNode[2])
{
  std::vector<std::vector<State>> path;
  std::vector<std::vector<int>> openNodes;

  int currentNode_x = startNode[0];
  int currentNode_y = startNode[1];
  int g = 0;
  int h = Heuristic(currentNode_x, currentNode_y, endNode[0], endNode[1]);
  if (CheckValidCell(currentNode_x, currentNode_y, grid))
  {
    AddToOpen(currentNode_x, currentNode_y, g, h, openNodes, grid);
  }
  // TODO: while open vector is non empty {

  while (openNodes.size())
  {

    // TODO: Sort the open list by calling `CellSort`. `CellSort` method will sort the open list in a descending order to have the node with the lowest heuristic value at the end of the vector.
    // TODO: When you call the `CellSort` method, you will need to pass the memory address of the open vector like that: CellSort(&open) because the argument of the CellSort method is a pointer to a vector.
    CellSort(openNodes);
    // TODO: get the last node from the open vector using the '.back()` method and save it to the variable `current_node`.
    std::vector<int> currentNode = openNodes.back();
    // TODO: remove the last node from the open vector using the`.pop_back()` method.
    openNodes.pop_back();
    // TODO: Get the x and y values from the `current_node`,
    // and set grid[x][y] to kPath.

    currentNode_x = currentNode[0];
    currentNode_y = currentNode[1];

    grid[currentNode_x][currentNode_y] = State::kPath;
    // TODO: Check if you've reached the goal. If so, return grid.
    if (currentNode_x == endNode[0] && currentNode_y == endNode[1])
    {
      grid[startNode[0]][startNode[1]] = State::kStart;
      grid[currentNode_x][currentNode_y] = State::kFinish;
      return grid;
    }
    else
    {
    }
    // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
    // ExpandNeighbors
    ExpandNeighbors(currentNode, endNode, openNodes, grid);
  }

  return grid;
}
static int Heuristic(int x1, int y1, int x2, int y2)
{
  return (abs(x2 - x1) + abs(y2 - y1));
}
static void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &openNodes, std::vector<std::vector<State>> &grid)
{
  openNodes.push_back({x, y, g, h});
  grid[x][y] = State::kClosed;
}

static bool Compare(std::vector<int> firstNode, std::vector<int> secondNode)
{
  return ((firstNode[2] + firstNode[3]) > (secondNode[2] + secondNode[3]) ? true : false);
}
static void CellSort(std::vector<std::vector<int>> &openNodes)
{
  sort(openNodes.begin(), openNodes.end(), Compare);
}
static bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid)
{
  bool ret = false;
  if ((x >= 0 && x < grid.size()) && (y >= 0 && y < grid[0].size()))
  {
    if (grid[x][y] == State::kEmpty)
    {
      ret = true;
    }
    else
    {
    }
  }
  else
  {
  }
  return ret;
}
static void ExpandNeighbors(std::vector<int> currNode, int goalNode[2], std::vector<std::vector<int>> &openNodes, std::vector<std::vector<State>> &grid)
{
  // TODO: ExpandNeighbors {
  int neighborNode_x, neighborNode_y, neighborNode_g, neighborNode_h;
  // TODO: Get current node's data.
  const int delta[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  // TODO: Loop through current node's potential neighbors.
  for (int loopCnt = 0; loopCnt < 4; ++loopCnt)
  {
    neighborNode_x = currNode[0] + delta[loopCnt][0];
    neighborNode_y = currNode[1] + delta[loopCnt][1];
    if (CheckValidCell(neighborNode_x, neighborNode_y, grid))
    {
      // TODO: Increment g value, compute h value, and add neighbor to open list.
      neighborNode_g = currNode[2] + 1;
      neighborNode_h = Heuristic(neighborNode_x, neighborNode_y, goalNode[0], goalNode[1]);
      AddToOpen(neighborNode_x, neighborNode_y, neighborNode_g, neighborNode_h, openNodes, grid);
    }
  }
  // TODO: Check that the potential neighbor's x2 and y2 values are on the grid and not closed.

  // } TODO: End function
}

static void printopenNode(std::vector<std::vector<int>> &openNodes)
{
  for (int i = 0; i < openNodes.size(); i++)
  {
    std::cout << std::format("[{},{},{},{}]\n", openNodes[i][0], openNodes[i][1], openNodes[i][2], openNodes[i][3]);
  }
}