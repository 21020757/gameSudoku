//
// Created by hbduwu on 18-May-22.
//

#ifndef UNTITLED_SOLVE_H
#define UNTITLED_SOLVE_H
#include "game.h"
#define notFilled 0

bool FindUnassignedLocation(int grid[ROWS][COLS], int &row, int &col);
bool isSafe(int grid[ROWS][COLS], int row, int col, int num);
bool solveSudoku(int grid[ROWS][COLS]);
bool FindUnassignedLocation(int ggrid[ROWS][COLS], int &row, int &col);
bool UsedInRow(int grid[ROWS][COLS], int row, int num);
bool UsedInCol(int grid[ROWS][COLS], int col, int num);
bool UsedInBox(int grid[ROWS][COLS], int boxStartRow, int boxStartCol, int num);
bool isSafe(int grid[ROWS][COLS], int row, int col, int num);

#endif //UNTITLED_SOLVE_H
