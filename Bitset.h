#pragma once
#include "Estrcuturas.h"
#include <cstdlib>
#include <iostream>
#include <bitset>
#define N 30
#define M 30

using namespace std;

class Filtro {
private:
	queue<coordenada> malezas;
public:
	bitset<M> matriz[N];
	Filtro() { setearFiltro(0); };
    
	queue<coordenada> buscarMaleza(int mapa[N][M]) {
		queue<coordenada> malezas;
		for (int i = 0; i <= N-3; i++) {
			for (int j = M - 1; j >= 3; j--) {
				chequearMaleza(mapa[N][M]);
				*this = *this >> 1;
			}
			if (i != N-3) {
				setearFiltro(i + 1);
			}
		}
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
};

/*void Filtro::impre(){
	for(int i=0;i<N;i++){
			cout<<endl;
		for(int j=M;j>0;j--){
			cout<<matriz[i][j]<<" ";			
		}
	}
	cout<<endl;	
}

void Filtro::setearFiltro(){
	
	for(int i=0;i<3;i++){
		for(int j=M;j>M-3;j--){
			matriz[i][j]=1;
		}
	}
	
}  

Filtro operator >>(Filtro c1, int n){
    for(int i=0;i<N;i++)
            c1.matriz[i]>>=n;
     return c1;
}
*/