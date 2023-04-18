#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
struct process{
	int process_id;
	int arrival_time;
	int execution_time;
	int start_time;
};

void init_processes(struct process *);
void display(struct process *);
void display_average_waiting_time(struct process *);
void schedule_FCFS(struct process *);
void schedule_SJF(struct process *);
void schedule_LJF(struct process *);

//Compare based on arrival time for FCFS. 
int cmpr (const void * a, const void * b){
    return ((struct process*)a)->arrival_time - ((struct process *)b)->arrival_time;
}
//Compare based on execution time for SJF. 
int cmpr_SJF(const void * a, const void *b){
    return ((struct process*)a)->execution_time - ((struct process*)b)->execution_time;
}
//like cmpr_SJF but inverse, since now we want the longer exec time to be first
int cmpr_LJF(const void * a, const void *b){
    return  -1*(((struct process*)a)->execution_time - ((struct process*)b)->execution_time);
}
int main()
{
	struct process processes[SIZE];	
	init_processes(processes);

	printf("Orignial input (processes)\n");
	display(processes);
	
	schedule_FCFS(processes);
	printf("Execution according to FCFS policy\n");
	display(processes);
	display_average_waiting_time(processes);

        //for SJF
        schedule_SJF(processes);
        printf("Execution according to SJF policy\n");
        display(processes);
        display_average_waiting_time(processes);

        //for LJF
        schedule_LJF(processes);
        printf("Execution according to LJF policy\n");
        display(processes);
        display_average_waiting_time(processes);

}
void init_processes(struct process * input)
{
	srand(100);
	for(int i=0;i<SIZE;i++)
	{
		input[i].arrival_time = rand()%10;
		input[i].execution_time = rand()%10;
		input[i].process_id= i;
		input[i].start_time=-1;      
	}	
}
void display(struct process * input){
	printf("process<id, arr, exe, start>:");
	for(int i=0;i<SIZE;i++)
	{
		printf("<%d,%d,%d,%d> ",  input[i].process_id,
		 input[i].arrival_time,  input[i].execution_time, input[i].start_time);	
	}
	printf("\n");
}

void schedule_FCFS(struct process * arr)
{
        //Sort array according to policy
	qsort(arr, SIZE, sizeof(struct process), cmpr);
        int i;
        int diff;
        int arrival;
        // process arr[0] starts when it arrives. Allways at time 0 in this case.
        arr[0].start_time = arr[0].arrival_time;
        // loop over arr calculating the respective start times
        for (i = 1; i < SIZE; i++) {
            /*We assume a process cannot start the same time an other end, hence +1. 
             * diff is the earliest possible start time. 
             * If process arrives after it will start when it arrives. 
             * (Note: arrival and start are atomic in this implementation i.e. can happen at the same time. */
           diff = arr[i-1].start_time + arr[i-1].execution_time + 1;
           arrival = arr[i].arrival_time;
           //cannot start before arrival
           arr[i].start_time = diff>arrival?diff:arrival;
        }
	printf("Implemented!\n");
}

/* each scheduler just uses theri respective cmpr function which essentially dictates the scheduling. 
 * Otherwise the considerations are like for FCFS, so we don't comment them to avoid redundancy */
void schedule_SJF(struct process * arr)
{

	qsort(arr, SIZE, sizeof(struct process), cmpr_SJF);
        int i;
        int diff;
        int arrival;
        arr[0].start_time = arr[0].arrival_time;
        for (i = 1; i < SIZE; i++) {
           diff = arr[i-1].start_time + arr[i-1].execution_time + 1;
           arrival = arr[i].arrival_time;
           arr[i].start_time = diff>arrival?diff:arrival;
        }
	printf("Implemented!\n");
}
void schedule_LJF(struct process * arr)
{
        //TODO


	qsort(arr, SIZE, sizeof(struct process), cmpr_LJF);
        int i;
        int diff;
        int arrival;
        arr[0].start_time = arr[0].arrival_time;
        for (i = 1; i < SIZE; i++) {
           diff = arr[i-1].start_time + arr[i-1].execution_time + 1;
           arrival = arr[i].arrival_time;
           arr[i].start_time = diff>arrival?diff:arrival;
        }
	printf("Implemented!\n");
}
void display_average_waiting_time(struct process * arr)
{
	//TODO
        int total = 0;
        int i;
        for (i = 0; i < SIZE; i++) {
            //Start time must be >= arrival time. so we dont take abs value
               total += arr[i].start_time - arr[i].arrival_time;
              // printf("Current total: %d. Start: %d. Arrival %d\n", total, arr[i].start_time, arr[i].arrival_time);
        }
        float avrg;
        avrg = (float)total/(float)SIZE;
	printf("Average waiting time: %.3f\n",avrg);
}
