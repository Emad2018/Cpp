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
void PrintBoard(std::vector<std::vector<State>> board);
std::vector<std::vector<State>> ReadBoardFile(std::string boardFile);
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, int startNode[2], int endNode[2]);
#endif /* ASEARCH_HPP */
