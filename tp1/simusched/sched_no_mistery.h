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
    deque<int> blockedTasks;
    deque<int> blockedTasksPriority;

	  int quantumCounter;
    int nexQueueToPush;
    int lastQueuePoped;
    int nextTask();
	  bool noQuantumLeft();
    int getNextQueueToBePoped();
    void resetQuantum();
    void pushToCertainQueue(int pid, int lastPriority, bool wasBloqued);
    void blockTask(int pid);
};

#endif
