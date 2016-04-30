#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"

using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	quantums.push_back(1);
	for(int i = 1; i < argn.size()-2; i++){
		quantums.push_back(argn[i+2]);
	}  
}

void SchedNoMistery::load(int pid) {  
	taskDequeue.push_back(pid);
	cout << "Loading task #" << pid << endl;
}

void SchedNoMistery::unblock(int pid) {  
	deque<int>::iterator it = blockedTasks.begin();
	for (; it != blockedTasks.end(); it++) {
		if(*it == pid) break;
	}
	blockedTasks.erase(it);
	taskDequeue.push_front(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {  
	if (current_pid(cpu) == IDLE_TASK || m == EXIT) {
		cuentaQuantumes[cpu] = quantumes[cpu];
		return nextTask(cpu);
	} else if (m == TICK && noQuantumLeft(cpu)) {
		cout << "no quantum left" << endl;
		taskDequeue.push_back(current_pid(cpu));
		cuentaQuantumes[cpu] = quantumes[cpu];
		cout << "quantum reinit: new quantum is " << cuentaQuantumes[cpu] << endl;
		return nextTask(cpu);
	} else if (m == BLOCK) {
		blockedTasks.insert(blockedTasks.begin(), current_pid(cpu));
		return nextTask(cpu);
	} else {
		cuentaQuantumes[cpu]--;
		cout << "Tick for process " << current_pid(cpu) << " quantum decrease: new quantum is " << cuentaQuantumes[cpu] << endl;
		return current_pid(cpu);
	}
}

int SchedNoMistery::nextTask(int cpu){
	if (taskDequeue.empty()) {
		return IDLE_TASK	;
	} else {
		int next = taskDequeue.front();
		taskDequeue.pop_front();
	cout << "next task number: " << next << endl;
		return next;
	}
}

bool SchedNoMistery::noQuantumLeft(int currentTick) {
	return cuentaQuantumes[currentTick] == 0;
}

