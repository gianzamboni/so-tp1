#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include "basesched.h"
using namespace std;

class SchedNoMistery : public SchedBase {
  public:
    SchedNoMistery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);  

  private:
  	vector<deque<int> > readyTasks;
  	vector<int> quantums;
	 
    int nextTask(int cpu);
	  bool noQuantumLeft(int currentCore);
	int lastQuantum;
};

#endif
