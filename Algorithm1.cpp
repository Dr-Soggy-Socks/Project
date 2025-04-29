#include "Algorithm1.h"
#include <iostream>
#include <algorithm>

// Forward declarations of functions from the main game
void printboard(int n, int moves, int P, const std::vector<std::vector<int>>& board);
bool mergeTiles(std::vector<std::vector<int>>& board, int n, char direction);
void placeNewTile(int n, int P, std::vector<std::vector<int>>& board);
bool checkWin(const std::vector<std::vector<int>>& board);
bool isGameOver(const std::vector<std::vector<int>>& board, int n);
void displayGameOver(int moves);
void displayWin(int moves);

// Implementation of private methods
int Algorithm1::countEmptyCells(const std::vector<std::vector<int>>& testBoard) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (testBoard[i][j] == 0) {
                count++;
            }
        }
    }
    return count;
}

int Algorithm1::countMergeablePairs(const std::vector<std::vector<int>>& testBoard) {
    int count = 0;

    // Check horizontal merges
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (testBoard[i][j] != 0 && testBoard[i][j] == testBoard[i][j + 1]) {
                count++;
            }
        }
    }

    // Check vertical merges
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n - 1; i++) {
            if (testBoard[i][j] != 0 && testBoard[i][j] == testBoard[i + 1][j]) {
                count++;
            }
        }
    }

    return count;
}

int Algorithm1::evaluateMove(char direction) {
    // Make a copy of the board to simulate move
    std::vector<std::vector<int>> testBoard = board;

    // Check if move is valid
    bool validMove = mergeTiles(testBoard, n, direction);
    if (!validMove) {
        return -1; // Invalid move
    }

    // Count empty cells after move
    int emptyCells = countEmptyCells(testBoard);

    // Count potentially mergeable pairs after move
    int mergeablePairs = countMergeablePairs(testBoard);

    // Score is weighted combination of empty cells and mergeable pairs
    // We prioritize creating empty cells but also value potential merges
    return emptyCells * 2 + mergeablePairs * 3;
}

char Algorithm1::convertMoveForDisplay(char move) {
    switch (move) {
        case 'w': return 'U';
        case 's': return 'D';
        case 'a': return 'L';
        case 'd': return 'R';
        default: return move;
    }
}

// Implementation of public methods
Algorithm1::Algorithm1(int boardSize, int reverseValue) : n(boardSize), P(reverseValue), moves(0) {
    // Initialize board
    board = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));

    // Place initial tile
    placeNewTile(n, P, board);
}

char Algorithm1::makeMove() {
    std::vector<char> directions = {'w', 's', 'a', 'd'};
    char bestMove = 'x'; // Default to invalid move
    int bestScore = -1;

    // Evaluate each possible move
    for (char dir : directions) {
        int score = evaluateMove(dir);
        if (score > bestScore) {
            bestScore = score;
            bestMove = dir;
        }
    }

    // If no good move is found, try any valid move
    if (bestMove == 'x') {
        for (char dir : directions) {
            std::vector<std::vector<int>> testBoard = board;
            if (mergeTiles(testBoard, n, dir)) {
                bestMove = dir;
                break;
            }
        }
    }

    // If still no valid move, game is over
    if (bestMove == 'x') {
        return 'q'; // Quit
    }

    // Apply the best move
    mergeTiles(board, n, bestMove);
    placeNewTile(n, P, board);
    moves++;
    moveHistory.push_back(bestMove);

    return bestMove;
}

void Algorithm1::play(bool showAllBoards) {
    std::cout << "Starting automated gameplay with Algorithm1...\n";
    std::cout << "Board size: " << n << "x" << n << ", Reverse mode: " << P << "\n\n";

    // Initial board state
    if (showAllBoards) {
        printboard(n, moves, P, board);
        std::cout << "Algorithm is thinking...\n";
    }

    // Game loop
    while (moves < 1000) { // Limit to 1000 moves
        // Check for win
        if (checkWin(board)) {
            displayWin(moves);
            printboard(n, moves, P, board);
            displayMoveHistory();
            return;
        }

        // Check for game over
        if (isGameOver(board, n)) {
            displayGameOver(moves);
            printboard(n, moves, P, board);
            displayMoveHistory();
            return;
        }

        // Make the best move
        char move = makeMove();
        if (move == 'q') {
            std::cout << "No valid moves available. Game over.\n";
            displayGameOver(moves);
            printboard(n, moves, P, board);
            displayMoveHistory();
            return;
        }

        // Display the board after every move if requested
        if (showAllBoards) {
            printboard(n, moves, P, board);
            std::cout << "Move #" << moves << ": " << convertMoveForDisplay(move) << "\n";
        } else if (moves % 100 == 0) {
            // Show progress every 100 moves
            std::cout << "Moves completed: " << moves << "\n";
        }
    }

    // If we've made 1000 moves without winning
    std::cout << "Move limit (1000) reached without solving the puzzle.\n";
    printboard(n, moves, P, board);
    displayMoveHistory();
}

void Algorithm1::displayMoveHistory() {
    std::cout << "\nMove History (" << moveHistory.size() << " moves):\n";
    std::string history = "";
    for (size_t i = 0; i < moveHistory.size(); i++) {
        history += convertMoveForDisplay(moveHistory[i]);
        if ((i + 1) % 50 == 0) {
            history += "\n";
        } else if ((i + 1) % 10 == 0) {
            history += " | ";
        } else {
            history += " ";
        }
    }
    std::cout << history << "\n\n";
}

std::vector<std::vector<int>> Algorithm1::getBoard() const {
    return board;
}

int Algorithm1::getMoves() const {
    return moves;
}
