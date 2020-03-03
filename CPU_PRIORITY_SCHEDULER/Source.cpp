#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <queue>
/*************************************************************************************************
									CPU_PRIORITY_SCHEDULER
									@Author@ - Ryan Dobbe
this program takes in process inputs from a file and schedules time in a preemptive priority
secondary Round Robin with quantum initially set to 2.  The quantum value is adjustable for the 
User.  Output of the process execution as well as turnaround times and total avg turnaround times
are shown on the consle. Input file is int the format:
							Arrival --->  Burst  --->   Priority
							0				2				2
**************************************************************************************************/

using namespace std;

//Globals
const int NUM_PROCESSES = 100;

//Functions
void file_read();

int main() {
	file_read();
	return 0;
}

void file_read() {
	//Set stream and open inputs file
	ifstream pr_File;
	pr_File.open("processes.txt");
	//Error check
	if (pr_File.fail()) {
		cerr << "FILE NOT FOUND" << endl;
		exit(1);
	}

	//Read process.txt into memory
	int arrival[100];
	int burst[100];
	int priority[100];
	queue <int> circ_buff;
	int exc_time[100];
	int tat_time[100];
	int tat_total = 0;
	int att_time;

	for (int i = 0; i < NUM_PROCESSES; i++) {
		pr_File >> arrival[i] >> burst[i] >> priority[i];
	}

	//Apply priority scheduler
	int time = 0;
	int quantum = 2;
	int num_processes_left = NUM_PROCESSES;
	int cp_quantum = 0;
	//Loop
	while (num_processes_left > 0) {

		//Add processes with arrival equal to time to a "buffer"
		for (int i = 0; i < NUM_PROCESSES; i++) {
			if (time == arrival[i]) {
				circ_buff.push(i);
			}
		}

		//If another process is in the queue
		if (circ_buff.size() <= 0) {
			//Empty Queue
			cp_quantum = 0;
			time++;

		}else {
			//Move process to back of queue when quantum threshold is hit
			if (cp_quantum >= quantum && circ_buff.size() > 1) {
				//Multiple in queue
				int temp = circ_buff.front();
				circ_buff.pop();
				circ_buff.push(temp);
				cp_quantum = 0;
			}


			//Process (step time)
			burst[circ_buff.front()] = burst[circ_buff.front()] - 1;
			cp_quantum++;
			time++;
			cout << "Processing " << circ_buff.front() + 1 << "	Q = " << cp_quantum << endl;

			//Remove Finished Processes
			if (burst[circ_buff.front()] <= 0) {
				//Calculate turn around time for each process
				exc_time[circ_buff.front()] = time;
				tat_time[circ_buff.front()] = exc_time[circ_buff.front()] - arrival[circ_buff.front()];
				cout << "Process " << circ_buff.front() + 1 << " has finished at time " << time << endl;
				cout << "Process " << circ_buff.front() + 1 << " Turnaround Time: " << tat_time[circ_buff.front()] << endl;
				circ_buff.pop();
				num_processes_left--;
				cp_quantum = 0;
				
			}

		}

	}
	pr_File.close();
	
	//Calculate Avg time
	for (int i = 0; i < NUM_PROCESSES; i++) {
		tat_total = tat_total + tat_time[i];
	}

	att_time = tat_total / NUM_PROCESSES;

	cout << "Average Turnaround Time : " << att_time << endl;
	
}

