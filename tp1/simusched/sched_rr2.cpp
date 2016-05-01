#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>
#include <limits.h>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	
	cores = argn[0];

	cout << "Number of cores: " << cores << endl;
	cuentaQuantumes = vector<int>(cores);
	quantumes = vector<int>(cores);
	blockedTasks = vector<deque<int> >(cores, deque<int>());
	readyTasks = vector<deque<int> >(cores, deque<int>());
	tasksPerCore = vector<int>(cores, 0);

	for(int i = 0; i < argn.size()-2; i++){
		cuentaQuantumes[i] = argn[i+2];
		cout << "Se carga el quantum " << argn[i+2] << " para el core " << i << endl;
		quantumes[i] = argn[i+2];
	}

}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
	int minTasksCore = this->minQueue();
	readyTasks[minTasksCore].push_back(pid);
	cout << "Loading task #" << pid << endl;
	tasksPerCore[minTasksCore]++;
}

void SchedRR2::unblock(int pid) {

	int index = searchInBlockedTasks(pid);

	deque<int>::iterator it = blockedTasks[index].begin();
	for (; it != blockedTasks[index].end(); it++) {
		if(*it == pid) break;
	}
	blockedTasks[index].erase(it);
	readyTasks[index].push_back(pid);
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	if (current_pid(cpu) == IDLE_TASK) {
		cuentaQuantumes[cpu] = quantumes[cpu];
		return getNextTask(cpu);
	} else if (m == EXIT) {
		tasksPerCore[cpu]--;
		cuentaQuantumes[cpu] = quantumes[cpu];
		return getNextTask(cpu);
	} else if (m == TICK && noQuantumLeft(cpu)) {
		cout << "no quantum left" << endl;
		readyTasks[cpu].push_back(current_pid(cpu));
		cuentaQuantumes[cpu] = quantumes[cpu];
		cout << "quantum reinit: new quantum is " << cuentaQuantumes[cpu] << endl;
		return getNextTask(cpu);
	} else if (m == BLOCK) {
		blockedTasks[cpu].insert(blockedTasks[cpu].begin(), current_pid(cpu));
		return getNextTask(cpu);
	} else {
		cuentaQuantumes[cpu]--;
		cout << "Tick for process " << current_pid(cpu) << " quantum decrease: new quantum is " << cuentaQuantumes[cpu] << endl;
		return current_pid(cpu);
	}
}

int SchedRR2::getNextTask(int cpu){
	if (readyTasks[cpu].empty()) {
		return IDLE_TASK;
	} else {
		int sig = readyTasks[cpu].front();
		readyTasks[cpu].pop_front();
	cout << "next task number: " << sig << endl;
		return sig;
	}
}

bool SchedRR2::noQuantumLeft(int currentCore) {
	return cuentaQuantumes[currentCore] == 0;
}

int SchedRR2::minQueue() {
	int min = 0;
	for (int i = 0; i < cores; i++) {
		cout << "amount of current tasks in core " << i << " is " << tasksPerCore[i] << endl;
		if (tasksPerCore[i] < tasksPerCore[min]) {
			cout << "tasksPerCore[i] in core "<< i << " evaluates to " << tasksPerCore[i] << " < " << tasksPerCore[min] << "min" << endl;
			min = i;
		}
		cout << "min is " << min << endl;
	}
	cout << "The min queue is " << min << endl;
	return min;
}

int SchedRR2::searchInBlockedTasks(int pid) {
	for(int i = 0; i < cores; i++) {
		int j;
		deque<int>* d = &blockedTasks[i];
		for(j = 0; j < d->size(); j++) {
			if ((*d)[j] == pid) break;
		}
		if ( j != d->size()) return i;
	}
}
