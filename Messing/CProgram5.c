#include <stdio.h>
#include <stdlib.h>

int main(){
    int *ptr;
    int num, sum = 0;

    num = 8;
    printf("We have %d elements to allocate memory to\n", num);

    //ptr = (cast-type*) malloc(byte-size)
    //ptr = (cast-type*) calloc(byte-size, element-size)
    //ptr = realloc(ptr, newSize)
    
    ptr = (int *) malloc(num * sizeof(int));

    if(ptr == NULL){
        printf("Memory allocation failed\n");
        exit(0);
    }
    else{
        printf("Memory allocation has been successful\n");
    }

    for(int i = 0; i < num; i++){
        ptr[i] = i + 1;
    }

    printf("Inserted 8 elements in the bloc are as follows:\n");

    for(int i = 0; i < num; i++){
        printf("%d, ", ptr[i]);
    }
    printf("\n");

    free(ptr);
}
