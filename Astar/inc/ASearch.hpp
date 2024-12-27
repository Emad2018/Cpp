#ifndef ASEARCH_HPP
#define ASEARCH_HPP
enum class State
{
    kEmpty,
    kObstacle,
    kClosed,
    kPath,
    kStart,
    kFinish
};
/**
 * @name PrintBoard
 * @brief Print the Board
 *
 * @param board
 */
void PrintBoard(std::vector<std::vector<State>> board);
/**
 * @name  ReadBoardFile
 * @brief Read the Board from a text File
 *
 * @param boardFile
 * @return std::vector<std::vector<State>>
 */
std::vector<std::vector<State>> ReadBoardFile(std::string boardFile);
/**
 * @name  Search
 * @brief the A Search main function
 *
 * @param grid
 * @param startNode
 * @param endNode
 * @return std::vector<std::vector<State>>
 */
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, int startNode[2], int endNode[2]);
#endif /* ASEARCH_HPP */
