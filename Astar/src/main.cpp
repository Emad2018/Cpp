/**
 * @file main.cpp
 * @author Abdelrahman Emad (a.emad02018@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-12-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <string>
#include <vector>
#include "ASearch.hpp"

/**
 * @name main
 * @brief program main function
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, const char *argv[])
{
  std::vector<std::vector<State>> board;
  int startNode[2] = {0, 0};
  int endNode[2] = {4, 5};
  board = ReadBoardFile("../board.txt");
  board = Search(board, startNode, endNode);
  PrintBoard(board);

  return 0;
}