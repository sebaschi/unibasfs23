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

int cmpr (const void * a, const void * b){
    return ((struct process*)a)->arrival_time - ((struct process *)b)->arrival_time;
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
	qsort(arr, SIZE, sizeof(struct process), cmpr);
        int i;
        int diff;
        int arrival;
        arr[0].start_time = 0;
        for (i = 1; i < SIZE; i++) {
           diff = arr[i-1].start_time + arr[i-1].execution_time + 1;
           arrival = arr[i].arrival_time;
           arr[i].start_time = diff>arrival?diff:arrival;
        }
	printf("Implemented!\n");
}
void schedule_SJF(struct process * arr)
{

        printf("Not implemented Yet!\n");
}
void schedule_LJF(struct process * arr)
{
        //TODO
        printf("Not implemented Yet!\n");
}
void display_average_waiting_time(struct process * arr)
{
	//TODO
        int total = 0;
        int i;
        for (i = 0; i < SIZE; i++) {
               total += arr[i].start_time - arr[i].arrival_time;
               printf("Current total: %d. Start: %d. Arrival %d\n", total, arr[i].start_time, arr[i].arrival_time);
        }
        float avrg;
        avrg = (float)total/(float)SIZE;
	printf("Average waiting time: %.3f\n",avrg);
}
