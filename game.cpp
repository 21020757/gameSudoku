//
// Created by hbduwu on 16-May-22.
//
#include "game.h"
#include "random.cpp"
#include "solve.h"

bool playMore = false;
SDL_Event e;

void playGame () {
    Grid mainboard[ROWS][COLS];
    if (!initSDL()) {
        cout << "Failed to initilize!";
    }
    else {
        printPic("pics/sudoku.png");
            while(playMore) {
                soundEffect = Mix_LoadWAV("sounds/game-start-6104.wav");
                Mix_PlayChannel(1,soundEffect,0);
                soundEffect = Mix_LoadWAV("sounds/sound.wav");
                bool isNotPlaying = false;
                int i = 0, j = 0;
                bool GridActive = false;
                myFont = TTF_OpenFont("fonts/OpenSans-VariableFont_wdth,wght.ttf", 120);
                if (myFont == nullptr) {
                    cout << "Font could not be located! TTF error: " << TTF_GetError();
                    isNotPlaying = true;
                }
                initBoard(mainboard, myFont);
                while (!isNotPlaying) {
                    static int x, y;
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            isNotPlaying = true;
                            playMore = false;
                        }
                        else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                            SDL_GetMouseState(&x, &y);
                            cout << x << " " << y << endl;
                            getGridPos(x, y, &i, &j);
                            clearActiveStates(mainboard);
                            if (e.button.button == SDL_BUTTON_LEFT) {
                                Mix_PlayChannel(1,soundEffect,0);
                                mainboard[i][j].isActive = true;
                                for (int k = 0; k < ROWS; k++) {
                                    mainboard[k][j].isHalfActive = true;
                                }
                                for (int k = 0; k < COLS; k++) {
                                    mainboard[i][k].isHalfActive = true;
                                }
                                for (int row = 0; row < 3; row++) {
                                    for (int col = 0; col < 3; col++) {
                                        mainboard[row + i - i % 3][col + j - j % 3].isHalfActive = true;
                                    }
                                }
                                for (int k = 0; k < ROWS; k++) {
                                    for (int m = 0; m < COLS; m++) {
                                        if (mainboard[k][m].value == mainboard[i][j].value &&
                                            mainboard[k][m].value != 0)
                                            mainboard[k][m].isActive = true;
                                    }
                                }
                                GridActive = true;
                            } else {
                                if (mainboard[i][j].isActive) {
                                    mainboard[i][j].isActive = false;
                                }
                                GridActive = false;
                            }
                        } else if (e.type == SDL_KEYDOWN && GridActive) {
                            Mix_PlayChannel(1,soundEffect,0);
                            clearActiveStates(mainboard);
                            switch (e.key.keysym.sym) {
                                case SDLK_ESCAPE: isNotPlaying = true;break;
                                case SDLK_UP: {
                                    if (y <= SCREEN_HEIGHT/9) break;
                                    else {
                                        y -= SCREEN_HEIGHT/9;
                                    }
                                    break;
                                }
                                case SDLK_DOWN:{
                                    if (y >= 8*SCREEN_HEIGHT/9) break;
                                    else {
                                        y += SCREEN_HEIGHT/9;
                                    }
                                    break;
                                }
                                case SDLK_LEFT: {
                                    if (x <= SCREEN_WIDTH/9) break;
                                    else {
                                        x -= SCREEN_WIDTH/9;
                                    }
                                    break;
                                }
                                case SDLK_RIGHT:{
                                    if (x >= 8*SCREEN_WIDTH/9) break;
                                    else {
                                        x += SCREEN_WIDTH/9;
                                    }
                                    break;
                                }
                            }
                            getGridPos(x,y,&i,&j);
                            mainboard[i][j].isActive = true;
                            for (int k = 0; k < ROWS; k++) {
                                mainboard[k][j].isHalfActive = true;
                            }
                            for (int k = 0; k < COLS; k++) {
                                mainboard[i][k].isHalfActive = true;
                            }
                            for (int row = 0; row < 3; row++) {
                                for (int col = 0; col < 3; col++) {
                                    mainboard[row + i - i % 3][col + j - j % 3].isHalfActive = true;
                                }
                            }
                            for (int k = 0; k < 10; k++) {
                                if ((e.key.keysym.sym == SDLK_0 + k) || (e.key.keysym.sym == SDLK_DELETE) ||
                                    (e.key.keysym.sym == SDLK_SPACE) || (e.key.keysym.sym == SDLK_BACKSPACE)) {
                                    if (!mainboard[i][j].isInitial) {
                                        mainboard[i][j].value = k;
                                        if (mainboard[i][j].value != 0) mainboard[i][j].recentlyFilled = true;
                                        else mainboard[i][j].recentlyFilled = false;
                                        mainboard[i][j].changed = true;
                                        checkMove(mainboard, i, j);
                                        break;
                                    }
                                }
                            }
                            for (int k = 0; k < ROWS; k++) {
                                for (int m = 0; m < COLS; m++) {
                                    if (mainboard[k][m].value == mainboard[i][j].value &&
                                        mainboard[k][m].value != 0)
                                        mainboard[k][m].isActive = true;
                                }
                            }
                        }
                    }
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);

                    renderColors(mainboard);
                    renderNums(mainboard, myFont);
                    drawGrid();
                    SDL_RenderPresent(renderer);

                    //win check
                    if (isAllFilled(mainboard) || (isAllFilled(mainboard) && isWin(mainboard))) {
                        soundEffect = Mix_LoadWAV("sounds/Victory Sound Effect.wav");
                        Mix_PlayChannel(1,soundEffect,0);
                        isNotPlaying = true;
                        printPic("pics/winning.png");
                    }
                }
            }
        closeSDL(mainboard);
    }
}
bool isWin (Grid mainboard[][COLS]) {
    int ran = randomNum();
    int solvedGrid[ROWS][COLS];
    loadNums(solvedGrid,randomGrid[ran]);
    solveSudoku(solvedGrid);
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (mainboard[row][col].value != solvedGrid[row][col]) return false;
        }
    }
    return true;
}

