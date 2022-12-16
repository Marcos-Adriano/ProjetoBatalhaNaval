#pragma once

#include <map>
#include <string>

//Estado do jogador para controlar quando acaba o jogo
enum Estado
{
	JOGANDO,
	VENCEDOR,
	DERROTADO
};

class Jogador
{
public:
	
	void setEstado(Estado estado);

	Estado getEstado();

	// Quantidades de cada navio disponivel por jogador
	const int submarinos{ 1 };       //tipo-1
	const int contraTorpedos{ 0 };   //tipo-2
	const int naviosTanque{ 0 };     //tipo-3
	const int portaAvioes{ 0 };      //tipo-4

	// Nome do jogador
	void setNome();
	std::string getNome();

	//Tabuleiro tabuleiro;

	// Mapa organizar a direcao horizontal com letras 
	std::map<const char, int> dirHorizontal =
	{
		{'A', 0},
		{'B', 1},
		{'C', 2},
		{'D', 3},
		{'E', 4},
		{'F', 5},
		{'G', 6},
		{'H', 7},
		{'I', 8},
		{'J', 9}
	};

private:

	std::string nome;
	Estado estado;

};