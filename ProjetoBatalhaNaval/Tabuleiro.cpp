#include "Tabuleiro.h"

#include <iostream>

#include "Jogador.h"

//Mapa para armazenar o tamanho dos navios 
std::map<const std::string, const int> navios =
{
	{"Submarino", 2},
	{"Contratorpedeiro", 3},
	{"Navio-Tanque", 4},
	{"Porta-Avião", 5}
};

void Tabuleiro::setTabuleiro( const int posX, const int posY, int val)
{
	tabuleiro[posX][posY] = val;
}

int Tabuleiro::getTabuleiro(int x, int y)
{
	return tabuleiro[x][y];
}

// Função que mostra o tabuleiro do jogador adversário
void Tabuleiro::mostrarTabuleiroAdversario(Tabuleiro& tabuleiro)
{
	std::cout << "    TABULEIRO DO ADVERSÁRIO:\n";
	std::cout << "   A  B  C  D  E  F  G  H  I  J \n";

	for (int x = 0; x < 10; x++)
	{
		std::cout << x + 1 << "  ";
		for (int y = 0; y < 10; y++)
		{
			if (tabuleiro.getTabuleiro(x, y) == -1)
			{					  // Mar 
				std::cout << "~  ";
			}
			else if (tabuleiro.getTabuleiro(x, y) == 0)
			{					  // Tiro errado 
				std::cout << "O  ";
			}
			else if (tabuleiro.getTabuleiro(x, y) == 1)
			{					  // Tiro certo
				std::cout << "X  ";
			}
			else // Aqui são os valores 2, 3, 4 ou 5 que representam barcos ocupando a posição
			{	 // Como o jogador não pode saber a localização, ira mostrar um '~' como se fosse o mar
				std::cout << "~  ";
			}
		}
		std::cout << '\n';
	}
	std::cout << "\n";
}

