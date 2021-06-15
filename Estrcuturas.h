#pragma once

struct coordenada
{
	int x;
	int y;
};


struct Barrera{
	coordenada comienzo;
	coordenada final;
};

struct Arista {
	coordenada v1;
	coordenada v2;
	float distancia;
};