bool isAllFilled (Grid mainboard[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (mainboard[i][j].isError || !mainboard[i][j].value) return false;
        }
    }
    return true;
}
int randomNum(){
    int ran = rand() % 16;
    return ran;
}

void printPic(const string& path) {
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_y) {
                    quit = true;
                    playMore = true;
                }
                else if (e.key.keysym.sym == SDLK_n){
                    quit = true;
                }
            }
            background = loadTexture(path, renderer);
            SDL_RenderCopy(renderer, background, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        }
    }

}



//game function
void getGridPos(int x, int y, int * i, int * j) {
    int k;
    for (k = 0; k < 9; k++) {
        if (y >= (k * SCREEN_HEIGHT / 9) && y < ((k + 1) * SCREEN_HEIGHT / 9) )
            *i = k;
    }

    for (k = 0; k < 9; k++) {
        if (x >= (k * SCREEN_WIDTH / 9) && x < ((k + 1) * SCREEN_WIDTH / 9) )
            *j = k;
    }
}


void clearActiveStates(Grid board[][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++){
            board[i][j].isActive = false;
            board[i][j].isHalfActive = false;
        }
    }
}

void checkMove(Grid board[][COLS], int row, int col) {
    int i, j, subrow, subcol;
    bool isSuitable = true;
    subrow = row / 3;
    subcol = col / 3;
    if (board[row][col].value) {
        for (j = 0; j < ROWS; j++) {
            if (board[row][j].value == board[row][col].value && j != col) {
                board[row][col].isError = true;
                cout << "Row confliction!" << endl;
                isSuitable = false;
            }
        }
        for (i = 0; i < COLS; i++) {
            if (board[i][col].value == board[row][col].value && i != row) {
                board[row][col].isError = true;
                cout << "Column confliction!" << endl;
                isSuitable = false;
            }
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[row][col].value == board[subrow * 3 + i][subcol * 3 + j].value && (subrow * 3 + i != row) &&
                    (subcol * 3 + j != col)) {
                    board[row][col].isError = true;
                    cout << "Subsquare confliction!" << endl;
                    isSuitable = false;
                }
            }
        }
    }
    if (isSuitable) {
        board[row][col].isError = false;
        for (i = 0; i < COLS; i++) {
            board[row][i].isError = false;
        }
        for (i = 0; i < ROWS; i++) {
            board[i][col].isError = false;
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                    board[subrow * 3 + i][subcol* 3 + j].isError = false;
                }
            }
    }
}


//init
void loadNums(int board[][COLS],const string& filename) {
    int row = 0, col = 0;
    for (int k = 0; k < filename.length(); k++) {
        if (col == 9) {
            col = 0;
            row++;
        }
        if(isdigit(filename[k])) {
            board[row][col] = filename[k] - 48;
            col++;
        }
    }
}

bool initSDL() {
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL failed to initialize! SDL Error: " << SDL_GetError();
        success = false;
    }
    else {
        window = SDL_CreateWindow( "Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN );
        if (window == nullptr) {
            cout << "Window couldn't be created! SDL error: " << SDL_GetError();
            success = false;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr) {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError();
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                if (TTF_Init() == -1) {
                    cout << "Failed to initialize font! Error: " <<  TTF_GetError();
                    success = false;
                }
                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0) {
                    cout << "Failed to initialize audio! Error: " << Mix_GetError();
                    success = false;
                }
            }
        }
    }
    return success;
}

void closeSDL(Grid board[][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j].numTexture != nullptr) {
                SDL_DestroyTexture(board[i][j].numTexture);
                board[i][j].numTexture = nullptr;
            }
        }
    }
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(soundEffect);
    window = nullptr;
    renderer = nullptr;
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

