#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>

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


int main(){
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

    int pointX = 39; //THE POINT COORDINATES
    int pointY = 39;

    int playerPoint = 0;

    struct termios oldattr, newattr; //OLD TERMINAL SETTINGS (GAME OFF) NEW SETTINGS (GAME ON)
                                     //HIDE KEYBOARD OUTPUT WHEN GAME IS ON
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); //GAME ON

    while(frame <1000){
        kbstatus = kbhit();
        system("clear");

        if(kbstatus == 1){ //RUN DETECTION ALGORITHM (switch) IF kbhit returns 1
            direction = getchar();
        }

        switch(direction){
            case 'D': //RIGHT
                headIcon = headRight;
                if (headX == 39){
                    headX = 0;
                    break;
                } else {
                    headX++;
                    break;
                }
            case 'A': //LEFT
                headIcon = headLeft;
                if (headX == 0){
                    headX = 39;
                    break;
                } else {
                    headX--;
                    break;
                }
            case 'W': //UP
                headIcon = headUp;
                if (headY == 0){
                    headY = 39;
                    break;
                } else {
                    headY--;
                    break;
                }
            case 'S': //DOWN
                headIcon = headDown;
                if (headY == 39){
                    headY = 0;
                    break;
                } else {
                    headY++;
                    break;
                }
        }
            // //Flush();
        //TILE CREATION
        for (int i = 0; i <40; i++){ //I
            for (int j = 0; j<40; j++){ //J
                if (i == headY && j == headX && i == pointY && j == pointX){
                    printf("1 ");
                    playerPoint++;
                    pointY = rand() % 39;
                    pointX = rand() % 39;
                }
                else if (i == headY && j == headX){ //PUT "H" ON
                    printf("%c ", headIcon); //TILES THAT MATCH COORDINATES headX, headY
                }
                else if (i == pointY && j == pointX){
                    printf("@ ");
                }
                else {
                    printf(". ");
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


