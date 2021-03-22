#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int n, int print_vertical){
    int i;
    int print_another_array = 1;
    int another_arr_to_always_print[] = {8, 4, 9, 5};

    if(print_vertical){
        if(print_another_array){
            for(i = 0; i < n; i++){
                printf("%d\n", another_arr_to_always_print[i]);
            }
            printf("\n");
        }
        for(i = 0; i < n; i++){
            printf("%d\n", arr[i]);
        }
        printf("\n");
    }
    else{
        for(i = 0; i < n; i++){
            printf("%d, ", arr[i]);
        }
        printf("\n");
    }
}

//recursive solution from https://www.codesdope.com/blog/article/generating-permutations-of-all-elements-of-an-arra/
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void print_all_permutations(int *arr, int start, int end){
    //stopping condition
    if(start == end){
        print_arr(arr, end + 1, 1);
        return;
    }

    int i;
    for(i = start; i <= end; i++){
        swap(&arr[i], &arr[start]);

        //fixing one first digit and calling print_all_permutations on the rest
        print_all_permutations(arr, start + 1, end);

        swap(&arr[i], &arr[start]);
    }
}

int fact(int num){
    if(num == 1){
        return 1;
    }
    return num * fact(num - 1);
}
int main(int argc, char **argv){
    //take input from command line args (format: number_elements, then all of the elements separated by a space)
    
    int suppress_chatter = 1;
    int num_elements = -1;
    if(!suppress_chatter){
        printf("num_elements: \n");
    }
    scanf("%d", &num_elements);

    //also include printing the number of elements for output file, then the # of different permutations
    printf("%d\n", num_elements);
    printf("%d\n\n", fact(num_elements));

    int *arr_1 = (int *)malloc(num_elements * sizeof(int));

    int i;
    for(i = 0; i < num_elements; i++){
        if(!suppress_chatter){
            printf("Enter Element (int): \n");
        }
        scanf("%d", &arr_1[i]);
    }

    //just printing
    //print_arr(arr_1, num_elements, 0);

    print_all_permutations(arr_1, 0, num_elements - 1);
    free(arr_1);

}