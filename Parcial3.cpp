#include <iostream>
#include "Bitset.h"
#include <queue>
#include "Estrcuturas.h"
#include <fstream>
#include <sstream>
using namespace std;

void cargarMapa(int mapa[N][M]);
void imprimir(int mapa[N][M]);
void encontrarBarreras(int mapa[N][M], queue<Barrera> &barreras);
void encontrarMalezas(int mapa[N][M], queue<coordenada> &malezas);
int main() {
	queue<Barrera> barreras; 
	int mapa[N][M];
	cargarMapa(mapa);
	encontrarBarreras(mapa, barreras);
	Filtro filtro;
	filtro.impre();
	cout<<"-----------------------------------" << endl;
	filtro.desplazar();
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
void encontrarMalezas(int mapa[N][M], queue<coordenada>& malezas){
	Filtro	matrizFiltro;


}
