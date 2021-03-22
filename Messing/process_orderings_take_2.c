#include <stdio.h>
#include <stdlib.h>

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

void insertionSortIndirect(struct p_info *proc_arr[], int arr_indirect[], int n){
    int i, key, j;

    //set up arr_indirect with values of index in order 0, 1, 2, 3, ..., n-1
    for(i = 0; i < n; i++){
        arr_indirect[i] = i;
    }

    for(i = 1; i < n; i++){
        key = proc_arr[i]->arrival; //key is holder to hold considered index value outside of the array
        j = i - 1; //j will be the index just below the considered index

        while(j >=0 && proc_arr[arr_indirect[j]]->arrival > key){
            arr_indirect[j + 1] = arr_indirect[j];
            j = j - 1;
        }

        arr_indirect[j + 1] = i;
    }
}

void fifo_process_calculations(struct p_info *proc_arr[], int fifo_queue[], int n, float *avg_turnaround_time, float *avg_response_time){
    //calculate the start times and finish times 
    //if you were trying to do something other than FIFO non-preemptive
    int time_marker = 0;
    int i;
    for(i = 0; i < n; i++){
        proc_arr[fifo_queue[i]]->start = time_marker;
        time_marker = time_marker + proc_arr[fifo_queue[i]]->duration;
        proc_arr[fifo_queue[i]]->finish = time_marker; //only accurate if FIFO
    }

    //calculate the turnaround times
    for(i = 0; i < n; i++){
        proc_arr[i]->turnaround_time = proc_arr[i]->finish - proc_arr[i]->arrival;
    }

    //calculate the response times
    for(i = 0; i < n; i++){
        proc_arr[i]->response_time = proc_arr[i]->start - proc_arr[i]->arrival;
    }

    //calculate the average turnaround time
    float sum = 0;
    for(i = 0; i < n; i++){
        sum = sum + proc_arr[i]->turnaround_time;
        
    }
    printf("sum: %f\n", sum);
    (*avg_turnaround_time) = sum / n;

    //calculate the average response time
    sum = 0;
    for(i = 0; i < n; i++){
        sum = sum + proc_arr[i]->response_time;
    }
    printf("sum: %f\n", sum);
    (*avg_response_time) = sum / n;

}

int main(int argc, char **argv){
    int num_processes = 4;
    struct p_info **proc_info_arr = (struct p_info **)malloc(num_processes * sizeof(struct p_info *));  

    int i;
    for(i = 0; i < num_processes; i++){
        proc_info_arr[i] = (struct p_info *)malloc(sizeof(struct p_info));
    }

    proc_info_arr[0]->duration = 8;
    proc_info_arr[1]->duration = 4;
    proc_info_arr[2]->duration = 9;
    proc_info_arr[3]->duration = 5;

    proc_info_arr[0]->arrival = 0;
    proc_info_arr[1]->arrival = 1;
    proc_info_arr[2]->arrival = 2;
    proc_info_arr[3]->arrival = 3;

    //just printing
    for(i = 0; i < num_processes; i++){
        printf("proc_info_arr[%d]->duration: %d\n", i, proc_info_arr[i]->duration);
        printf("proc_info_arr[%d]->arrival: %d\n", i, proc_info_arr[i]->arrival);
    }

    //arr for order in which the processes arrived in order
    int *fifo_queue = (int *)malloc(num_processes * sizeof(int));

    insertionSortIndirect(proc_info_arr, fifo_queue, num_processes);

    //just printing
    for(i = 0; i < num_processes; i++){
        printf("fifo_queue[%d]: %d, ", i, fifo_queue[i]);
    }
    printf("\n");

    float avg_turnaround_time = -1;
    float avg_response_time = -1;
    fifo_process_calculations(proc_info_arr, fifo_queue, num_processes, &avg_turnaround_time, &avg_response_time);
    printf("avg_turnaround_time: %f\n", avg_turnaround_time);
    printf("avg_response_time: %f\n\n", avg_response_time);
    free(fifo_queue);

    //free memory
    for(i = 0; i < num_processes; i++){
        free(proc_info_arr[i]);
    }
    free(proc_info_arr);
}