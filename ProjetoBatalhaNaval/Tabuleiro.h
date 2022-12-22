#pragma once

#include "Uteis.h"
#include "Jogador.h"

constexpr int linha{ 10 };
constexpr int coluna{ 10 };

class Tabuleiro
{
public:

	void setTabuleiro( const int posX, const int posY, int val);

	int getTabuleiro(int x, int y);
	
	void mostrarTabuleiroAdversario(Tabuleiro& adversario, SOCKET& socket);

	void mostrarProprioTabuleiro(Tabuleiro& proprio, SOCKET& socket);

	void iniciarTabuleiro(Tabuleiro& tabuleiro, Jogador& jogador);

	bool posicionarNavio(Tabuleiro& tabuleiro, int posX, int posY, std::string tipoNavio, int orientacao, SOCKET& socket);

	bool jogo(Tabuleiro& tabuleiro1, Tabuleiro& tabuleiro2, Jogador& jogador1, Jogador& jogador2, SOCKET& socket1, SOCKET& socket2);

	void posicionarFrota(Jogador& jogador, Tabuleiro& tabuleiro, SOCKET& socket);

	bool verificarVitoria(Tabuleiro& tabuleiro);

	bool atirar(Jogador& atirador, Tabuleiro& alvo, SOCKET& socket);

	//Mapa para armazenar o tamanho dos navios 
	std::map<const std::string, const int> tamanhoNavios =
	{
		{"Submarino", 2},
		{"Contratorpedeiro", 3},
		{"Navio-Tanque", 4},
		{"Porta-Avião", 5}
	};

private:
	// Aqui está o tabuleiro de cada jogador 10x10
	int tabuleiro[linha][coluna]{ -1 };

};

