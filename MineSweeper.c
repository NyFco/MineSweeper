#include <stdio.h>
#include <stdlib.h>
#include <time.h>0

char blocks[11][11] = {{'!','!','!','!','!','!','!','!','!','!'},{'!','#','#','#','#','#','#','#','#','#'},{'!','#','#','#','#','#','#','#','#','#'},{'!','#','#','#','#','#','#','#','#','#'},{'!','#','#','#','#','#','#','#','#','#'},{'!','#','#','#','#','#','#','#','#','#'},{'!','#','#','#','#','#','#','#','#','#'},{'!','#','#','#','#','#','#','#','#','#'},{'!','#','#','#','#','#','#','#','#','#'},{'!','#','#','#','#','#','#','#','#','#'}};
char mines[11][11];
// '!' is just for starting the number of blocks from 1, '#' for unknown , '*' for mines , 'numbers' for counting the near mines , ' ' for blank blocks

void screen(int winCheck){
    system("cls");

    int i;
    int j;

    if(winCheck != -1){
        if(winCheck == 0){
            system("color CF");
            printf("\n                       You lost!\n\n");
        }
        else{
            system("color 2F");
            printf("\n                       You won!\n\n");
        }
        printf("Y\\X___[1]___[2]___[3]___[4]___[5]___[6]___[7]___[8]___[9]______\n");
        for(i=1;i<=9;i++){
            printf("[%d]:|",i);
            for(j=1;j<=9;j++){
                if(mines[j][i] == '*' && winCheck == -1) printf("__#__|");
                else printf("__%c__|",mines[j][i]);
            }
            printf(":[%d]",i);
            puts("");
        }
        printf("Y\\X___[1]___[2]___[3]___[4]___[5]___[6]___[7]___[8]___[9]______\n");
        printf("-----------------------------------------------------------\n");
    }

    else{
        printf("Y\\X___[1]___[2]___[3]___[4]___[5]___[6]___[7]___[8]___[9]______\n");
        for(i=1;i<=9;i++){
            printf("[%d]:|",i);
            for(j=1;j<=9;j++){
                if(blocks[j][i] == '*' && winCheck == -1) printf("__#__|");
                else printf("__%c__|",blocks[j][i]);
            }
            printf(":[%d]",i);
            puts("");
        }
        printf("Y\\X___[1]___[2]___[3]___[4]___[5]___[6]___[7]___[8]___[9]______\n");
        printf("-----------------------------------------------------------\n");
    }

}

void mineField(void){
    int i;
    int j;
    int x;
    int y;
    int nearMines=0;

    for(i=1;i<=10;i++){
        j=0; // this is just for checking if the generated mine block is repeated or not
        while (j==0){
            x = (rand()%9)+1;
            y = (rand()%9)+1;
            if (blocks[x][y] != '*' ){
                blocks[x][y] = '*';
                j++;
            }
        }
    }

    for(j=1;j<=9;j++){
        for(i=1;i<=9;i++){
            if(blocks[i][j] == '*'){
                mines[i][j] = '*';
                continue;
            }
            if(blocks[i-1][j-1] == '*') nearMines++;
            if(blocks[i-1][j] == '*') nearMines++;
            if(blocks[i-1][j+1] == '*') nearMines++;
            if(blocks[i][j-1] == '*') nearMines++;
            if(blocks[i][j+1] == '*') nearMines++;
            if(blocks[i+1][j-1] == '*') nearMines++;
            if(blocks[i+1][j] == '*') nearMines++;
            if(blocks[i+1][j+1] == '*') nearMines++;
            mines[i][j] = nearMines + 48;
            if(nearMines==0) mines[i][j]=' ';
            nearMines=0;
        }
    }

}

int checker(int x, int y){
    if(x < 1 || y < 1 || x > 9 || y > 9) return -1;

    if(mines[x][y] == '*') return 0;
    else if(mines[x][y] == ' '){
        if(blocks[x][y] == ' ') return -1;
        blocks[x][y] = ' ';
        checker(x,y-1);
        checker(x-1,y);
        checker(x+1,y);
        checker(x,y+1);
        return -1;
    }
    else{
        blocks[x][y] = mines[x][y];
        return -1;
    }
}

int stepCounter(void){

    int i;
    int j;
    int counter=0;

    for(j=1;j<=9;j++){
        for(i=1;i<=9;i++){
           if(blocks[i][j] == '#') counter++;
        }
    }
    if(counter == 10) return 1;
    else return -1;
}

int main()
{
    system("color FC");
    srand(time(0));

    int x;
    int y;
    int finish = -1; // -1 == not finished / 0 == lost / 1 == won
    int repeated = 0;

    screen(finish);

    printf("Please enter the position of your block\nX:");
    while(repeated==0){
        scanf("%d",&x);
        repeated++;
        if(x>9 || x<1){
            printf("The entered number is invalid! Please enter a valid number.(1-9)\nX:");
            repeated--;
        }
    }
    printf("Y:");
    repeated = 0;
    while(repeated==0){
        scanf("%d",&y);
        repeated++;
        if(y>9 || y<1){
            printf("The entered number is invalid! Please enter a valid number.(1-9)\nY:");
            repeated--;
        }
    }

    mineField();
    finish = checker(x,y); // Error for ' '
    screen(finish);

    while(finish == -1){
        repeated = 0;
        printf("Please enter the position of your block\nX:");
        while(repeated==0){
            scanf("%d",&x);
            repeated++;
            if(x>9 || x<1){
                printf("The entered number is invalid! Please enter a valid number.(1-9)\nX:");
                repeated--;
            }
        }
        printf("Y:");
        repeated = 0;
        while(repeated==0){
            scanf("%d",&y);
            repeated++;
            if(y>9 || y<1){
                printf("The entered number is invalid! Please enter a valid number.(1-9)\nY:");
                repeated--;
            }
        }

        if(checker(x,y) == -1 && stepCounter() == -1) finish = -1;
        else if(checker(x,y) == 0) finish = 0;
        else finish = 1;

        screen(finish);

    }

    return 0;
}
