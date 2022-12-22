#pragma once

#include <vector>
#include <map>
#include <string>

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
	int getTamanho();
	void setTamanho(int tamanho);
	TIPO_NAVIO getTipo();
	void setTipo(TIPO_NAVIO tipo);

private:

	// Vector para armazenar as coordenadas no navio
	std::vector<std::pair<int, int>> posicoes;

	bool destruido;
	// Tipo do navio que determina o tamanho
	TIPO_NAVIO tipo;
	// Tamanho do navio para determinar até onde o vector irá crescer
	int tamanho;
};

