#ifndef ALGORITHM1_H
#define ALGORITHM1_H

#include <vector>
#include <string>

class Algorithm1 {
private:
    int n; // Board size
    int P; // Reverse mode value
    std::vector<std::vector<int>> board;
    int moves;
    std::vector<char> moveHistory; // Store move history

    // Function to count empty cells in a board
    int countEmptyCells(const std::vector<std::vector<int>>& testBoard);

    // Function to count mergeable pairs in a board
    int countMergeablePairs(const std::vector<std::vector<int>>& testBoard);

    // Evaluate a potential move
    int evaluateMove(char direction);

    // Convert WASD to UDLR for display
    char convertMoveForDisplay(char move);

public:
    // Constructor
    Algorithm1(int boardSize, int reverseValue);

    // Make the best move based on evaluation
    char makeMove();

    // Play the game automatically
    void play(bool showAllBoards = true);

    // Display move history
    void displayMoveHistory();

    // Getter for the board
    std::vector<std::vector<int>> getBoard() const;

    // Getter for number of moves
    int getMoves() const;
};

#endif // ALGORITHM1_H
