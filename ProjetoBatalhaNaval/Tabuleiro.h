#pragma once

#include "Uteis.h"
#include "Jogador.h"

constexpr int linha{ 10 };
constexpr int coluna{ 10 };
static std::stringstream mensagem;
static std::string strAux;
static char buffer[1024];

class Tabuleiro
{
public:

	void setTabuleiro( const int lin, const int col, int val);

	int getTabuleiro(int x, int y);
	
	void mostrarTabuleiroAdversario(Tabuleiro& adversario);

	void mostrarProprioTabuleiro(Tabuleiro& proprio);

	void iniciarTabuleiro(Tabuleiro& tabuleiro, Jogador& jogador);

	bool posicionarNavio(Tabuleiro& tabuleiro, int lin, int col, std::string tipoNavio, int orientacao, SOCKET& socket);

	void jogo(Tabuleiro& tabuleiro1, Tabuleiro& tabuleiro2, Jogador& jogador1, Jogador& jogador2, SOCKET& socket1, SOCKET& socket2);

	void posicionarFrota(Jogador& jogador, Tabuleiro& tabuleiro, SOCKET& socket);

	bool verificarVitoria(Tabuleiro& tabuleiro);

	bool atirar(Jogador& atirador, Tabuleiro& alvo, SOCKET& socket, SOCKET& socket2);

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
