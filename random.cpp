//
// Created by hbduwu on 18-May-22.
//
#include "game.h"
const string randomGrid[] = {
        //0
        "4 0 0 9 0 8 0 0 6"
        "1 5 0 0 0 0 7 9 0"
        "3 0 0 7 0 0 0 0 0"
        "5 0 1 0 9 0 0 0 0"
        "0 3 0 0 0 0 0 0 0"
        "0 0 0 3 0 0 0 1 0"
        "0 1 0 5 0 0 4 0 0"
        "0 0 4 2 0 0 0 0 0"
        "2 9 0 0 0 0 0 0 7",
//1
        "0 0 0 0 0 6 5 0 0"
        "0 9 0 0 0 0 0 6 3"
        "0 0 0 0 9 0 8 0 4"
        "0 0 3 4 0 0 2 0 0"
        "6 0 0 0 3 0 0 0 0"
        "0 5 0 0 0 1 0 0 0"
        "0 0 0 0 0 0 0 0 2"
        "0 0 0 0 1 2 6 0 0"
        "0 4 0 0 0 0 0 0 0",
//2
        "5 0 8 0 0 0 0 0 0"
        "0 0 0 5 0 0 0 0 0"
        "0 7 0 0 0 0 5 3 0"
        "0 8 0 1 0 0 2 0 0"
        "0 9 0 8 0 0 0 4 0"
        "1 0 0 9 4 6 0 0 3"
        "0 0 0 0 0 5 0 0 8"
        "7 0 9 0 8 0 0 0 0"
        "8 0 0 6 9 0 0 0 0",
//3
        "7 0 6 0 0 0 0 3 0"
        "0 0 0 0 9 0 0 0 0"
        "3 0 5 1 0 4 2 9 0"
        "0 0 9 0 0 7 5 0 8"
        "0 0 1 9 6 2 4 0 0"
        "4 0 7 5 0 0 9 0 0"
        "0 1 8 6 0 3 7 0 9"
        "0 0 0 0 4 0 0 0 0"
        "0 2 0 0 0 0 3 0 5",
//4
        "0 0 0 0 6 0 2 0 0"
        "0 0 0 0 0 0 0 0 0"
        "0 3 0 0 1 0 6 9 0"
        "0 0 7 5 0 0 0 0 0"
        "0 0 0 0 0 0 0 0 9"
        "5 0 0 9 0 0 3 0 0"
        "0 0 3 0 5 0 0 0 2"
        "0 0 0 3 0 9 0 0 7"
        "0 0 8 1 2 0 9 0 0",
//5
        "0 0 0 0 8 3 2 0 0"
        "3 0 0 2 0 0 9 5 0"
        "0 8 0 0 9 5 0 1 0"
        "0 0 0 0 0 8 0 0 0"
        "0 0 0 0 2 0 0 0 4"
        "4 0 0 6 0 0 0 3 0"
        "1 0 5 8 3 0 0 0 0"
        "7 9 6 5 1 0 0 0 0"
        "8 4 3 0 0 0 0 2 0",
//6
        "4 0 6 0 5 0 0 0 2"
        "0 1 0 4 0 2 0 0 5"
        "0 0 0 0 0 0 0 0 0"
        "0 0 9 0 0 8 7 1 0"
        "8 0 7 9 1 0 3 2 4"
        "0 0 0 0 2 4 0 0 9"
        "3 9 5 0 0 0 0 4 0"
        "7 0 0 1 0 9 0 5 3"
        "0 0 0 3 0 0 2 0 7\n",
//7
        "4 6 0 0 0 1 5 0 8"
        "0 1 0 0 5 8 4 0 6"
        "8 0 5 0 0 0 2 0 0"
        "1 0 9 0 0 0 7 0 0"
        "6 0 0 0 7 0 0 8 0"
        "0 2 0 0 0 0 0 4 0"
        "2 0 0 1 3 5 6 0 0"
        "3 0 0 0 0 6 0 5 0"
        "5 0 0 4 8 0 3 0 0",
//8
       "8 5 0 9 1 0 0 7 4"
       "4 6 2 8 0 7 0 3 9"
       "0 0 0 0 0 4 8 0 0"
       "6 2 7 1 0 3 0 4 8"
       "0 8 0 0 0 0 9 0 0"
       "3 4 9 2 8 5 0 1 0"
       "2 0 0 0 3 0 0 0 7"
       "0 9 4 6 0 1 0 0 0 "
       "0 0 6 7 4 0 2 0 0"
       ,
//9
        "0 0 1 5 0 0 0 0 0"
        "0 3 8 0 1 0 0 0 0"
        "6 5 4 2 9 3 1 0 8"
        "3 1 7 8 6 5 4 0 0"
        "0 0 9 0 2 0 0 0 6"
        "0 6 0 0 0 0 5 0 0"
        "0 0 0 1 0 2 0 5 0"
        "0 0 0 0 0 8 7 6 1"
        "0 7 0 0 0 9 2 0 0",
//10
        "3 2 9 7 6 5 4 8 1\n"
        "1 7 8 3 9 4 6 2 5\n"
        "4 6 5 2 8 1 3 9 7\n"
        "9 5 1 6 4 2 8 7 3\n"
        "7 4 6 5 1 3 9 6 2\n"
        "6 3 2 8 7 9 5 1 4\n"
        "5 1 6 4 2 8 0 3 9\n"
        "7 9 4 1 3 6 0 5 8\n"
        "2 8 3 9 5 7 0 0 0",
        //11
        "0 9 0 0 6 5 1 0 0 \n"
        "1 8 5 0 7 9 0 0 0 \n"
        "7 6 3 0 2 8 0 5 4\n"
        "3 4 7 0 9 1 2 0 0\n"
        "9 2 0 0 4 0 0 0 5\n"
        "0 1 0 2 3 6 0 0 0 \n"
        "0 0 0 0 0 0 7 4 0\n"
        "4 7 0 0 5 2 0 3 1\n"
        "0 0 2 0 0 0 5 0 0 ",
        //12
        "5 0 2 3 0 0 0 0 0 \n"
        "1 6 4 0 2 7 9 3 0\n"
        "6 9 5 2 0 3 0 8 0\n"
        "2 0 0 9 0 5 1 0 0 \n"
        "3 4 1 0 7 0 0 0 0 \n"
        "0 0 0 0 0 9 0 7 0\n"
        "7 0 3 4 8 1 5 9 6 \n"
        "9 5 0 7 3 0 0 4 1",
        //13
        "6 7 9 4 1 8 0 0 0 \n"
        "0 0 2 5 3 0 9 1 0\n"
        "1 3 0 2 6 9 4 8 7\n"
        "0 8 7 0 0 0 0 0 0 \n"
        "0 0 4 0 8 0 0 0 0 \n"
        "0 6 1 9 0 0 0 7 2\n"
        "7 0 0 8 9 0 1 6 0\n"
        "0 1 0 0 0 0 0 0 8\n"
        "0 0 0 0 0 0 0 0 3",
        //14
        "5 8 3 1 9 4 0 2 0 \n"
        "2 7 1 3 0 6 0 5 4 \n"
        "9 0 0 7 0 0 3 1 8\n"
        "7 0 0 4 0 3 0 0 5\n"
        "3 5 9 0 0 0 4 6 0\n"
        "0 6 0 9 1 0 0 3 0\n"
        "8 0 0 6 0 9 1 7 2\n"
        "0 9 0 0 2 7 5 0 0 \n"
        "4 0 0 0 3 0 0 8 9",
        //15
        "6 0 4 0 0 5 9 0 0\n"
        "5 9 0 0 8 2 6 4 7\n"
        "0 1 2 9 0 0 3 0 8\n"
        "2 0 9 8 5 0 1 3 0\n"
        "0 4 0 0 0 0 7 0 0 \n"
        "0 6 5 0 9 0 2 8 0\n"
        "9 2 0 0 0 0 5 6 0\n"
        "4 0 6 5 0 0 0 7 0\n"
        "8 0 1 0 0 0 0 0 9",
};