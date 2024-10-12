#include <iostream>
#include <vector>

using namespace std;

// Function to display the Tic-Tac-Toe board
void displayBoard(const vector<vector<char>>& board) {
    cout << "\n    1   2   3\n"; // Column headers
    
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << " | "; // Row headers
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | "; // Column separator
        }
        cout << " |\n"; // Right border
        if (i < 2) {
            cout << "  |---|---|---|\n"; // Middle border between rows
        }
    }
    
    cout << "\n";
}
// Function to check if a player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Function to check if the board is full (draw condition)
bool checkDraw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char spot : row) {
            if (spot == ' ') return false;
        }
    }
    return true;
}

// Function to get player move
pair<int, int> getPlayerMove(const vector<vector<char>>& board, char player) {
    int row, col;
    while (true) {
        cout << "Player " << player << ", enter your move (row and column: 1 1 for top-left): ";
        cin >> row >> col;
        row--; col--; // Convert to 0-based index
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            return {row, col};
        }
        cout << "Invalid move! Please try again.\n";
    }
}

// Minimax algorithm for AI
int minimax(vector<vector<char>>& board, bool isMaximizing) {
    if (checkWin(board, 'O')) return 1;
    if (checkWin(board, 'X')) return -1;
    if (checkDraw(board)) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(board, false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(board, true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

// Function for AI move
pair<int, int> getAIMove(vector<vector<char>>& board) {
    int bestScore = -1000;
    pair<int, int> move = {-1, -1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O'; // AI is O
                int score = minimax(board, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    move = {i, j};
                }
            }
        }
    }
    return move;
}

// Main game function
void ticTacToe() {
    while (true) {
        vector<vector<char>> board(3, vector<char>(3, ' '));
        displayBoard(board);

        // Ask if player wants to play against a friend or the computer
        int mode;
        cout << "Enter 1 to play against a friend, 2 to play against the computer: ";
        cin >> mode;

        char currentPlayer = 'X'; // Player X starts
        bool gameOver = false;

        while (!gameOver) {
            if (currentPlayer == 'X') {
                auto [row, col] = getPlayerMove(board, currentPlayer);
                board[row][col] = currentPlayer;
            } else {
                if (mode == 1) {
                    auto [row, col] = getPlayerMove(board, currentPlayer);
                    board[row][col] = currentPlayer;
                } else {
                    cout << "Computer's turn...\n";
                    auto [row, col] = getAIMove(board);
                    board[row][col] = currentPlayer;
                }
            }

            displayBoard(board);

            if (checkWin(board, currentPlayer)) {
                cout << "Player " << currentPlayer << " wins!\n";
                gameOver = true;
            } else if (checkDraw(board)) {
                cout << "It's a draw!\n";
                gameOver = true;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        // Ask to restart the game
        char restart;
        cout << "Do you want to play again? (y/n): ";
        cin >> restart;
        if (restart != 'y') break;
    }
}

// Entry point of the program
int main() {
    ticTacToe();
    return 0;
}
