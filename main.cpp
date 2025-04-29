#include <iostream>
#include <vector>
#include <cstdlib> // For rand and srand
#include <ctime>   // For time (seeding rand)
#include <limits>  // For numeric_limits
#include "Algorithm1.h"

using namespace std;

// Function declarations
void printboard(int n, int moves, int P, const vector<vector<int>>& board);
bool processMove(int n, char& option, vector<vector<int>>& board);
void placeNewTile(int n, int P, vector<vector<int>>& board);
bool mergeTiles(vector<vector<int>>& board, int n, char direction);
bool checkWin(const vector<vector<int>>& board);
bool isGameOver(const vector<vector<int>>& board, int n);
bool canMove(const vector<vector<int>>& board, int n);
void displayGameOver(int moves);
void displayWin(int moves);

int main() {
    srand(time(0)); // Seed the random number generator
    int n; // Board size
    int P;
    char gameMode;

    // Choose between manual play or algorithm play
    cout << "Choose game mode:\n";
    cout << "1. Manual play\n";
    cout << "2. Algorithm1 play\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> gameMode;

    // Get board size with validation
    do {
        cout << "Enter board size 5x5, 4x4 or 3x3; enter only 3, 4 or 5: \n";
        cin >> n;
        cout << endl;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            n = 0;
        }
    } while(n < 3 || n > 5);

    // Ask for tile value (P)
    do {
        cout << "Enter 512, 256 or 128 for reverse mode: \n";
        cin >> P;
        cout << endl;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            P = 0;
        }
    } while (P != 512 && P != 256 && P != 128);

    if (gameMode == '2') {
        // Algorithm play
        char showBoards;
        cout << "Show all board states? (y/n): ";
        cin >> showBoards;

        Algorithm1 algorithm(n, P);
        algorithm.play(showBoards == 'y' || showBoards == 'Y');
    } else {
        // Original manual play mode
        vector<vector<int>> board(n, vector<int>(n, 0)); // Create empty board
        char option;
        int moves = 0;
        bool gameWon = false;
        bool gameOver = false;

        // Place initial tile
        placeNewTile(n, P, board);

        // Game loop
        do {
            printboard(n, moves, P, board);

            // Check for win condition
            if (checkWin(board)) {
                displayWin(moves);
                gameWon = true;
                break;
            }

            // Check for game over condition
            if (isGameOver(board, n)) {
                displayGameOver(moves);
                gameOver = true;
                break;
            }

            cout << "Go up down left or right; with w, s, a, d respectively (q to quit): ";
            cin >> option;

            bool validMove = false;

            if (option == 'w' || option == 's' || option == 'a' || option == 'd') {
                validMove = mergeTiles(board, n, option);

                if (!validMove) {
                    cout << "No tiles moved. Try another direction.\n";
                } else {
                    placeNewTile(n, P, board);
                    moves++;
                }
            } else if (option == 'q') {
                cout << "GoodBye\n";
            } else {
                cout << "Invalid input, try again.\n";
            }
        } while(option != 'q');

        // Show final board state
        if (gameWon || gameOver) {
            printboard(n, moves, P, board);
        }
    }

    return 0;
}

// Print the current state of the board
void printboard(int n, int moves, int P, const vector<vector<int>>& board) {
    cout << "\n=== Reverse " << P << " Mode ===\n\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl << endl;
    }
    cout << "Moves: " << moves << endl;
}

// Process user input and update board
bool processMove(int n, char& option, vector<vector<int>>& board) {
    cout << "Go up down left or right; with w, s, a, d respectively (q to quit): ";
    cin >> option;

    bool validMove = false;

    if (option == 'w' || option == 's' || option == 'a' || option == 'd') {
        validMove = mergeTiles(board, n, option);

        if (!validMove) {
            cout << "No tiles moved. Try another direction.\n";
        }
    } else if (option == 'q') {
        return false;
    } else {
        cout << "Invalid input, try again.\n";
    }

    return validMove;
}

// Place a new tile based on reverse mode
void placeNewTile(int n, int P, vector<vector<int>>& board) {
    vector<pair<int, int>> emptyCells;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(board[i][j] == 0) {
                emptyCells.push_back(make_pair(i, j));
            }
        }
    }

    if(!emptyCells.empty()) {
        int idx = rand() % emptyCells.size();
        int i = emptyCells[idx].first;
        int j = emptyCells[idx].second;

        vector<int> allowedValues;
        if (P == 512) {
            allowedValues = {256, 128, 64};
        } else if (P == 256) {
            allowedValues = {128, 64, 32};
        } else if (P == 128) {
            allowedValues = {64, 32, 16};
        } else {
            allowedValues = {2, 4}; // fallback
        }

        int value = allowedValues[rand() % allowedValues.size()];
        board[i][j] = value;
    }
}

