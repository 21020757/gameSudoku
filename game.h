//
// Created by hbduwu on 16-May-22.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H


#include "header.h"
#include "grid.h"


#define ROWS 9
#define COLS 9
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
static SDL_Window * window = nullptr;
static SDL_Renderer * renderer = nullptr;
static SDL_Texture* background = nullptr;
static TTF_Font *myFont = nullptr;
static Mix_Chunk* soundEffect = nullptr;
//init
void loadNums(int board[][COLS], const string& filename); //Init
bool initSDL();
void closeSDL(Grid board[][COLS]);
void initBoard(Grid board[][COLS], TTF_Font *fontFam);

//rendering
void renderNums(Grid board[][COLS], TTF_Font *font);//Rendering functions
void renderColors(Grid board[][COLS]);
void drawGrid();

//gamefunc
void getGridPos(int x, int y, int *i, int *j);//Main game functions
void clearActiveStates(Grid board[][COLS]);
void checkMove(Grid board[][COLS], int row, int col);

//win check
bool isAllFilled(Grid mainboard[][COLS]);
bool isWin(Grid mainboard[][COLS]);
//stuff
void printPic(const string& path);
void playGame();
int randomNum();


SDL_Texture *loadString(const char* message, TTF_Font *font);
SDL_Texture *numToText(int num, TTF_Font *font);
SDL_Texture *loadTexture(const string& path, SDL_Renderer* renderer);
#endif //UNTITLED_GAME_H
