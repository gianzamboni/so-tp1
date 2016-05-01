#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <iostream>
using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	readyTasks = vector<deque<int> >(argn.size(), deque<int>());
  	quantums = vector<int>(argn.begin(), argn.end());
  	nexQueueToPush = 0;
  	lastQueuePoped = 0;
  	resetQuantum();
}

void SchedNoMistery::load(int pid) {
	readyTasks[0].push_back(pid);
	cout << "Loading task #" << pid << endl;
}

void SchedNoMistery::unblock(int pid) {  
	/*deque<int>::iterator it = blockedTasks.begin();
	for (; it != blockedTasks.end(); it++) {
		if(*it == pid) break;
	}
	blockedTasks.erase(it);
	taskDequeue.push_front(pid);*/
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {  
	if (current_pid(cpu) == IDLE_TASK || m == EXIT) {
		return nextTask();
	} else if (m == TICK && noQuantumLeft()) {
		cout << "no quantum left" << endl;
		pushToCertainQueue(current_pid(cpu), lastQueuePoped, 0);
		return nextTask();
	} else if (m == BLOCK) {
		// blockedTasks.insert(blockedTasks.begin(), current_pid(cpu));
		// return nextTask(cpu);
	} else {
		quantumCounter--;
		cout << "Tick for process " << current_pid(cpu) << " quantum decrease: new quantum is " << quantumCounter << endl;
		return current_pid(cpu);
	}

	return -1;
}

int SchedNoMistery::nextTask(){
	lastQueuePoped = getNextQueueToBePoped();
	if(lastQueuePoped == -1) return IDLE_TASK;
	resetQuantum();
	int next = readyTasks[lastQueuePoped].front();
	readyTasks[lastQueuePoped].pop_front();
	cout << "next task number: " << next << endl;
	return next;
	
	}

bool SchedNoMistery::noQuantumLeft(){
	return quantumCounter == 0;
}

int SchedNoMistery::getNextQueueToBePoped(){
	int i = 0;
	for(; i < readyTasks.size(); i++){
		if(!readyTasks[i].empty()) return i;
	}
	if(i = readyTasks.size()) return -1;
};

void SchedNoMistery::resetQuantum(){
	quantumCounter = quantums[lastQueuePoped]-1;
}

void SchedNoMistery::pushToCertainQueue(int pid, int lastPriority, bool wasBlocked){
	if(wasBlocked){}
	else {
		if(lastPriority == quantums.size()-1) readyTasks[lastPriority].push_back(pid);
		else readyTasks[++lastPriority].push_back(pid);
	}
};