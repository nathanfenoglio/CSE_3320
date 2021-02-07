#include <stdio.h>
#include <limits.h>

int main(int argc, char **argv){
    printf("LONG_MIN: %ld\n", LONG_MIN);
    printf("LONG_MAX: %ld\n", LONG_MAX);
    printf("CHAR_MIN: %d\n", CHAR_MIN);
    printf("CHAR_MAX: %d\n", CHAR_MAX);
    printf("CHAR_BIT: %d\n", CHAR_BIT);

    return 0;
}