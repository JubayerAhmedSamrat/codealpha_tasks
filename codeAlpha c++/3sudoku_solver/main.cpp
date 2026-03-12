#include <iostream>
using namespace std;

#define N 9

// Print Sudoku grid
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}

// Check if number is in row
bool usedInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Check column
bool usedInCol(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Check 3x3 box
bool usedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + boxStartRow][j + boxStartCol] == num)
                return true;
    return false;
}

// Check if safe to place number
bool isSafe(int grid[N][N], int row, int col, int num) {
    return !usedInRow(grid, row, num) &&
           !usedInCol(grid, col, num) &&
           !usedInBox(grid, row - row % 3, col - col % 3, num);
}

// Find empty cell
bool findEmpty(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

// Backtracking solver
bool solveSudoku(int grid[N][N]) {
    int row, col;

    if (!findEmpty(grid, row, col))
        return true;  // solved

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0;  // backtrack
        }
    }
    return false;
}

int main() {
    int grid[N][N];

    cout << "Enter Sudoku (9x9), use 0 for empty:\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> grid[i][j];

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}

