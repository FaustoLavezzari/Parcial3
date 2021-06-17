#pragma once
#include <vector>
#include<queue>
#define  INF 999999
using namespace std;

class Nodo {
private:
	Nodo* padre;
	int num_vertice;
	double distancia;
public:
	Nodo(Nodo* pad, int num, double arista) {
		padre = pad;
		num_vertice = num;
		if (pad == NULL){
			distancia = 0;
		}
		else{
			distancia = pad->getDistancia() + arista;
		}
	}

	double getDistancia() { return distancia; }
	Nodo* getPadre() { return padre; }
	int getNumVertice() { return num_vertice; }
	
};




