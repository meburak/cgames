#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>

int kbhit(){ //NON-BLOCK INPUT
    //RETURN 1 IF THERE IS ANY CHANGES IN BUFFER
    struct termios oldt, newt;
    int ch;
    int oldf;

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0); //take 0 something value in GETFLN,
    //guess it is for "block stuff"
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); //set that to NONBLOCK

    ch = getchar(); //get the char

    fcntl(STDIN_FILENO, F_SETFL, oldf); //return old settings

    if (ch != EOF){
        ungetc(ch, stdin); //put char into stdin
        return 1;
    }
    return 0;
}


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
        direction = getchar();
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
        usleep(100000);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); //GAME OFF
    return 0;
}


