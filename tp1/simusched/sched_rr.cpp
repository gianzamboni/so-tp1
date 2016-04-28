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

	load(IDLE_TASK);

	for(int i = 0; i < argn.size()-2; i++){
		cuentaQuantumes[i] = argn[i+2];
		cout << "Se carga el quantum " << argn[i+2] << " para el core " << i << endl;
		quantumes[i] = argn[i+2];
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
	cuentaQuantumes[cpu]--;
		cout << "quantum decrease: new quantum is " << cuentaQuantumes[cpu] << endl;
	if (current_pid(cpu) == IDLE_TASK || m == EXIT ) {
		getNextTask(cpu);
	} else if(m == TICK && noQuantumLeft(cpu)) {
		cout << "no quantum left" << endl;
		q.push(current_pid(cpu));
		cuentaQuantumes[cpu] = quantumes[cpu];
		return getNextTask(cpu);
	} else if(m == BLOCK) {
		blockedTasks.insert(blockedTasks.begin(), current_pid(cpu));
		return getNextTask(cpu);
	} else {
		return  current_pid(cpu);
	}
}

int SchedRR::getNextTask(int cpu){
	int sig = q.front();
	q.pop();
	cout << "next task number: " << sig << endl;
	if(sig == IDLE_TASK && !q.empty()) {
		q.push(sig);
		sig = q.front();
		if (sig != IDLE_TASK) q.pop();
		cout << "quantum reinit: new quantum is " << cuentaQuantumes[cpu] << endl;
	}
	return sig;
}

bool SchedRR::noQuantumLeft(int currentCore) {
	return cuentaQuantumes[currentCore] == 0;
}
