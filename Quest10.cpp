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
    vector<vector<char>> board;
    vector<vector<bool>> mineLocations;

public:


private:
    void initializeBoard() {
        board.assign(rows, vector<char>(cols, ' '));
        mineLocations.assign(rows, vector<bool>(cols, false));
    }

    void placeMines() {
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

    void calculateNumbers() {
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

    int countAdjacentMines(int row, int col) const {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                    mineLocations[newRow][newCol]) {
                    count++;
                }
            }
        }
        return count;
    }

    void revealCell(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != ' ') {
            return;
        }

        int adjacentMines = countAdjacentMines(row, col);
        board[row][col] = (adjacentMines == 0) ? ' ' : static_cast<char>('0' + adjacentMines);

        if (adjacentMines == 0) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    revealCell(row + i, col + j);
                }
            }
        }
    }

    bool checkWin() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!mineLocations[i][j] && board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }


public:
    Minesweeper(int rows, int cols, int mines) : rows(rows), cols(cols), totalMines(mines) {
        initializeBoard();
        placeMines();
        calculateNumbers();
    }

    void printBoard(bool showMines = false) const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (mineLocations[i][j] && showMines) {
                    cout << "* ";
                }
                else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    bool play(int row, int col) {
        if (mineLocations[row][col]) {
            cout << "\nGame Over! You hit a mine." << endl;
            return false;
        }
        else {
            revealCell(row, col);
            if (checkWin()) {
                cout << "\nCongratulations! You won!" << endl;
                return false;
            }
            return true;
        }
    }



};

int main() {
    int rows, cols, mines;

    cout << "Enter the number of rows, columns, and mines: ";
    cin >> rows >> cols >> mines;
    
    Minesweeper game(rows, cols, mines);

    while (true)
    {
        int row, col;

        cout << "Enter row and column (starting from 0) to reveal: ";
        cin >> row >> col;
        game.printBoard();
        if (!game.play(row, col)) {
            break;
        }
    }

    game.printBoard(true);

    
    return 0;
}
