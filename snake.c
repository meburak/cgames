#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

int main(){
    int frame = 0;
    int headX = 0;
    int headY = 0;
    char direction = 'D'; //D LEFT MAX 10 MIN 0 COLUMNS J +
                          //A RIGHT MAX 0 MIN 10 COLUMNS J -
                          //W UP MAX 0 MIN 10 ROWS I +
                          //S DOWN MIN 0 MAX 10 ROWS I -

    struct termios oldattr, newattr; //OLD TERMINAL SETTINGS (GAME OFF) NEW SETTINGS (GAME ON)
                                     //HIDE KEYBOARD OUTPUT WHEN GAME IS ON
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); //GAME ON

    while(frame <101){

        system("clear");
        printf("FRAME: %d\n", frame);
        //FRAME START

        //USER INPUT FOR DIRECTION
        direction = keyhit();
        switch(direction){
            case 'D': //RIGHT
                if (headX == 9){
                    headX = 0;
                    break;
                } else {
                    headX++;
                    break;
                }
            case 'A': //LEFT
                if (headX == 0){
                    headX = 9;
                    break;
                } else {
                    headX--;
                    break;
                }
            case 'W': //UP
                if (headY == 0){
                    headY = 9;
                    break;
                } else {
                    headY--;
                    break;
                }
            case 'S': //DOWN
                if (headY == 9){
                    headY = 0;
                    break;
                } else {
                    headY++;
                    break;
                }
        }
        //TILE CREATION
        for (int i = 0; i <10; i++){ //I
            for (int j = 0; j<10; j++){ //J
                if (i == headY && j == headX){ //PUT "H" ON
                    printf("H "); //TILES THAT MATCH COORDINATES headX, headY
                } else {
                    printf("O ");
                }
            }
            printf("\n");
        }
        frame++;
        sleep(1);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); //GAME OFF
    return 0;
}
/*
int keyhit(){
    struct termios oldattr, newattr; //define strucutre
    int ch = '0'; //define character
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
*/

