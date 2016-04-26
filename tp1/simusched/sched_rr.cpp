#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;


SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	q.push(pid);
}

void SchedRR::unblock(int pid) {
	deque<int>::iterator it = blockedTasks.begin();
	for (; it!=blockedTasks.end(); ++it){
		if(*it != pid) break;
	};

	blockedTasks.erase(it);
	q.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	if (m == EXIT) {
		if (q.empty()) return IDLE_TASK;
	} else if(m == TICK) {
		q.push(current_pid(cpu));
	} else {
		blockedTasks.insert(blockedTasks.begin(), current_pid(cpu));
	}
	
	return getNextTask();
	
}

int SchedRR::getNextTask(){
	int sig = q.front(); 
	q.pop();
	return sig;
}