SDL_Texture * loadString(const char * message, TTF_Font * font) {
    SDL_Color blackColor = { 0, 0, 0 };

    SDL_Texture *text = nullptr;

    SDL_Surface *surfaceMsg;

    surfaceMsg = TTF_RenderText_Solid(font, message, blackColor);
    if (surfaceMsg == nullptr) {
        cout << "Surface message could not be loaded! TTF Error: " << TTF_GetError();
    }
    else {
        text = SDL_CreateTextureFromSurface(renderer, surfaceMsg);
        if (text == nullptr) {
            cout << "Texture could not be created";
        }
        SDL_FreeSurface(surfaceMsg);
    }
    return text;
}

SDL_Texture * numToText(int num, TTF_Font * font) {
    char number[10];
    SDL_Texture * numtext = nullptr;
    if (sprintf(number, "%d", num) < 0) {
        cout << "Failed to change! ";
    }
    else {
        numtext = loadString(number, font);
        if (numtext == nullptr) {
            cout << "There were errors in numToText. Error:"<< SDL_GetError();
        }
    }
    return numtext;
}

SDL_Texture * loadTexture (const string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cout << "Unable to load img" << endl;
        playMore = false;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) cout << "Unable to create texture from " << path << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void initBoard(Grid board[][COLS], TTF_Font * font) {
    int i, j;
    int ran = randomNum();
    int boardVals[ROWS][COLS];
    loadNums(boardVals, randomGrid[ran]);
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                board[i][j].value = boardVals[i][j];
                board[i][j].recentlyFilled = false;
                board[i][j].isActive = false;
                board[i][j].isError = false;
                board[i][j].changed = false;
                if(board[i][j].value) {
                    board[i][j].isInitial = true;
                }
                else {
                    board[i][j].isInitial = false;
                }

                board[i][j].numTexture = numToText(board[i][j].value, font);

                board[i][j].square.x = SCREEN_WIDTH * j / 9 + 1;
                board[i][j].square.y = SCREEN_HEIGHT * i / 9 + 1;
                board[i][j].square.w = SCREEN_WIDTH / 9 - 1;
                board[i][j].square.h = SCREEN_HEIGHT / 9 - 1;
            }
        }
}



//render
void renderNums(Grid board[][COLS], TTF_Font * font) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].value) {
                if (board[i][j].changed) {
                    SDL_DestroyTexture(board[i][j].numTexture);

                    board[i][j].numTexture = numToText(board[i][j].value, font);

                    board[i][j].changed = false;
                }
                SDL_RenderCopy(renderer, board[i][j].numTexture, nullptr, &(board[i][j].square));
            }
        }
    }
}

void drawGrid() {
    int i;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (i = 0; i <= 9; i++) {
        if (i % 3 == 0 && i != 0 && i != 9) {
            SDL_RenderDrawLine(renderer, SCREEN_WIDTH * i / 9 - 1, 0, SCREEN_WIDTH * i / 9 - 1, SCREEN_HEIGHT);
            SDL_RenderDrawLine(renderer, SCREEN_WIDTH * i / 9 + 1, 0, SCREEN_WIDTH * i / 9 + 1, SCREEN_HEIGHT);
        }
        else if (i == 9) {
            SDL_RenderDrawLine(renderer, SCREEN_WIDTH * i / 9 - 1, 0, SCREEN_WIDTH * i / 9 - 1, SCREEN_HEIGHT);
        }
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH * i / 9, 0, SCREEN_WIDTH * i / 9, SCREEN_HEIGHT);
    }

    for (i = 0; i <= 9; i++) {
        if (i % 3 == 0 && i != 0 && i != 9) {
            SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT * i / 9 - 1, SCREEN_WIDTH, SCREEN_HEIGHT * i / 9 - 1);
            SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT * i / 9 + 1, SCREEN_WIDTH, SCREEN_HEIGHT * i / 9 + 1);
        }
        else if (i == 9) {
            SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT * i / 9 - 1, SCREEN_WIDTH, SCREEN_HEIGHT * i / 9 - 1);
        }
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT * i / 9, SCREEN_WIDTH, SCREEN_HEIGHT * i / 9);
    }
}

void renderColors(Grid board[][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j].isActive) {
                if (board[i][j].isError) {
                    SDL_SetRenderDrawColor(renderer, 237, 87, 87, 255);
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 0, 191, 255, 1);
                }
                SDL_RenderFillRect(renderer, &(board[i][j].square));
            }
            else if (board[i][j].isError) {
                SDL_SetRenderDrawColor(renderer, 237, 87, 87, 255);
                SDL_RenderFillRect(renderer, &(board[i][j].square));
            }
            else if (board[i][j].isError && !board[i][j].recentlyFilled) {
                SDL_SetRenderDrawColor(renderer, 237, 87, 87, 255);
                SDL_RenderFillRect(renderer, &(board[i][j].square));
            }
            else if (board[i][j].isHalfActive && !board[i][j].recentlyFilled) {
                SDL_SetRenderDrawColor(renderer, 211, 211, 211, 1);
                SDL_RenderFillRect(renderer, &(board[i][j].square));
            }
            else if (board[i][j].recentlyFilled) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 1);
                SDL_RenderFillRect(renderer, &(board[i][j].square));
            }
        }
    }
}




