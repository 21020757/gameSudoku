//
// Created by hbduwu on 18-May-22.
//

#include "solve.h"

bool solveSudoku(int grid[ROWS][COLS])
{
    int row, col;
    if (!FindUnassignedLocation(grid, row, col))
        return true;
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = notFilled;
        }
    }
    return false;
}

/* Searches the grid to find an entry that is still unassigned. */
bool FindUnassignedLocation(int grid[ROWS][COLS], int &row, int &col)
{
    for (row = 0; row < ROWS; row++)
        for (col = 0; col < COLS; col++)
            if (grid[row][col] == notFilled)
                return true;
    return false;
}

/* Returns whether any assigned entry n the specified row matches
   the given number. */
bool UsedInRow(int grid[ROWS][COLS], int row, int num)
{
    for (int col = 0; col < COLS; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns whether any assigned entry in the specified column matches
   the given number. */
bool UsedInCol(int grid[ROWS][COLS], int col, int num)
{
    for (int row = 0; row < ROWS; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches
   the given number. */
bool UsedInBox(int grid[ROWS][COLS], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

/* Returns whether it will be legal to assign num to the given row,col location.
 */
bool isSafe(int grid[ROWS][COLS], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row % 3 , col - col % 3, num);
}
