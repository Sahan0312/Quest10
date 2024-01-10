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


};

int main() {
    int rows, cols, mines;

    cout << "Enter the number of rows, columns, and mines: ";
    cin >> rows >> cols >> mines;
    return 0;
}
