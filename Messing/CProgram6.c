#include <stdio.h>
#include <time.h>

void func_name(){
    printf("Function starts\n");
    printf("Press Return to stop function\n");

    //syntax for for loop forever, diff of just while true???
    for(;;){
        if(getchar()){
            break;
        }
    }

    printf("Function ends\n");
}

int main(int argc, char **argv){
    clock_t t;
    t = clock();
    func_name();
    t = clock() - t; //subtract starting time from current time

    double time_taken_by_func = ((double) t) / CLOCKS_PER_SEC;
    //doesn't end up being the real time that it took before you pressed a key, processor time instead
    printf("The processing time of function is: %f\n", time_taken_by_func);
}