#include <stdio.h>
#include <stdlib.h>

#define NUM_PROCESSES 4

//struct to hold all of the relevant process info
struct p_info{
    int p_num;
    int duration; //(burst time)
    int arrival;
    int start;
    int finish; //you might just call this duration or no think you should include another field called duration
    int turnaround_time;
    int response_time;
};

void insertionSortIndirect(struct p_info proc_arr[], int arr_indirect[], int n){
    int i, key, j;

    //set up arr_indirect with values of index in order 0, 1, 2, 3, ..., n-1
    for(i = 0; i < n; i++){
        arr_indirect[i] = i;
    }

    for(i = 1; i < n; i++){
        key = proc_arr[i].arrival; //key is holder to hold considered index value outside of the array
        j = i - 1; //j will be the index just below the considered index

        while(j >=0 && proc_arr[arr_indirect[j]].arrival > key){
            arr_indirect[j + 1] = arr_indirect[j];
            j = j - 1;
        }

        arr_indirect[j + 1] = i;
    }
}

void fifo_process_calculations(struct p_info p_arr[]){
    //just printing
    printf("flam\n");
    int i;
    for(i = 0; i < NUM_PROCESSES; i++){
        printf("%d\n", p_arr[i].duration);
        //p_arr[i].duration = 666;
    }
}

int main(int argc, char **argv){
    //array of process info structs
    struct p_info proc_info_arr[NUM_PROCESSES];

    //should implement ability to read all of the processes info from csv file like you're using process_orderings
    int i;
    for(i = 0; i < NUM_PROCESSES; i++){
        proc_info_arr[i].p_num = i + 1;
    }

    proc_info_arr[0].duration = 8;
    proc_info_arr[1].duration = 4;
    proc_info_arr[2].duration = 9;
    proc_info_arr[3].duration = 5;

    proc_info_arr[0].arrival = 3;
    proc_info_arr[1].arrival = 2;
    proc_info_arr[2].arrival = 1;
    proc_info_arr[3].arrival = 0;

    //think that all of the rest of the struct info can be determined from the given above info
    //arr for order in which the processes arrived in order
    int fifo_queue[NUM_PROCESSES];
    //sort least to greatest, using insertion sort 
    //int num_sorted = 0;
    insertionSortIndirect(proc_info_arr, fifo_queue, NUM_PROCESSES);
    
    //just printing
    printf("\nfifo queue\n");
    for(i = 0; i < NUM_PROCESSES; i++){
        printf("%d, ", fifo_queue[i]);
    }
    printf("\n\n");

    //calculate the start times and finish times 
    //if you were trying to do something other than FIFO non-preemptive
    int time_marker = 0;
    for(i = 0; i < NUM_PROCESSES; i++){
        proc_info_arr[fifo_queue[i]].start = time_marker;
        time_marker = time_marker + proc_info_arr[fifo_queue[i]].duration;
        proc_info_arr[fifo_queue[i]].finish = time_marker; //only accurate if FIFO
    }

    //calculate the turnaround times
    for(i = 0; i < NUM_PROCESSES; i++){
        proc_info_arr[i].turnaround_time = proc_info_arr[i].finish - proc_info_arr[i].arrival;
    }

    //calculate the response times
    for(i = 0; i < NUM_PROCESSES; i++){
        proc_info_arr[i].response_time = proc_info_arr[i].start - proc_info_arr[i].arrival;
    }
    //calculate the average turnaround time
    float sum = 0;
    for(i = 0; i < NUM_PROCESSES; i++){
        sum = sum + proc_info_arr[i].turnaround_time;
        
    }
    printf("sum: %f\n", sum);
    float avg_turnaround_time = sum / NUM_PROCESSES;
    
    //calculate the average response time
    sum = 0;
    for(i = 0; i < NUM_PROCESSES; i++){
        sum = sum + proc_info_arr[i].response_time;
    }
    printf("sum: %f\n", sum);
    float avg_response_time = sum / NUM_PROCESSES;

    //just printing
    for(i = 0; i < NUM_PROCESSES; i++){
        printf("proc_info_arr[%d].p_num: %d\n", i, proc_info_arr[i].p_num);
        printf("proc_info_arr[%d].start: %d\n", i, proc_info_arr[i].start);
        printf("proc_info_arr[%d].finish: %d\n", i, proc_info_arr[i].finish);
        printf("proc_info_arr[%d].turnaround_time: %d\n", i, proc_info_arr[i].turnaround_time);
        printf("proc_info_arr[%d].response_time: %d\n\n", i, proc_info_arr[i].response_time);
    }
    
    printf("avg_turnaround_time: %f\n\n", avg_turnaround_time);
    printf("avg_response_time: %f\n\n", avg_response_time);

    fifo_process_calculations(proc_info_arr);
    printf("proc_info_arr[2]: %d\n", proc_info_arr[2]); //not changing the actual array info out here...
}