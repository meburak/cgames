#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdbool.h>
#include "mygamelib.h"

int kbhit(void){
    struct timeval tv;
    fd_set read_fd;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&read_fd); //clear "bitmask" of read_fd
    FD_SET(0, &read_fd); //set 1, the 0th bit in read_fd

    if(select(1, &read_fd, NULL, NULL, &tv) == -1){
        return 0;
    }
    if(FD_ISSET(0, &read_fd)){
        return 1;
    }
    else{
        return 0;
    }
}

void Flush(void){
    while( getchar() != '\n' );
}

void printHUD(char playerName[], int playerHP, int playerPoint){
    tc_move_cursor(2,0);
    printf("PLAYER %s", playerName);
    tc_move_cursor(2, 3);
    printf("HEALTH %d", playerHP);
    tc_move_cursor(40, 3);
    printf("POINTS %d", playerPoint);
    tc_move_cursor(0, 4);
    printf("=================================================");
    tc_move_cursor(0, 5);
}


void printEffects(char playerName[], int playerHP, int playerPoint){
    tc_move_cursor(2,0);
    printf("PLAYER %s", playerName);
    tc_move_cursor(2, 3);
    printf("HEALTH %d", playerHP);
    tc_move_cursor(40, 3);
    printf("POINTS %d", playerPoint);
    tc_move_cursor(0, 4);
    printf("=================================================");
    tc_move_cursor(0, 5);
}

int main(){
    int gridXSize = 25;
    int gridYSize = 25;

    int kbstatus = 0; //IF KBHIT RETURNS TRUE
    int frame = 0;
    int headX = 0;
    int headY = 0;
    char direction = 'D'; //D LEFT MAX 10 MIN 0 COLUMNS J +
                          //A RIGHT MAX 0 MIN 10 COLUMNS J -
                          //W UP MAX 0 MIN 10 ROWS I +
                          //S DOWN MIN 0 MAX 10 ROWS I -

    char headUp = '^'; //HEAD ICONS, ACCORDING TO LAST BUTTON PRESSED
    char headDown = 'V';
    char headRight = '>';
    char headLeft = '<';
    char headIcon = 'H';

    int pointX = gridXSize-1; //THE POINT COORDINATES
    int pointY = gridYSize-1;

    int playerPoint = 0; //PLAYER STATUS VARIABLES
    char playerName[] = "";
    int lastPointWin = 0;
    int playerHP = 10;
    char playerAction = 'H';
    bool pendingPlayerAction = false;
    bool statusChange = false; //DETECT STATUS CHANGE


    system("clear");
    tc_move_cursor(10,10); //NOTE FUNCTIONALIZE HERE
    printf("~~SNAKE HEAD~~\n");
    tc_move_cursor(10, 12);
    printf("cgames v3\n");
    tc_move_cursor(10, 14);
    printf("Enter player name to start: \n");
    tc_move_cursor(10,16);
    scanf("%s", playerName);



    struct termios oldattr, newattr; //OLD TERMINAL SETTINGS (GAME OFF) NEW SETTINGS (GAME ON)
                                     //HIDE KEYBOARD OUTPUT WHEN GAME IS ON
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); //GAME ON

    system("clear");
    printf("\033[H");

    printHUD(playerName, playerHP, playerPoint);

    while(playerHP > 0){
        kbstatus = kbhit();

        if(statusChange){
            //BEFORE FRAME CREATION CHECK IF THERE IS ANY CHANGES IN STATUS BAR
            //WE SET THIS WHEN THERE IS A CHANGE IN PREVIOUS FRAME, THIS WAY WE DO NOT NEED COMPARISON STATEMENTS
            //MAKING OUR GAME RUN FASTER
            printHUD(playerName, playerHP, playerPoint);
            statusChange = false;
        }

        if(kbstatus == 1){ //RUN DETECTION ALGORITHM (switch) IF kbhit returns 1
            char temp = 'O';
            temp = getchar();
            if (temp == 'H'){ //NOTE Implement
                playerAction = temp; // No one can press two keys at once, hopefully.
                pendingPlayerAction = true;
            } //NOTE Point HP Exchange
            else {
                direction = temp;
            }
        }

        if (pendingPlayerAction) {
            switch (playerAction){
                case 'H':
                    if (playerPoint > 4 && playerHP < 10){
                        playerPoint = playerPoint - 5;
                        playerHP++;
                        statusChange = true;
                        pendingPlayerAction = false;
                    }
                default: 
                    //do nothing 
            }
        }
        switch(direction){
            case 'D': //RIGHT
                headIcon = headRight;
                if (headX == (gridXSize-1)){
                    headX = 0;
                    playerHP--;
                    statusChange = true;
                    break;
                } else {
                    headX++;
                    break;
                }
            case 'A': //LEFT
                headIcon = headLeft;
                if (headX == 0){
                    headX = gridXSize-1;
                    playerHP--;
                    statusChange = true;
                    break;
                } else {
                    headX--;
                    break;
                }
            case 'W': //UP
                headIcon = headUp;
                if (headY == 0){
                    headY = (gridYSize-1);
                    playerHP--;
                    statusChange = true;
                    break;
                } else {
                    headY--;
                    break;
                }
            case 'S': //DOWN
                headIcon = headDown;
                if (headY == (gridYSize-1)){
                    headY = 0;
                    playerHP--;
                    statusChange = true;
                    break;
                } else {
                    headY++;
                    break;
                }
        }
            // //Flush();
        //TILE CREATION
        /*
        if (lastPointWin != 0){
            if (frame <= lastPointWin + 5){


            }
        }
        */

        tc_move_cursor(0,5); //DRAW FROM POINT
        for (int i = 0; i <gridYSize; i++){ //I
            for (int j = 0; j<gridXSize; j++){ //J
                if (i == headY && j == headX && i == pointY && j == pointX){ //POINT GAIN //TRACE ANIMATION?
                    printf("1 "); //POINT WON
                    playerPoint++;
                    pointY = rand() % (gridYSize-1);
                    pointX = rand() % (gridXSize-1);
                    lastPointWin = frame; //MECHANISM: FRAME, FRAME + 5 FRAMES, 5 BLOCK RADIUS GETS 1 ANIMATION, THEN 6 BLOCK RADIUS GETS 1 ANIMATION.
                    statusChange = true;
                }
                else if (i == headY && j == headX){ //PUT "H" ON
                    printf("%c ", headIcon); //TILES THAT MATCH COORDINATES headX, headY
                }
                else if (i == pointY && j == pointX){
                    printf("@ ");
                }
                else {
                    printf("_ ");
                }
            }
            printf("\n");
        }
        
        frame++;
        usleep(90000);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); //GAME OFF
    return 0;
}