// Função que mostra o tabuleiro do próprio jogador
void Tabuleiro::mostrarProprioTabuleiro(Tabuleiro& tabuleiro)
{
	std::cout << "\t SEU TABULEIRO:\n";
	//std::cout << "   A  B  C  D  E  F  G  H  I  J \n";
	std::cout << "   1  2  3  4  5  6  7  8  9  10 \n";
	for (int x = 0; x < 10; x++)
	{
		std::cout << x + 1 << "  ";
		for (int y = 0; y < 10; y++)
		{
			if (tabuleiro.getTabuleiro(x, y) == -1)
			{					  // Mar
				std::cout << "~  ";
			}
			else if (tabuleiro.getTabuleiro(x, y) == 0)
			{					  // Tiro errado
				std::cout << "O  ";
			}
			else if (tabuleiro.getTabuleiro(x, y) == 1)
			{					  // Tiro certo
				std::cout << "X  ";
			}
			else  // Aqui são os valores 2, 3, 4 ou 5 que representam barcos ocupando a posição
			{     // Para o jogador saber onde estão os próprios barcos, vai aparecer na tela
				std::cout << tabuleiro.getTabuleiro(x, y) << "  ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

// Inicia ou limpa todo o tabuleiro com -1 para indicar mar (posição vazia)
void Tabuleiro::iniciarTabuleiro(Tabuleiro& tabuleiro, Jogador& jogador)
{
	for (int x = 0; x < linha; x++)
	{
		for (int y = 0; y < coluna; y++)
		{
			tabuleiro.setTabuleiro( x, y, -1);
		}
	}
	// Inicializando o estado do jogador como jogando
	jogador.setEstado(JOGANDO);
}

// Função para posicionar os navios no tabuleiro 
// Retorna true se os navios foram posicionados com sucesso 
// Retorna false caso contrário 
bool Tabuleiro::posicionarNavio(Tabuleiro& tabuleiro, int posX, int posY, std::string tipoNavio, int orientacao)
{
	// Obtendo o tamanho do navio
	int tamNavio = navios[tipoNavio]; 

	// Verificando se o navio pode ser posicionado
	if (orientacao == 0)
	{
		// Verificando se o navio cabe na linha
		if (posY + tamNavio > linha)
		{
			std::cout << "Este navio não cabe nesta linha!\n";
			return false;
		}

		// Verificando se os espaços estão livres
		for (int i = 0; i < tamNavio; i++)
		{
			if (tabuleiro.getTabuleiro(posX, posY + i) != -1)
			{
				std::cout << "Esta posição já está ocupada!\n";
				return false;
			}
		}

		// Posicionando o navio na linha
		for (int i = 0; i < tamNavio; i++)
		{
			tabuleiro.setTabuleiro(posX, (posY + i), tamNavio);
		}
		// Retornando true para indicar que os navios foram posicionados com sucesso
		return true;
	}

	else if (orientacao == 1)
	{
		// Verificando se o navio cabe na coluna
		if (posX + tamNavio > coluna)
		{
			std::cout << "Este navio não cabe nesta coluna!\n";
			return false;
		}

		// Verificando se os espaços estão livres
		for (int i = 0; i < tamNavio; i++)
		{
			if (tabuleiro.getTabuleiro(posX + i, posY) != -1)
			{
				std::cout << "Esta posição já está ocupada!\n";
				return false;
			}
		}

		// Posicionando o navio na coluna 
		for (int i = 0; i < tamNavio; i++)
		{
			tabuleiro.setTabuleiro((posX + i), posY, tamNavio);
		}
		// Retornando true para indicar que os navios foram posicionados com sucesso 
		return true;
	}
	else
	{
		std::cout << "Orientação errada. Escolha 0 para horizontal e 1 para vertical!\n";
		return false;
	}
}

// Função para atirar nos navios do outro jogador 
bool Tabuleiro::atirar(Jogador& atirador, Tabuleiro& alvo)
{
	// Escolhendo as coordenadas 
	int posX, posY;
	std::cout << atirador.getNome() << " digite as coordenadas do tiro: \n";
	std::cout << "Linha: ";
	std::cin >> posX;
	std::cout << "Coluna: ";
	std::cin >> posY;

	// Verificando se o tiro acertou 
	if (alvo.getTabuleiro(posX,posY) == 2 || alvo.getTabuleiro(posX, posY) == 3 || alvo.getTabuleiro(posX, posY) == 4 || alvo.getTabuleiro(posX, posY) == 5)
	{
		std::cout << "ACERTOOOUUU!!!\nPra cima deles!!\n";
		alvo.setTabuleiro(posX, posY, 1);
		alvo.mostrarTabuleiroAdversario(alvo);
		return true;
	}
	else if ((alvo.getTabuleiro(posX, posY) == 0 || alvo.getTabuleiro(posX, posY) == 1) && (posX < 9 || posY < 9))
	{
		std::cout << "Você já atirou nesse local. Tente outras coordenadas!\n";
		atirar(atirador, alvo);
	}
	else if (alvo.getTabuleiro(posX, posY) == -1)
	{
		std::cout << "EERRROOOOU!!!\nMelhore a mira ;)\n";
		alvo.setTabuleiro(posX, posY, 0);
		alvo.mostrarTabuleiroAdversario(alvo);
		return false;
	}
	else
	{
		std::cout << "Posição inválida. Tente outras coordenadas!\n";
		atirar(atirador, alvo);
	}
	return false; // Pro compilador não reclamar
}

// Função que procura no tabuleiro do adversário se ainda tem navios se não tiver o jogador venceu
bool Tabuleiro::verificarVitoria(Tabuleiro& tabuleiro)
{
	// Percorrendo o tabuleiro 
	for (int x = 0; x < linha; x++)
	{
		for (int y = 0; y < coluna; y++)
		{
			// Verificando se ainda há navios não afundados 
			if (tabuleiro.getTabuleiro(x, y) != -1 && tabuleiro.getTabuleiro(x, y) != 0 && tabuleiro.getTabuleiro(x, y) != 1)
			{
				return false;
			}
		}
	}
	// Retornando 1 para indicar que o jogador venceu 
	return true;
}

void Tabuleiro::posicionarFrota(Tabuleiro& tabuleiro, Jogador& jogador)
{
	std::cout << "Jogador " << jogador.getNome() << ", posicione os seus navios:\n";
	for (int i = 0; i < jogador.submarinos; i++)
	{
		tabuleiro.mostrarProprioTabuleiro(tabuleiro);

		int posX, posY, orientacao;
		std::cout << "Submarino: " << i + 1 << ":\n";
		std::cout << "Linha: ";
		std::cin >> posX;
		std::cout << "Coluna: ";
		std::cin >> posY;
		std::cout << "Orientação (0 para horizontal e 1 para vertical): ";
		std::cin >> orientacao;
		if (!posicionarNavio(tabuleiro, posX, posY, "Submarino", orientacao))
		{
			std::cout << "Posição inválida!\n";
			i--;
		}
	}
	for (int i = 0; i < jogador.contraTorpedos; i++)
	{
		tabuleiro.mostrarProprioTabuleiro(tabuleiro);
		int posX, posY, orientacao;
		std::cout << "ContraTorpedo: " << i + 1 << ":" << std::endl;
		std::cout << "Linha: ";
		std::cin >> posX;
		std::cout << "Coluna: ";
		std::cin >> posY;
		std::cout << "Orientação (0 para horizontal e 1 para vertical): ";
		std::cin >> orientacao;
		if (!posicionarNavio(tabuleiro, posX, posY, "Contratorpedo", orientacao))
		{
			std::cout << "Posição inválida!\n";
			i--;
		}
	}
	for (int i = 0; i < jogador.naviosTanque; i++)
	{
		tabuleiro.mostrarProprioTabuleiro(tabuleiro);
		int posX, posY, orientacao;
		std::cout << "Navio-Tanque: " << i + 1 << ":" << std::endl;
		std::cout << "Linha: ";
		std::cin >> posX;
		std::cout << "Coluna: ";
		std::cin >> posY;
		std::cout << "Orientação (0 para horizontal e 1 para vertical): ";
		std::cin >> orientacao;
		if (!posicionarNavio(tabuleiro, posX, posY, "Navio-Tanque", orientacao))
		{
			std::cout << "Posição inválida!\n";
			i--;
		}
	}
	for (int i = 0; i < jogador.portaAvioes; i++)
	{
		tabuleiro.mostrarProprioTabuleiro(tabuleiro);
		int posX, posY, orientacao;
		std::cout << "Porta-avião: " << i + 1 << ":\n";
		std::cout << "Linha: ";
		std::cin >> posX;
		std::cout << "Coluna: ";
		std::cin >> posY;
		std::cout << "Orientação (0 para horizontal e 1 para vertical): ";
		std::cin >> orientacao;
		if (!posicionarNavio(tabuleiro, posX, posY, "Porta-Avião", orientacao))
		{
			std::cout << "Posição inválida!\n";
			i--;
		}
	}
	tabuleiro.mostrarProprioTabuleiro(tabuleiro);
}

int Tabuleiro::jogo(Tabuleiro& tabuleiro1, Tabuleiro& tabuleiro2, Jogador& jogador1, Jogador& jogador2)
{
	while (jogador1.getEstado() == JOGANDO && jogador2.getEstado() == JOGANDO)
	{
		if (atirar(jogador1, tabuleiro2))
		{
			if (verificarVitoria(tabuleiro2))
			{
				jogador1.setEstado(VENCEDOR) ;
				jogador2.setEstado(DERROTADO);
				std::cout << "PARABÉNS " << jogador1.getNome() << " VOCÊ GANHOU O JOGO!!!!\n";
				return 1;
			}
		}
		if (atirar(jogador2, tabuleiro1))
		{
			if (verificarVitoria(tabuleiro1))
			{
				jogador2.setEstado(VENCEDOR);
				jogador1.setEstado(DERROTADO);
				std::cout << "PARABÉNS " << jogador2.getNome() << " VOCÊ GANHOU O JOGO!!!!\n";
				return 1;
			}
		}
	}
	return 1;
}