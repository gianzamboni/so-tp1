#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include "basesched.h"

using namespace std;

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		std::vector<deque<int> > blockedTasks;
		std::vector<deque<int> > readyTasks;
		std::vector<int> tasksPerCore;

	// los recibe en orden en cantidad de cores
		std::vector<int> quantumes;
		std::vector<int> cuentaQuantumes;

		int searchInBlockedTasks(int pid);
		int getNextTask(int cpu);
		bool noQuantumLeft(int currentCore);
		int minQueue(); 
		int cores;
};

#endif
