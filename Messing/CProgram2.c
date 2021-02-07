#include <stdio.h>
#include <stdlib.h>

struct threeNumb{
    int num1, num2, num3;
};

int main(int argc, char **argv){
    int num;
    struct threeNumb number;
    FILE *fptr;

    if((fptr = fopen("program.bin", "wb")) == NULL){
        printf("ERROR OPENING FILE!\n");
        exit(1);
    }

    for(num = 1; num < 5; num++){
        number.num1 = num;
        number.num2 = 2 * num;
        number.num3 = 2*num + 3;
        fwrite(&num, sizeof(struct threeNumb), 1, fptr);

    }

    fclose(fptr);

}