// Move and merge logic for tiles - 2048 style
bool mergeTiles(vector<vector<int>>& board, int n, char direction) {
    bool changed = false;

    if (direction == 'w') { // Up
        for (int col = 0; col < n; col++) {
            // Collect non-zero values
            vector<int> values;
            for (int row = 0; row < n; row++) {
                if (board[row][col] != 0) {
                    values.push_back(board[row][col]);
                    board[row][col] = 0;
                }
            }

            if (values.empty()) continue;

            // Process merges
            vector<int> mergedValues;
            for (size_t i = 0; i < values.size(); i++) {
                if (i + 1 < values.size() && values[i] == values[i + 1]) {
                    // When merging in reverse mode, we divide by 2
                    int mergedValue = values[i] / 2;
                    if (mergedValue == 0) mergedValue = 1; // Minimum value is 1
                    mergedValues.push_back(mergedValue);
                    i++; // Skip the next element as it's been merged
                    changed = true;
                } else {
                    mergedValues.push_back(values[i]);
                }
            }

            // Place values back on the board
            for (size_t i = 0; i < mergedValues.size(); i++) {
                board[i][col] = mergedValues[i];
            }

            changed = true; // Movement happened
        }
    }
    else if (direction == 's') { // Down
        for (int col = 0; col < n; col++) {
            // Collect non-zero values from bottom to top
            vector<int> values;
            for (int row = n - 1; row >= 0; row--) {
                if (board[row][col] != 0) {
                    values.push_back(board[row][col]);
                    board[row][col] = 0;
                }
            }

            if (values.empty()) continue;

            // Process merges
            vector<int> mergedValues;
            for (size_t i = 0; i < values.size(); i++) {
                if (i + 1 < values.size() && values[i] == values[i + 1]) {
                    int mergedValue = values[i] / 2;
                    if (mergedValue == 0) mergedValue = 1;
                    mergedValues.push_back(mergedValue);
                    i++; // Skip the next element
                    changed = true;
                } else {
                    mergedValues.push_back(values[i]);
                }
            }

            // Place values back on the board from bottom to top
            for (size_t i = 0; i < mergedValues.size(); i++) {
                board[n - 1 - i][col] = mergedValues[i];
            }

            changed = true;
        }
    }
    else if (direction == 'a') { // Left
        for (int row = 0; row < n; row++) {
            // Collect non-zero values from left to right
            vector<int> values;
            for (int col = 0; col < n; col++) {
                if (board[row][col] != 0) {
                    values.push_back(board[row][col]);
                    board[row][col] = 0;
                }
            }

            if (values.empty()) continue;

            // Process merges
            vector<int> mergedValues;
            for (size_t i = 0; i < values.size(); i++) {
                if (i + 1 < values.size() && values[i] == values[i + 1]) {
                    int mergedValue = values[i] / 2;
                    if (mergedValue == 0) mergedValue = 1;
                    mergedValues.push_back(mergedValue);
                    i++; // Skip the next element
                    changed = true;
                } else {
                    mergedValues.push_back(values[i]);
                }
            }

            // Place values back on the board from left to right
            for (size_t i = 0; i < mergedValues.size(); i++) {
                board[row][i] = mergedValues[i];
            }

            changed = true;
        }
    }
    else if (direction == 'd') { // Right
        for (int row = 0; row < n; row++) {
            // Collect non-zero values from right to left
            vector<int> values;
            for (int col = n - 1; col >= 0; col--) {
                if (board[row][col] != 0) {
                    values.push_back(board[row][col]);
                    board[row][col] = 0;
                }
            }

            if (values.empty()) continue;

            // Process merges
            vector<int> mergedValues;
            for (size_t i = 0; i < values.size(); i++) {
                if (i + 1 < values.size() && values[i] == values[i + 1]) {
                    int mergedValue = values[i] / 2;
                    if (mergedValue == 0) mergedValue = 1;
                    mergedValues.push_back(mergedValue);
                    i++; // Skip the next element
                    changed = true;
                } else {
                    mergedValues.push_back(values[i]);
                }
            }

            // Place values back on the board from right to left
            for (size_t i = 0; i < mergedValues.size(); i++) {
                board[row][n - 1 - i] = mergedValues[i];
            }

            changed = true;
        }
    }

    return changed;
}

// Check if any tile has reached the value 2 (win condition)
bool checkWin(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int value : row) {
            if (value == 2) {
                return true;
            }
        }
    }
    return false;
}

// Check if the game is over (board full and no possible moves)
bool isGameOver(const vector<vector<int>>& board, int n) {
    for (const auto& row : board) {
        for (int value : row) {
            if (value == 0) {
                return false;
            }
        }
    }
    return !canMove(board, n);
}

// Check if any moves are possible
bool canMove(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (board[i][j] == board[i][j + 1]) {
                return true;
            }
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n - 1; i++) {
            if (board[i][j] == board[i + 1][j]) {
                return true;
            }
        }
    }

    return false;
}

// Display a visually prominent game over message
void displayGameOver(int moves) {
    cout << "\n";
    cout << "******************************\n";
    cout << "*                            *\n";
    cout << "*         GAME OVER          *\n";
    cout << "*                            *\n";
    cout << "* Board is full and no more  *\n";
    cout << "* moves are possible.        *\n";
    cout << "*                            *\n";
    cout << "* Total moves: " << moves << (moves < 10 ? "           *\n" : "          *\n");
    cout << "*                            *\n";
    cout << "******************************\n\n";
}

// Display a visually prominent win message
void displayWin(int moves) {
    cout << "\n";
    cout << "******************************\n";
    cout << "*                            *\n";
    cout << "*       YOU HAVE WON!        *\n";
    cout << "*                            *\n";
    cout << "* You reached the value of 2 *\n";
    cout << "* and completed the game!    *\n";
    cout << "*                            *\n";
    cout << "* Total moves: " << moves << (moves < 10 ? "           *\n" : "          *\n");
    cout << "*                            *\n";
    cout << "******************************\n\n";
}
