export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS) sched_mistery.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all

TPear: make ejercicio1 ejercicio2 ejercicio3 ejercicio4 ejercicio5 ejercicio6 ejercicio7 ejercicio8 

make:
	make
ejercicio1:
	./simusched -v ejercicio1.tsk 1 1 1 SchedFCFS 0 | python graphsched.py > ej1.png
ejercicio2:
	./simusched -v ejercicio2.tsk 1 5 1 SchedFCFS 0 | python graphsched.py > ej2_1.png
	./simusched -v ejercicio2.tsk 2 5 1 SchedFCFS 0 | python graphsched.py > ej2_2.png
	./simusched -v ejercicio2.tsk 4 5 1 SchedFCFS 0 | python graphsched.py > ej2_4.png
ejercicio3:
	./simusched -v ejercicio3.tsk 1 1 1 SchedFCFS 0 | python graphsched.py > ej3.png
ejercicio4:
	./simusched -v ejercicio4.tsk 1 1 1 SchedRR 2 | python graphsched.py > ej4_1.png
	./simusched -v ejercicio4.tsk 2 1 1 SchedRR 2 4 | python graphsched.py > ej4_2.png
	./simusched -v ejercicio4.tsk 4 1 1 SchedRR 2 4 6 | python graphsched.py > ej4_4.png
ejercicio5:
	./simusched -v ejercicio5.tsk 1 2 1 SchedRR 2 | python graphsched.py > ej5_2.png
	./simusched -v ejercicio5.tsk 1 2 1 SchedRR 10 | python graphsched.py > ej5_10.png
	./simusched -v ejercicio5.tsk 1 2 1 SchedRR 30 | python graphsched.py > ej5_30.png
ejercicio6:
	./simusched -v ejercicio5.tsk 1 2 1 SchedFCFS 0 | python graphsched.py > ej6.png
ejercicio7:
	./simusched -v ejercicio7cpu.tsk 1 1 1 SchedMistery 2 3 5 | python graphsched.py > ej7_CPU.png
	./simusched -v ejercicio7blk.tsk 1 1 1 SchedMistery 2 3 5 | python graphsched.py > ej7_BLK.png
	./simusched -v ejercicio7alt.tsk 1 1 1 SchedMistery 2 3 5 | python graphsched.py > ej7_ALT1.png
	./simusched -v ejercicio7alt.tsk 1 1 1 SchedMistery 5 2 3 | python graphsched.py > ej7_ALT2.png
	./simusched -v ejercicio7alt.tsk 1 1 1 SchedNoMistery 5 2 3 | python graphsched.py > ej7_ALTNoMistery.png
ejercicio8:
	./simusched -v ejercicio8.tsk 2 1 10 SchedRR2 4 8 | python graphsched.py > ej8RR2a.png
	./simusched -v ejercicio8.tsk 2 1 10 SchedRR 4 8 | python graphsched.py > ej8RR1a.png
	./simusched -v ejercicio8.tsk 2 1 10 SchedRR2 100 2 | python graphsched.py > ej8RR2b.png
	./simusched -v ejercicio8.tsk 2 1 10 SchedRR 100 2 | python graphsched.py > ej8RR1b.png
