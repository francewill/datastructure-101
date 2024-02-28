/*
 * Author: 
 * Section: 
 * Program Description: 
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

/* Process Control Block (PCB) */
typedef struct PCB {
	int process_id;
	int arrival_time;
	int job_length;
	int wait_time;
	int run_time;
}PCB;

/* Singly-linked list of PCB */
typedef struct linked_list{
	PCB pcb;
	struct linked_list *next;
}linked_list;

/* Stores the processes */
linked_list *ready_queue = NULL;


/* Prints the details of the process */
void PrintPCB(PCB pcb){
	printf("\tProcess ID: %d, Arrival Time: %d, Job Length: %d, Wait Time: %d, Run Time: %d\n", pcb.process_id, pcb.arrival_time, pcb.job_length, pcb.wait_time, pcb.run_time);
}


/* Prints the processes in the ready queue */
void PrintReadyQueue(){
	linked_list *ptr = ready_queue;

	printf("\n\tPrinting Ready Queue:\n");

	while(ptr!=NULL){
		PrintPCB(ptr->pcb);
		ptr = ptr->next;
	}
    // printf("\n>>> This is head: id %d\n", ready_queue->pcb.process_id);
}


/* 
 * Reads from process.txt
   * First line of the file is the process count
   * Succeeding lines are the <arrival_time> <job_length> values
   * Assume that the processes are sorted in ascending order by arrival time
 * Stores <arrival_time> to arrival_time array
 * Stores <job_length> to job_length array
 * Returns the process count
 */
int ReadProcesses(int *arrival_time, int *job_length){
	int arrival, length, pcnt;
	FILE *fp;

	fp = fopen("process.txt", "rw");
	
	if(fp != NULL){
		fscanf(fp, " %d\n",&pcnt);
		for(int i = 0; i<pcnt;i++){
			fscanf(fp, " %d %d\n",&arrival,&length);
			arrival_time[i] = arrival;
			job_length[i] = length;
		
		}



		fclose(fp);
	}
	return pcnt;
}


/* 
 * Prints the terminated process
 * Removes the terminated process at the head of the queue
 */
void Dequeue(){	
	printf("\tThe following process already ended:\n");
    PrintPCB(ready_queue->pcb);
	linked_list *temp = ready_queue;
	ready_queue = ready_queue->next;
	free(temp);

	

}


/* Inserts the process in the queue */
void Enqueue(int process_id, int arrival, int job_length){
	printf("HAHA");
	PCB *p = (PCB *) malloc (sizeof(PCB));
	p->process_id = process_id;
	p->job_length = job_length;
	p->arrival_time = arrival;
	p->wait_time = 0;
	p->run_time = 0;

	linked_list *node = (linked_list *) malloc (sizeof(linked_list));
	node->pcb = *p;
    int statusHead = -1;
    if(ready_queue!=NULL){
        statusHead =  ready_queue->pcb.job_length - ready_queue->pcb.run_time;
        printf("\nstatus = %d\n", statusHead);
    }
    // printf("\nA\n");
	if(ready_queue==NULL || statusHead>p->job_length){  // add at head
		// printf("\nB\n");
		node->next = ready_queue;
		ready_queue = node;
	}else{
        printf("\nB\n");
		linked_list *temp;
		for(temp = ready_queue; temp->next!=NULL; temp = temp->next){
            statusHead = temp->pcb.job_length - temp->pcb.run_time;
			if(statusHead<p->job_length){

				break;
			}
   
		}
		node->next = temp->next;
		temp->next = node;
	}

	

}


/*
 * Simulates processing of a single CPU cycle
 * Increases the run time of the currently executing process
   * Currently executing processs is the first process in the queue
 * Increases the wait time of the other processes in the queue
 * Checks if a process terminates (run time == job length)
 */
void Processing(){
	ready_queue->pcb.run_time++;
	
	
	linked_list *traverse = ready_queue;
	if(traverse==NULL){
		return;
	}else{
		for(traverse;traverse!=NULL; traverse = traverse->next){
            if(traverse==ready_queue){
                continue;
            }
			traverse->pcb.wait_time++;
		}
	}

	if(ready_queue->pcb.run_time == ready_queue->pcb.job_length){
		Dequeue();

	}

}


/* 
 * Simulates the CPU scheduling
 * Checks the arrival of processes in a given cpu cycle
 * Updates the processes in the queue
 * Prints the processes in the ready queue
 */
void RunSimulation(int *arrival_time, int *job_length, int process_count){
	int i=0, cpu_cycles=1;
	
	while(1){
		
		if(cpu_cycles == arrival_time[i]){
			
			Enqueue(i,arrival_time[i],job_length[i]);
			i++;
		}

		printf("\nCPU Cycle: %d\n", cpu_cycles);


		




		Processing();
        if(ready_queue!=NULL){
            PrintReadyQueue();
        }else{
            printf("\nReady Queue is empty!\n");
        }
		
		cpu_cycles++;
		if(ready_queue == NULL) break;
	}
}


int main(){	
	int arrival_time[MAX], job_length[MAX];
	int process_count = ReadProcesses(arrival_time, job_length);
	RunSimulation(arrival_time, job_length, process_count);
}