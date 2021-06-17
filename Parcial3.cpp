#include <iostream>
#include "Bitset.h"
#include <queue>
#include "Estrcuturas.h"
#include "Hamiltoniano.h"
#include <fstream>
#include <sstream>
#include <vector>
#define  INF 999999
using namespace std;
void cargarMapa(int mapa[N][M]);
void imprimir(int mapa[N][M]);
void encontrarBarreras(int mapa[N][M], queue<Barrera> &barreras);
bool hayInterseccion(coordenada A1, coordenada B1, coordenada A2, coordenada B2);
int orientation(coordenada p, coordenada q, coordenada r);
bool onSegment(coordenada p, coordenada q, coordenada r);
float calcularArista(coordenada pt1, coordenada pt2);
vector<coordenada> cargarMalezas( queue<coordenada> cola);
void armarMatrizAdyacencia(vector<Barrera>& muros, vector<coordenada>& malezas, vector<vector<double>>& grafo);
vector<Barrera> cargarBarreras(queue<Barrera> cola);
Nodo* encontrarHamiltoniano(vector<vector<double>> matrizAdyacencia);
bool perteneceALosPadres(Nodo* nodo, int num);
int cuantosPadresTengo(Nodo* hijo, int contador);
void imprimirRecorrido(Nodo* final);


int main() {
	vector<vector<double>> matrizAdyacencia ;
	vector<coordenada> coordenadasMalezas;
	vector<Barrera> barrerasVector;
	queue<Barrera> barreras;
	queue<coordenada> malezas;
	int mapa[N][M];
	
	cargarMapa(mapa);
	encontrarBarreras(mapa, barreras);
	Filtro filtro;
	malezas = filtro.buscarMaleza(mapa);
	coordenadasMalezas = cargarMalezas(malezas);
	barrerasVector = cargarBarreras(barreras);
	armarMatrizAdyacencia(barrerasVector,coordenadasMalezas,matrizAdyacencia);
	Nodo* final = encontrarHamiltoniano(matrizAdyacencia);
	imprimirRecorrido(final);
	cout << "El dron recorrio: " << final->getDistancia() << " metros" << endl;
   
	return 0;
}

void cargarMapa(int mapa[N][M]) {
	ifstream archivo;
	string linea;
	archivo.open("Mapa.txt", ios::out);
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}

	for (int i = 0; i < N; i++) {
		getline(archivo, linea);
		for (int j = 0; j < M; j++) {
			if (linea[j] == 'x') {
				mapa[i][j] = 2;
			}
			else if (linea[j] == '1') {
				mapa[i][j] = 1;
			}
			else {
				mapa[i][j] = 0;
			}
		}
	}
}

void encontrarBarreras(int mapa[N][M], queue<Barrera> &barreras) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (mapa[i][j] == 2 && j + 3 < M && mapa[i][j + 3] == 2) {
				coordenada final;
				coordenada comienzo;
				final.y = i;
				comienzo.x = j;
				comienzo.y = i;
				for (int q = 0; q <= 2; q++) {
					mapa[i][j + q] = 0;
				}
				for (int k = j + 3; mapa[i][k] == 2; k++) {
					final.x = k;
					mapa[i][k] = 0;
				}
				Barrera barrera;
				barrera.comienzo = comienzo;
				barrera.final = final;
				barreras.emplace(barrera);
			}
			else if(mapa[i][j] == 2 && i+3 <N && mapa[i + 3][j] == 2){
				coordenada final;
				coordenada comienzo;
				final.x = j;
				comienzo.x = j;
				comienzo.y = i;
				for (int q = 0; q <= 2; q++) {
					mapa[i + q][j] = 0;
				}
				for (int k = i + 3; mapa[k][j] == 2; k++) {
					final.y = k;
					mapa[k][j] = 0;
				}
				Barrera barrera;
				barrera.comienzo = comienzo;
				barrera.final = final;
				barreras.emplace(barrera);
			}
		}
	}
}

void imprimir(int mapa[N][M]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << mapa[i][j];
		}
		cout << endl;
	}
}

bool hayInterseccion(coordenada p1, coordenada q1, coordenada p2, coordenada q2) {
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}

