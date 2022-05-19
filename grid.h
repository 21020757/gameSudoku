//
// Created by hbduwu on 17-May-22.
//

#ifndef UNTITLED_GRID_H
#define UNTITLED_GRID_H

#include "header.h"

//Tile datatype. Contains the sudoku value, state of the square, rectangular position and size, and the texture
struct Grid {
    int value;		//numeric value stored in the tile
    bool isInitial;	//Was this initially loaded? Can it be modified?
    bool isActive;	//Is the tile active, i.e. was it clicked?
    bool isHalfActive;
    bool isError;	//Is the tile correct? Is there a game rule conflict?
    bool changed;	//Change flag for updating the number texture
    bool recentlyFilled;
    SDL_Rect square;	//Rectangle containing position and size of each tile
    SDL_Texture * numTexture;	//Pointer to the texture for the number in the tile
};


#endif //UNTITLED_GRID_H
