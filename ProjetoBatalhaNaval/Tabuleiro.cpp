#include "Tabuleiro.h"

#include <iostream>

#include "Jogador.h"

//Mapa para armazenar o tamanho dos navios 
std::map<const std::string, const int> navios =
{
	{"Submarino", 2},
	{"Contratorpedeiro", 3},
	{"Navio-Tanque", 4},
	{"Porta-Avi�o", 5}
};

void Tabuleiro::setTabuleiro( const int posX, const int posY, int val)
{
	tabuleiro[posX][posY] = val;
}

int Tabuleiro::getTabuleiro(int x, int y)
{
	return tabuleiro[x][y];
}

// Fun��o que mostra o tabuleiro do jogador advers�rio
void Tabuleiro::mostrarTabuleiroAdversario(Tabuleiro& tabuleiro)
{
	std::cout << "    TABULEIRO DO ADVERS�RIO:\n";
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
			else // Aqui s�o os valores 2, 3, 4 ou 5 que representam barcos ocupando a posi��o
			{	 // Como o jogador n�o pode saber a localiza��o, ira mostrar um '~' como se fosse o mar
				std::cout << "~  ";
			}
		}
		std::cout << '\n';
	}
	std::cout << "\n";
}

// Fun��o que mostra o tabuleiro do pr�prio jogador
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
			else  // Aqui s�o os valores 2, 3, 4 ou 5 que representam barcos ocupando a posi��o
			{     // Para o jogador saber onde est�o os pr�prios barcos, vai aparecer na tela
				std::cout << tabuleiro.getTabuleiro(x, y) << "  ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

// Inicia ou limpa todo o tabuleiro com -1 para indicar mar (posi��o vazia)
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

// Fun��o para posicionar os navios no tabuleiro 
// Retorna true se os navios foram posicionados com sucesso 
// Retorna false caso contr�rio 
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
			std::cout << "Este navio n�o cabe nesta linha!\n";
			return false;
		}

		// Verificando se os espa�os est�o livres
		for (int i = 0; i < tamNavio; i++)
		{
			if (tabuleiro.getTabuleiro(posX, posY + i) != -1)
			{
				std::cout << "Esta posi��o j� est� ocupada!\n";
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
			std::cout << "Este navio n�o cabe nesta coluna!\n";
			return false;
		}

		// Verificando se os espa�os est�o livres
		for (int i = 0; i < tamNavio; i++)
		{
			if (tabuleiro.getTabuleiro(posX + i, posY) != -1)
			{
				std::cout << "Esta posi��o j� est� ocupada!\n";
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
		std::cout << "Orienta��o errada. Escolha 0 para horizontal e 1 para vertical!\n";
		return false;
	}
}

// Fun��o para atirar nos navios do outro jogador 
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
		std::cout << "Voc� j� atirou nesse local. Tente outras coordenadas!\n";
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
		std::cout << "Posi��o inv�lida. Tente outras coordenadas!\n";
		atirar(atirador, alvo);
	}
	return false; // Pro compilador n�o reclamar
}

// Fun��o que procura no tabuleiro do advers�rio se ainda tem navios se n�o tiver o jogador venceu
bool Tabuleiro::verificarVitoria(Tabuleiro& tabuleiro)
{
	// Percorrendo o tabuleiro 
	for (int x = 0; x < linha; x++)
	{
		for (int y = 0; y < coluna; y++)
		{
			// Verificando se ainda h� navios n�o afundados 
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
		std::cout << "Orienta��o (0 para horizontal e 1 para vertical): ";
		std::cin >> orientacao;
		if (!posicionarNavio(tabuleiro, posX, posY, "Submarino", orientacao))
		{
			std::cout << "Posi��o inv�lida!\n";
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
		std::cout << "Orienta��o (0 para horizontal e 1 para vertical): ";
		std::cin >> orientacao;
		if (!posicionarNavio(tabuleiro, posX, posY, "Contratorpedo", orientacao))
		{
			std::cout << "Posi��o inv�lida!\n";
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
		std::cout << "Orienta��o (0 para horizontal e 1 para vertical): ";
		std::cin >> orientacao;
		if (!posicionarNavio(tabuleiro, posX, posY, "Navio-Tanque", orientacao))
		{
			std::cout << "Posi��o inv�lida!\n";
			i--;
		}
	}
	for (int i = 0; i < jogador.portaAvioes; i++)
	{
		tabuleiro.mostrarProprioTabuleiro(tabuleiro);
		int posX, posY, orientacao;
		std::cout << "Porta-avi�o: " << i + 1 << ":\n";
		std::cout << "Linha: ";
		std::cin >> posX;
		std::cout << "Coluna: ";
		std::cin >> posY;
		std::cout << "Orienta��o (0 para horizontal e 1 para vertical): ";
		std::cin >> orientacao;
		if (!posicionarNavio(tabuleiro, posX, posY, "Porta-Avi�o", orientacao))
		{
			std::cout << "Posi��o inv�lida!\n";
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
				std::cout << "PARAB�NS " << jogador1.getNome() << " VOC� GANHOU O JOGO!!!!\n";
				return 1;
			}
		}
		if (atirar(jogador2, tabuleiro1))
		{
			if (verificarVitoria(tabuleiro1))
			{
				jogador2.setEstado(VENCEDOR);
				jogador1.setEstado(DERROTADO);
				std::cout << "PARAB�NS " << jogador2.getNome() << " VOC� GANHOU O JOGO!!!!\n";
				return 1;
			}
		}
	}
	return 1;
}