int orientation(coordenada p, coordenada q, coordenada r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool onSegment(coordenada p, coordenada q, coordenada r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

float calcularArista(coordenada pt1, coordenada pt2) {
	int A=pt1.x - pt2.x;
	int B = pt1.y - pt2.y;
	double C = sqrt((A * A) + (B * B));
	return C;
}

vector<coordenada> cargarMalezas(queue<coordenada> cola) {
	queue<coordenada> colaAux = cola;
	vector<coordenada> vector1;
	for (int i = 0; !colaAux.empty(); i++) {
		vector1.push_back(colaAux.front());
		colaAux.pop();
	}
	return vector1;
}

vector<Barrera> cargarBarreras(queue<Barrera> cola) {
	queue<Barrera> colaAux = cola;
	vector<Barrera> vector1;
	for (int i = 0; !colaAux.empty(); i++) {
		vector1.push_back(colaAux.front());
		colaAux.pop();
	}
	return vector1;
}

void armarMatrizAdyacencia(vector<Barrera>& muros, vector<coordenada>& malezas, vector<vector<double>>& grafo) {
	grafo.resize(malezas.size());
	for (int i = 0; i < malezas.size(); i++) {
		grafo[i].resize(malezas.size());
	}
	for (int i = 0; i < malezas.size(); i++) {
		coordenada pos_Aux = malezas[i];
		for (int j = 0; j < malezas.size(); j++) {
			coordenada pos_Aux2 = malezas[j];
			bool bandera = true;
			for (int m = 0; m < muros.size(); m++) {
				Barrera m_aux = muros[m];

				if (hayInterseccion(pos_Aux, pos_Aux2, m_aux.comienzo , m_aux.final) || i==j) {
					grafo[i][j] = INF;
					bandera = false;
				}
			}
			if (bandera) {
				grafo[i][j] = calcularArista(pos_Aux, pos_Aux2);
			}
		}
	}

}

Nodo* encontrarHamiltoniano(vector<vector<double>> matrizAdyacencia) {
	queue<Nodo*> cola;
	vector<Nodo*> Finalizados;
	Nodo* siguiente = new Nodo(NULL, 0, 0);
	cola.emplace(siguiente);
	int contador = 0;
	while (!cola.empty())
	{
		bool fin = true;
		siguiente = cola.front();
		cola.pop();
		for (int j = 0; j < matrizAdyacencia.size(); j++) {
			if (matrizAdyacencia[siguiente->getNumVertice()][j] != INF && !(perteneceALosPadres(siguiente, j))) {
				Nodo* hijo = new Nodo(siguiente, j, matrizAdyacencia[siguiente->getNumVertice()][j]);
					cola.emplace(hijo);
					fin = false;
			}
		}
		if (fin && cuantosPadresTengo(siguiente,contador) == (matrizAdyacencia.size()-1) && matrizAdyacencia[siguiente->getNumVertice()][0] != INF) {
			Nodo* inicio = new Nodo(siguiente, 0, matrizAdyacencia[siguiente->getNumVertice()][0]);
			Finalizados.push_back(inicio);
		}
	}
	Nodo* aux = new Nodo (NULL,0,0);
	for(int i = 0; i < Finalizados.size(); i++) {
		for (int j = i + 1; j < Finalizados.size(); j++) {
			if (Finalizados[i]->getDistancia() > Finalizados[j]->getDistancia()) {
				aux = Finalizados[i];
				Finalizados[i] = Finalizados[j];
				Finalizados[j] = aux;
			}
		}
	}
	return Finalizados[0];
}

bool perteneceALosPadres(Nodo * nodo, int num) {										//Filtro recursivo, para saber si el numero que le ingreso, pertenece a alguno de los padres o padres de los padres
	if (nodo->getPadre() == NULL) {
		return false;
	}
	if (nodo->getPadre()->getNumVertice() == num) {
		return true;
	}
	else {
		return perteneceALosPadres(nodo->getPadre(), num);
	}
}

int cuantosPadresTengo(Nodo* nodo , int contador) {
	
	if (nodo->getPadre() == NULL) {
		return contador;
	}
	else {
		contador++;
		return cuantosPadresTengo(nodo->getPadre(), contador);
	}
}

void imprimirRecorrido(Nodo* nodo) {
	if (nodo->getPadre() != NULL) {
		cout << "Voy desde la maleza "<<nodo->getNumVertice()<<" hacia la maleza "<<nodo->getPadre()->getNumVertice()<<endl;
		imprimirRecorrido(nodo->getPadre());
	}
}
