#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "stdc++.h"

using namespace std;

//Structures
struct Process {
	int pid;
	int arrival;
	int burst;
	int priority;
	int ex_time;
};

//Globals
bool done = false;
int _time = 0;
const int NUM_PROCESSES = 100;

//Functions
void file_read();

int main() {
	file_read();
	system("pause");
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

	int num[150], arrival[150], burst[150], priority[150];
	int quantum = 2;

	//Read file line by line & set  process arrays
	for (int i = 1; i < NUM_PROCESSES ;) {
		Process proc[102] = { arrival[i], burst[i], priority[i] };
		while (pr_File >> arrival[i] >> burst[i] >> priority[i]) {
			cout << "Process: " << i << " " << "| Arrival: " << arrival[i] << " " << "| Burst: " << burst[i] << " " << "| Prority: " << priority[i] << " " << '\n';
			proc[i].pid = i;
			proc[i].arrival = arrival[i];
			proc[i].burst = burst[i];
			proc[i].priority = priority[i];
			i++;
		}
		i = 1;
		cout << proc[i].pid << " " << proc[i].arrival << " " << proc[i].burst << " " << proc[i].priority << " " << endl << '\n';
		pr_File.close();
		
		if (i == 1) {
			
			proc[i].burst = proc[i].burst - quantum;
			_time = _time + quantum;
			if (proc[i].burst == 0) {
				done = true;
			}
			else if (proc[i].burst < 0) {
				done = true;
				proc[i].burst = 0;
				_time = _time + (-1 * proc[i].burst);
				proc[i].ex_time = _time;
			}
			if (done) {
				cout << "Process: " << proc[i].pid << " Finished at time: " << proc[i].ex_time << endl;
			}
			cout << "Current Time: " << _time << endl;
			i++;
			system("pause");

		}
		else {
		
			if (_time < proc[i].arrival) {
				
				if (proc[i - 1].burst > 0) {
					proc[i - 1].burst = proc[i - 1].burst - quantum;
				}
				_time = _time + 1;
			}
			else  if (_time >= proc[i].arrival) {


				if (proc[i].priority > proc[i + 1].priority) {
					proc[i + 1].burst = proc[i + 1].burst - quantum;
				}
				else if (proc[i].priority < proc[i + 1].priority) {
					proc[i].burst = proc[i].burst - quantum;
				}


				if (done) {
					cout << "Process: " << proc[i].pid << " Finished at time: " << proc[i].ex_time << endl;
				}
			}
		}
		i++;
	}
	
}

