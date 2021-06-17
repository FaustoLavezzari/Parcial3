#pragma once
#include "Estrcuturas.h"
#include <cstdlib>
#include <iostream>
#include <bitset>
#include <queue>
#define N 30
#define M 30

using namespace std;

class Filtro {
private:
bool chequearMaleza(int mapa[N][M]) {
		Filtro aux = *this&mapa;
		return aux == *this;
	}
void borrar(coordenada posicion, int matriz[N][M]) {
	for (int i = posicion.y - 1; i <= posicion.y + 1; i++) {
		for (int j = posicion.x - 1; j <= posicion.x + 1; j++) {
			matriz[i][j] = 0;
		}
	}
}

public:
	bitset<M> matriz[N];
	Filtro() { setearFiltro(0); };
    
	queue<coordenada> buscarMaleza(int mapa[N][M]) {
		queue<coordenada> malezas;
		coordenada comienzo;
		comienzo.x = 0;
		comienzo.y = 0;
		malezas.emplace(comienzo);
		for (int i = 0; i <= N-3; i++) {
			for (int j = M - 1; j >= 3; j--) {
				if (chequearMaleza(mapa)){
					coordenada posicionMaleza;
					posicionMaleza.x =M-j ;
					posicionMaleza.y =i+1 ;
					borrar(posicionMaleza, mapa);
					malezas.emplace(posicionMaleza);
				}
				*this = *this >> 1;
			}
			if (i != N-3) {
				setearFiltro(i + 1);	
			}
		}
		return malezas;
	}

	void impre() {
		for (int i = 0; i < N; i++) {
			cout << endl;
			for (int j = M-1; j >= 0; j--) {
				cout << matriz[i][j] << " ";
			}
		}
		cout << endl;
	}

    void setearFiltro(int n) {
		for (int k = 0; k < N; k++) {
			matriz[k].reset();
		}

		for (int i = n; i <n+3; i++) {
			for (int j = M-1; j > M - 4; j--) {
				this->matriz[i][j] = 1;
			}
		}
	}

    friend Filtro operator >>(Filtro c1,int n) {
		for (int i = 0; i < N; i++)
			c1.matriz[i] >>= n;
		return c1;
	}

	friend Filtro operator &(Filtro c1, int c2[N][M]) {
		Filtro c3;
		for(int i=0;i<N;i++){
			int k = M-1;
			for (int j= 0; j<M; j++){
				c3.matriz[i][k] = c1.matriz[i][k]&c2[i][j];
				k--;
			}
		}
		return c3;
	}

	friend bool operator ==(Filtro c1, Filtro c2) {
		for (int i = 0; i < N;i++) {
			for (int j = M - 1; j>=0 ; j--) {
				if (c1.matriz[i][j]!=c2.matriz[i][j])
					return false;
			}
		}
		return true;
	}
};

	
		

	
 


