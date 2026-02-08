#include <stdio.h>
#include <unistd.h>

int main(){
    int frame = 0;
    int headX = 0;
    int headY = 0;
    char direction = 'D'; //D RIGHT MAX 10 MIN 0 COLUMNS J +
                          //A LEFT MAX 0 MIN 10 COLUMNS J -
                          //W UP MAX 0 MIN 10 ROWS I +
                          //S DOWN MIN 0 MAX 10 ROWS I -
    while(frame <101){
        //FRAME START
        //USER INPUT FOR DIRECTION
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

        printf("FRAME: %d\n", frame);
        frame++;
    }

    return 0;
}
