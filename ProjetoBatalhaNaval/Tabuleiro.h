#pragma once

#include "Uteis.cpp"
#include "Jogador.h"

constexpr int linha{ 10 };
constexpr int coluna{ 10 };

class Tabuleiro
{
public:
	void setTabuleiro( const int posX, const int posY, int val);

	int getTabuleiro(int x, int y);
	
	void mostrarTabuleiroAdversario(Tabuleiro& tabuleiro);

	void mostrarProprioTabuleiro(Tabuleiro& tabuleiro);

	void iniciarTabuleiro(Tabuleiro& tabuleiro, Jogador& jogador);

	bool posicionarNavio(Tabuleiro& tabuleiro, int posX, int posY, std::string tipoNavio, int orientacao);

	int jogo(Tabuleiro& tabuleiro1, Tabuleiro& tabuleiro2, Jogador& jogador1, Jogador& jogador2);

	void posicionarFrota(Tabuleiro& tabuleiro, Jogador& jogador);

	bool verificarVitoria(Tabuleiro& tabuleiro);

	bool atirar(Jogador& atirador, Tabuleiro& alvo);

private:
	
	int tabuleiro[linha][coluna]{ -1 };

};

