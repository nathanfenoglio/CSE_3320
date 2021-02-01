//https://www.youtube.com/watch?v=6OSeJFo6GOc
//I get a seg fault but he doesn't...
#include <stdio.h>
#include <stdlib.h>

struct threeNumb{
    int num1, num2, num3;
};

int main(int argc, char **argv){
    int num;
    struct threeNumb number;
    FILE *fptr;

    if((fptr = fopen("program.bin", "rb")) == NULL){
        printf("ERROR OPENING FILE!\n");
        exit(1);
    }

    for(num = 1; num < 5; num++){
        fread(&num, sizeof(struct threeNumb), 1, fptr);
        printf("n1: %d\tn2: %d\tn3: %d", number.num1, number.num2, number.num3);
    }

    fclose(fptr);

}