#pragma once

#include <vector>

#include "Uteis.h"

//Enum para armazenar os tipos de navios
enum TIPO_NAVIO
{
	SUBMARINO,
	CONTRATORPEDEIRO,
	NAVIOTANQUE,
	PORTAAVIOES
};

class Navio
{
public:
	int tam;
	TIPO_NAVIO tipo;
	// Vector para armazenar as coordenadas no navio
	std::vector<std::pair<int, int>> posicoes;
	Navio();
};

