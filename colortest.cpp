#include <stdio.h>
#include <stdlib.h>

int main(){
    int count = 111;
    system("clear");
    for (int i = 0; i < count; i++) {
        printf("\033[%dm%d \033[0m", i, i);
        //printf("%c[5;%dm%d %c[0m", 27, i, i, 27);
        if (i%10 == 0){
            printf("\n");
        }
    }
}
