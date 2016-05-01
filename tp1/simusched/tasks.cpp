#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "tasks.h"

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

int dameRandEntre(int bmin, int bmax){
  	srand(time(NULL));	
 	sleep(1);
 	cout << "rango [" << bmin << "; " << bmax << "]" << endl;
 	int module = (bmax - bmin);
 	int nr;
 	if (module == 0) {
		nr = bmin;
 	} else {
		nr = rand() %  module + bmin;
 	}
 	cout << "numero random: " << nr << endl;
	return nr;
}


/*********************************************************************************************************************
 *********************************************************************************************************************
 *********************************************************************************************************************
 ******																											******
 ******												EJERCICIO 1 												******
 ******																											******
 *********************************************************************************************************************
 *********************************************************************************************************************
 *********************************************************************************************************************/

void TaskConsola(int pid, std::vector<int> params){ // params: n, bmin, bmax
	int n = params[0];
	int bmin = params[1];
	int bmax = params[2];

	for(int i = 0; i < n; i++){
		uso_IO(pid, dameRandEntre(bmin, bmax));
	};
}

/*********************************************************************************************************************
 *********************************************************************************************************************
 *********************************************************************************************************************
 ******																											******
 ******												EJERCICIO 2 												******
 ******																											******
 *********************************************************************************************************************
 *********************************************************************************************************************
 *********************************************************************************************************************/

void usuario1(int pid, std::vector<int> params){
    uso_CPU(pid, 9);
    uso_IO(pid, dameRandEntre(1,4));
}

void usuario2(int pid, std::vector<int> params){
    uso_CPU(pid, 19);
    uso_IO(pid, dameRandEntre(1,4));
}

void usuario3(int pid, std::vector<int> params){
	uso_CPU(pid, 29);
    uso_IO(pid, dameRandEntre(1,4));
}

void procesoPesado(int pid, std::vector<int> params){
	uso_CPU(pid, 500);
}

/*********************************************************************************************************************
 *********************************************************************************************************************
 *********************************************************************************************************************
 ******																											******
 ******												EJERCICIO 3 												******
 ******																											******
 *********************************************************************************************************************
 *********************************************************************************************************************
 *********************************************************************************************************************/

bool isAcceptable(int val, std::vector<int>* v, int i) {
	for(uint j = 0; j < i; j++) {
		if( !(val < (*v)[j]-2 || val > (*v)[j]+3)) {
			return false;
		} 
	}
	return true;
}	

void fillWithOrderedRands(vector<int>* v, int maxValue){
	vector<int>::iterator it = v->begin();
	cout << "el vector inicia con tamaño " << v->size() << endl;
	for (uint i = 0; i < v->size(); i++) {
		cout << "el vector tiene tamaño " << v->size() << endl;
		int val = dameRandEntre(0, maxValue);
		cout << "se quiere insertar el random: " << val << endl;
		if(i == 0){
			(*v)[i] = val;
			cout << "inserte al primero" << endl;
		} else if(i == 1) {
			cout << "ubicando al segundo ..."<< endl;
			int cotaSuperior = (*v)[i-1] + 2;
			int cotaInferior = (*v)[i-1] - 2;
			cout << "la cota inferior es " << cotaInferior << endl;
			cout << "la cota superior es " << cotaSuperior << endl;
			while(!(val < cotaInferior || val > cotaSuperior)) {
				cout << "como " << val << " < " << cotaInferior << "o bien " << val << " > " << cotaSuperior << endl;
				val = dameRandEntre(0, maxValue);
				cout << val << " es mi nuevo random" << endl;
			}
			cout << val << " me sirve" << endl;
			(*v)[i] = val; 
			cout << "yay! ya ubique al segundo y lo asigne" << endl;
		} else {
			cout << "ubico uno mas" << endl;
			while(!isAcceptable(val,v, i)) {
				cout << val << "no es aceptable" << endl;
				val = dameRandEntre(0, maxValue);
			}
			(*v)[i] = val;
			cout << "ya ubique el " << i << "-esimo" << endl;
		}
		cout << "ordeno" << endl;
		sort(v->begin(), ++it);
		cout << "El vector es: {"; 
		for (std::vector<int>::const_iterator it2 = v->begin(); it2 != v->end(); ++it2) cout << *it2 << ' ';
		cout << "}" << endl;
	}
	sort(v->begin(), v->end());
	cout << "Ya ordene todo" << endl;
	return;
}


bool usado(vector<int>* v, int k){
	bool usado = false;
  	for(uint i = 0; i < v->size(); i++){
    	if((*v)[i] + 2 < k) {
      		usado = true;
      		break;
    	}
  	}

  	return usado;
}

void TaskBatch(int pid, std::vector<int> params) {  // params: total_cpu, cant_bloqueos
	int total_cpu = params[0];
	int cant_bloqueos = params[1];
  	vector<int> bloqueos(cant_bloqueos); 
  	fillWithOrderedRands(&bloqueos, total_cpu);
  	cout << "Hola, soy el proces con pid " << pid << " y ya decidi cuando voy a bloquearme" << endl; 
  	int cpu_usado = 0;
  	for(int i = 0; i < cant_bloqueos; i++){
  		int cpu_a_usar = bloqueos[i] - cpu_usado;
  		cout << "El primer bloqueo es en el tick " << bloqueos[i] << ", asi que voy a usar " << cpu_a_usar << " antes de bloquearme" << endl;
   		uso_CPU(pid, cpu_a_usar);
   		cpu_usado += cpu_a_usar	;
   		uso_IO(pid, 2);
  	}
  return;
}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(usuario1, 0);
	register_task(usuario2, 0);
	register_task(usuario3, 0);
	register_task(procesoPesado, 0);
	register_task(TaskBatch, 2);
}
