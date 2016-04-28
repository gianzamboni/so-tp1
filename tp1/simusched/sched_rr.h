#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include "basesched.h"

class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		std::queue<int> q;
		std::deque<int> blockedTasks;

	// los recibe en orden en cantidad de cores
		std::vector<int> quantumes;
		std::vector<int> cuentaQuantumes;
		
		int getNextTask();
		bool noQuantumLeft(int currentCore);
};

#endif
