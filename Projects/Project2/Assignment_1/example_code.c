/*
The following is a sequential solution of the problem. read_f() reads the two strings from a file named
“string.txt and num_substring() calculates the number of substrings.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1024

int total = 0;
int n1, n2;
char *s1, *s2;
FILE *fp;

int readf(FILE *fp){
    if((fp = fopen("strings.txt", "r")) == NULL){
        printf("ERROR: can't open string.txt!\n");
        return 0;
    }

    s1 = (char *)malloc(MAX * sizeof(char));
    if(s1 == NULL){
        printf("ERROR: Out of memory!\n");
        return -1;
    }

    s2 = (char *)malloc(MAX * sizeof(char));
    if(s2 == NULL){
        printf("ERROR: Out of memory\n");
        return -1;
    }

    //read s1 s2 from the file
    s1 = fgets(s1, MAX, fp);
    s2 = fgets(s2, MAX, fp);

    //need to subtract 2 to ditch \r\n characters
    n1 = strlen(s1) - 2; //length of string 1
    n2 = strlen(s2) - 2; //length of string 2

    //check if either string is NULL or if the string that we are searching is smaller than the string that we are trying to match
    if(s1 == NULL || s2 == NULL || n1 < n2){
        return -1;
    }
}

int num_substring(void){
    int i, j, k;
    int count;

    for(i = 0; i <= (n1 - n2); i++){
        count = 0;
        for(j = i, k = 0; k < n2; j++, k++){ //search for the next string of size of n2
            if(*(s1 + j) != *(s2 + k)){
                break;
            }
            else{
                count++;
            }

            //THIS IS WHERE YOU WOULD NEED TO USE MUTEX TO PROTECT THE GLOBAL total VARIABLE
            if(count == n2){
                total++; 
            }
        }
    }

    return total;
}

int main(int argc, char **argv){
    int count;
    readf(fp);
    count = num_substring();
    printf("The number of substrings is: %d\n", count);
    return 1;
}
