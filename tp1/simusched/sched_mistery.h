#ifndef __SCHED_MIS__
#define __SCHED_MIS__

#include <vector>
#include <queue>
#include "basesched.h"

class SchedMistery : public SchedBase {
  public:
    SchedMistery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);

  private:
    //Esto es sólo un fake para que el compilador calcule el tamaño
    //correcto de la clase
    std::vector<int> lala;
    std::vector<int> lala2;
    std::vector<int> lala3;
    int lala4, lala5, lala6;
    int lala7(void);
};

#endif

