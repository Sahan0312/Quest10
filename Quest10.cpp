#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int rows;
    int cols;
    int totalMines;
    int flags;  // Track the number of flags remaining
    vector<vector<char>> board;
    vector<vector<bool>> mineLocations;
    vector<vector<bool>> revealed;

    void initializeBoard();
    void placeMines();
    void calculateNumbers();
    int countAdjacentMines(int row, int col) const;
    void revealCell(int row, int col);

public:
    Minesweeper(int rows, int cols, int mines);

    void printBoard() const;
    bool play(int row, int col, char command);
    bool checkWin() const;
};

Minesweeper::Minesweeper(int rows, int cols, int mines) : rows(rows), cols(cols), totalMines(mines), flags(mines) {
    initializeBoard();
    placeMines();
    calculateNumbers();
}

void Minesweeper::initializeBoard() {
    board.assign(rows, vector<char>(cols, 'c'));
    mineLocations.assign(rows, vector<bool>(cols, false));
    revealed.assign(rows, vector<bool>(cols, false));
}

void Minesweeper::placeMines() {
    srand(static_cast<unsigned>(time(nullptr)));
    int minesPlaced = 0;

    while (minesPlaced < totalMines) {
        int randRow = rand() % rows;
        int randCol = rand() % cols;

        if (!mineLocations[randRow][randCol]) {
            mineLocations[randRow][randCol] = true;
            minesPlaced++;
        }
    }
}

void Minesweeper::calculateNumbers() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!mineLocations[i][j]) {
                int count = countAdjacentMines(i, j);
                if (count > 0) {
                    board[i][j] = static_cast<char>('0' + count);
                }
            }
        }
    }
}

int Minesweeper::countAdjacentMines(int row, int col) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && mineLocations[newRow][newCol]) {
                count++;
            }
        }
    }
    return count;
    
}

void Minesweeper::revealCell(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || revealed[row][col]) {
        return;
    }

    revealed[row][col] = true;

    if (mineLocations[row][col]) {
        // Game over if a mine is revealed
        cout << "\nGame Over! You hit a mine." << endl;
    } else if (board[row][col] == ' ') {
        // If no adjacent mines, recursively reveal neighbors
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                revealCell(row + i, col + j);
            }
        }
    }
    
}

bool Minesweeper::checkWin() const {

     for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!mineLocations[i][j] && !revealed[i][j]) {
                return false;
            }
        }
    }
    return true;
    
}

void Minesweeper::printBoard() const {

     cout << "  ";
    for (int i = 0; i < cols; ++i) {
        cout << char('A' + i) << " ";
    }
    cout << endl;

    for (int i = 0; i < rows; ++i) {
        cout << char('A' + i) << " ";
        for (int j = 0; j < cols; ++j) {
            if (!revealed[i][j]) {
                cout << "c ";
            } else if (mineLocations[i][j]) {
                cout << "* ";
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }


    
}


bool Minesweeper::play(int row, int col, char command) {

    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        cout << "Invalid input! Please enter valid row and column values." << endl;
        return true;  // Continue the game
    }

    if (command == 'F') {
        // Place a flag
        if (flags > 0 && !revealed[row][col]) {
            board[row][col] = 'F';
            flags--;
            revealCell(row, col);
        } else {
            cout << "Cannot place a flag here." << endl;
        }
    } else if (command == 'R') {
        // Reveal the cell
        revealCell(row, col);
        if (checkWin()) {
            cout << "\nCongratulations! You won!" << endl;
            return false;  // End the game
        }
    } else {
        cout << "Invalid command! Please enter F for flag or R for reveal." << endl;
    }

    return true;  // Continue the game
    
}

int main() {
    int choice;
    cout << "Select the field option (1: 10x10, 2: 15x15, 3: 20x20): ";
    cin >> choice;

    int rows, cols, mines;
    switch (choice) {
        case 1:
            rows = cols = 10;
            mines = 12;
            break;
        case 2:
            rows = cols = 15;
            mines = 18;
            break;
        case 3:
            rows = cols = 20;
            mines = 24;
            break;
        default:
            cout << "Invalid choice! Exiting..." << endl;
            return 1;
    }

    Minesweeper game(rows, cols, mines);

    while (true) {
        game.printBoard();

        int row, col;
        char command;

        cout << "Enter row and column (starting from 0) and command (F for flag, R for reveal): ";
        cin >> row >> col >> command;

        if (!game.play(row, col, command)) {
            break;  // End the game
        }
    }

    
}