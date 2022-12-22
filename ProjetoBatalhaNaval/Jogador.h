#pragma once

#include <map>
#include <string>
#include <vector>
#include <WinSock2.h>

#include "Navio.h"

//Estado do jogador para controlar quando acaba o jogo
enum Estado
{
	JOGANDO,
	VENCEDOR,
	DERROTADO
};

// Mapa organizar a direcao horizontal com letras 
static std::map<const std::string, int> dirHorizontal =
{
	{"a", 0},
	{"b", 1},
	{"c", 2},
	{"d", 3},
	{"e", 4},
	{"f", 5},
	{"g", 6},
	{"h", 7},
	{"i", 8},
	{"j", 9}
};

class Jogador
{
public:
	
	void setEstado(Estado estado);

	Estado getEstado();

	// Quantidades de cada navio disponivel por jogador
	const int qtdSubmarinos{ 3 };       //tipo-1
	const int qtdContraTorpedos{ 2 };   //tipo-2
	const int qtdNaviosTanque{ 1 };     //tipo-3
	const int qtdPortaAvioes{ 1 };      //tipo-4

	// Nome do jogador
	void setNome(SOCKET& socket);
	std::string getNome();
	std::vector<Navio> navios;

	//Tabuleiro tabuleiro;


private:

	std::string nome;
	Estado estado{};

};