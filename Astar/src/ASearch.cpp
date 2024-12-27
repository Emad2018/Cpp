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
/**
 * @name   ParseLine
 * @brief  Parse one row from the board
 *
 * @param line
 * @return std::vector<State>
 */
static std::vector<State> ParseLine(std::string line);
/**
 * @name   CellString
 * @brief  Replace the cell with related Shape
 *
 * @param cell
 * @return std::string
 */
static std::string CellString(State cell);
/**
 * @name   Heuristic
 * @brief  Calculate the Heuristic function between 2 points
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return int
 */
static int Heuristic(int x1, int y1, int x2, int y2);
/**
 * @name   AddToOpen
 * @brief  Add a Node to the open Node and close that Node on the Grid
 *
 * @param x
 * @param y
 * @param g
 * @param h
 * @param openNodes
 * @param grid
 */
static void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &openNodes, std::vector<std::vector<State>> &grid);
/**
 * @name  CellSort
 * @brief Sort the Open Nodes based on the lower F (G + H )vaule
 *
 * @param openNodes
 */
static void CellSort(std::vector<std::vector<int>> &openNodes);
/**
 * @name  CheckValidCell
 * @brief check if the cell is in the Grid and empty
 *
 * @param x
 * @param y
 * @param grid
 * @return true
 * @return false
 */
static bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid);
/**
 * @name  ExpandNeighbors
 * @brief Get vaild Neighbors cells to the current cell
 *
 * @param currNode
 * @param goalNode
 * @param openNodes
 * @param grid
 */
static void ExpandNeighbors(std::vector<int> currNode, int goalNode[2], std::vector<std::vector<int>> &openNodes, std::vector<std::vector<State>> &grid);

/**
 * @name PrintBoard
 * @brief Print the Board
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
 * @name  ReadBoardFile
 * @brief Read the Board from a text File
 *
 * @param boardFile
 * @return std::vector<std::vector<State>>
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
 * @name   ParseLine
 * @brief  Parse one row from the board
 *
 * @param line
 * @return std::vector<State>
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
 * @name   CellString
 * @brief  Replace the cell with related Shape
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
/**
 * @name  Search
 * @brief the A Search main function
 *
 * @param grid
 * @param startNode
 * @param endNode
 * @return std::vector<std::vector<State>>
 */
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
  // while open vector is non empty {

  while (openNodes.size())
  {

    // Sort the open list by calling `CellSort`. `CellSort` method will sort the open list in a descending order to have the node with the lowest heuristic value at the end of the vector.
    // When you call the `CellSort` method, you will need to pass the memory address of the open vector like that: CellSort(&open) because the argument of the CellSort method is a pointer to a vector.
    CellSort(openNodes);
    // get the last node from the open vector using the '.back()` method and save it to the variable `current_node`.
    std::vector<int> currentNode = openNodes.back();
    // remove the last node from the open vector using the`.pop_back()` method.
    openNodes.pop_back();
    // Get the x and y values from the `current_node`,
    // and set grid[x][y] to kPath.

    currentNode_x = currentNode[0];
    currentNode_y = currentNode[1];

    grid[currentNode_x][currentNode_y] = State::kPath;
    // Check if you've reached the goal. If so, return grid.
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
/**
 * @name   Heuristic
 * @brief  Calculate the Heuristic function between 2 points
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return int
 */
static int Heuristic(int x1, int y1, int x2, int y2)
{
  return (abs(x2 - x1) + abs(y2 - y1));
}
/**
 * @name   AddToOpen
 * @brief  Add a Node to the open Node and close that Node on the Grid
 *
 * @param x
 * @param y
 * @param g
 * @param h
 * @param openNodes
 * @param grid
 */
static void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &openNodes, std::vector<std::vector<State>> &grid)
{
  openNodes.push_back({x, y, g, h});
  grid[x][y] = State::kClosed;
}
/**
 * @name  Compare
 * @brief Compare two nodes based on the lower F value
 *
 * @param firstNode
 * @param secondNode
 * @return true
 * @return false
 */
static bool Compare(std::vector<int> firstNode, std::vector<int> secondNode)
{
  return ((firstNode[2] + firstNode[3]) > (secondNode[2] + secondNode[3]) ? true : false);
}
/**
 * @name  CellSort
 * @brief Sort the Open Nodes based on the lower F (G + H )vaule
 *
 * @param openNodes
 */
static void CellSort(std::vector<std::vector<int>> &openNodes)
{
  sort(openNodes.begin(), openNodes.end(), Compare);
}
/**
 * @name  CheckValidCell
 * @brief check if the cell is in the Grid and empty
 *
 * @param x
 * @param y
 * @param grid
 * @return true
 * @return false
 */
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
/**
 * @name  ExpandNeighbors
 * @brief Get vaild Neighbors cells to the current cell
 *
 * @param currNode
 * @param goalNode
 * @param openNodes
 * @param grid
 */
static void ExpandNeighbors(std::vector<int> currNode, int goalNode[2], std::vector<std::vector<int>> &openNodes, std::vector<std::vector<State>> &grid)
{
  // ExpandNeighbors {
  int neighborNode_x, neighborNode_y, neighborNode_g, neighborNode_h;
  // Get current node's data.
  const int delta[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  // Loop through current node's potential neighbors.
  for (int loopCnt = 0; loopCnt < 4; ++loopCnt)
  {
    neighborNode_x = currNode[0] + delta[loopCnt][0];
    neighborNode_y = currNode[1] + delta[loopCnt][1];
    if (CheckValidCell(neighborNode_x, neighborNode_y, grid))
    {
      // Increment g value, compute h value, and add neighbor to open list.
      neighborNode_g = currNode[2] + 1;
      neighborNode_h = Heuristic(neighborNode_x, neighborNode_y, goalNode[0], goalNode[1]);
      AddToOpen(neighborNode_x, neighborNode_y, neighborNode_g, neighborNode_h, openNodes, grid);
    }
  }
  // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.

  // } End function
}
