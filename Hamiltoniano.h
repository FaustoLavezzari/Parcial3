#pragma once
#include <vector>
#include<queue>
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
		distancia = pad->getDistancia() + arista;
	}

	double getDistancia() { return distancia; }
	Nodo* getPadre() { return padre; }
	int getNumVertice() { return num_vertice; }
};


vector<int> encontrarHamiltoniano(vector<vector<double>> matrizAdyacencia) {
	queue<Nodo> cola;
	queue<Nodo> colaFinalizados;
	Nodo raiz();

}

bool perteneceALosPadres(Nodo *nodo, int num){										//Filtro recursivo, para saber si el numero que le ingreso, pertenece a alguno de los padres o padres de los padres
	if(nodo->getPadre() == NULL){
		return false;
	}
	if (nodo->getPadre()->getNumVertice() == num) {
		return true;
	}
	else {
		return perteneceALosPadres(nodo->getPadre(), num);
	}
}