#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	cuentaQuantumes = vector<int>(argn[0]);
	quantumes = vector<int>(argn[0]);

	for(int i = 0; i < argn[0] - 1; i++){
		cuentaQuantumes[i] = argn[i+1];
		quantumes[i] = argn[i+1];
	}
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	q.push(pid);
}

void SchedRR::unblock(int pid) {
	// deque<int>::iterator it = blockedTasks.begin();
	// for (; it!=blockedTasks.end(); ++it){
	// 	if(*it != pid) break;
	// };

	// blockedTasks.erase(it);
	q.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	if (current_pid(cpu) == IDLE_TASK || m == EXIT ) {
		getNextTask();
	} else if(m == TICK && noQuantumLeft(cpu)) {
		q.push(current_pid(cpu));
		return getNextTask();
	} else if(m == BLOCK) {
		blockedTasks.insert(blockedTasks.begin(), current_pid(cpu));
		cuentaQuantumes[cpu] = quantumes[cpu];
		return getNextTask();
	} else {
		cuentaQuantumes[cpu]--;
		return  current_pid(cpu);
	}
}

int SchedRR::getNextTask(){
	int sig = q.front(); 
	q.pop();
	if(sig == IDLE_TASK && !q.empty()) {
		q.push(sig);
		sig = q.front();
		q.pop();
	}
	return sig;
}

bool SchedRR::noQuantumLeft(int currentCore) {
	return cuentaQuantumes[currentCore] == 0;
}
