#include "Tabuleiro.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <thread>
#include <mutex>

#include "Jogador.h"

void Tabuleiro::setTabuleiro( const int posX, const int posY, int val)
{
	tabuleiro[posX][posY] = val;
}

int Tabuleiro::getTabuleiro(int x, int y)
{
	return tabuleiro[x][y];
}

// Função que mostra o tabuleiro do jogador adversário
void Tabuleiro::mostrarTabuleiroAdversario(Tabuleiro& adversario, SOCKET& envia)
{
	std::stringstream tabuleiro;
	std::string string;
	tabuleiro << "    TABULEIRO DO ADVERSÁRIO:\n";
	tabuleiro << "    A  B  C  D  E  F  G  H  I  J \n";
	for (int x = 0; x < 10; x++)
	{
		if (x < 9)
		{
			tabuleiro << " " << x + 1 << "  ";
		}
		else
		{
			tabuleiro << x + 1 << "  ";
		}
		for (int y = 0; y < 10; y++)
		{
			if (adversario.getTabuleiro(x, y) == -1)
			{					  // Mar 
				tabuleiro << "~  ";
			}
			else if (adversario.getTabuleiro(x, y) == 0)
			{					  // Tiro errado 
				tabuleiro << "O  ";
			}
			else if (adversario.getTabuleiro(x, y) == 1)
			{					  // Tiro certo
				tabuleiro << "X  ";
			}
			else // Aqui são os valores 2, 3, 4 ou 5 que representam barcos ocupando a posição
			{	 // Como o jogador não pode saber a localização, ira mostrar um '~' como se fosse o mar
				tabuleiro << "~  ";
			}
		}
		tabuleiro << '\n';
	}
	string = tabuleiro.str();
	send(envia, string.c_str(), 1024, 0);
	tabuleiro.str("");
	tabuleiro.clear();
}

// Função que mostra o tabuleiro do próprio jogador
void Tabuleiro::mostrarProprioTabuleiro(Tabuleiro& proprio, SOCKET& envia)
{
	std::stringstream tabuleiro;
	std::string string;
	tabuleiro << "         SEU TABULEIRO:\n";
	tabuleiro << "    A  B  C  D  E  F  G  H  I  J \n";
	//tabuleiro << "    1  2  3  4  5  6  7  8  9  10 \n";
	for (int x = 0; x < 10; x++)
	{
		if (x < 9)
		{
			tabuleiro << " " << x + 1 << "  ";
		}
		else
		{
			tabuleiro << x + 1 << "  ";
		}
		for (int y = 0; y < 10; y++)
		{
			if (proprio.getTabuleiro(x, y) == -1)
			{					  // Mar
				tabuleiro << "~  ";
			}
			else if (proprio.getTabuleiro(x, y) == 0)
			{					  // Tiro errado
				tabuleiro << "O  ";
			}
			else if (proprio.getTabuleiro(x, y) == 1)
			{					  // Tiro certo
				tabuleiro << "X  ";
			}
			else  // Aqui são os valores 2, 3, 4 ou 5 que representam barcos ocupando a posição
			{     // Para o jogador saber onde estão os próprios barcos, vai aparecer na tela
				tabuleiro << proprio.getTabuleiro(x, y) << "  ";
			}
		}
		tabuleiro << "\n";
	}
	string = tabuleiro.str();
	send(envia, string.c_str(), 1024, 0);
	tabuleiro.str("");
	tabuleiro.clear();
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
bool Tabuleiro::posicionarNavio(Tabuleiro& tabuleiro, int posX, int posY, std::string tipoNavio, int orientacao, SOCKET& socket)
{
	char buffer[1024];
	//responsavel por arrumar a posicao desejada
	posX--;

	// Obtendo o tamanho do navio
	int tamNavio = tabuleiro.tamanhoNavios[tipoNavio];

	// Verificando se o navio pode ser posicionado
	if (orientacao == 0)
	{
		// Verificando se o navio cabe na linha
		if (posY + tamNavio > linha)
		{
			strcpy_s(buffer, "Este navio não cabe nesta linha!");
			send(socket, buffer, sizeof(buffer), 0);
			return false;
		}

		// Verificando se os espaços estão livres
		for (int i = 0; i < tamNavio; i++)
		{
			if (tabuleiro.getTabuleiro(posX, posY + i) != -1)
			{
				
				strcpy_s(buffer, "Esta posição já está ocupada!");
				send(socket, buffer, sizeof(buffer), 0);
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
			strcpy_s(buffer, "Este navio não cabe nesta coluna!\n");
			send(socket, buffer, sizeof(buffer), 0);
			return false;
		}

		// Verificando se os espaços estão livres
		for (int i = 0; i < tamNavio; i++)
		{
			if (tabuleiro.getTabuleiro(posX + i, posY) != -1)
			{
				strcpy_s(buffer, "Esta posição já está ocupada!");
				send(socket, buffer, sizeof(buffer), 0);
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
		strcpy_s(buffer, "Orientação errada. Escolha 0 para horizontal e 1 para vertical!\n");
		send(socket, buffer, sizeof(buffer), 0);
		return false;
	}
}

// Função para atirar nos navios do outro jogador 
bool Tabuleiro::atirar(Jogador& atirador, Tabuleiro& alvo, SOCKET& socket)
{
	std::stringstream mensagem;
	std::string string;
	char buffer[1024]{};
	// Escolhendo as coordenadas 
	int posX, posY;

	mensagem << atirador.getNome() << " digite as coordenadas do tiro: \n";
	string = mensagem.str();
	mensagem.str("");
	mensagem.clear();
	send(socket, string.c_str(), 256, 0);

	
	strcpy_s(buffer, "Linha: de 1 a 10");
	send(socket, buffer, sizeof(buffer), 0);

	recv(socket, buffer, 256, 0);
	posX = atoi(buffer);

	strcpy_s(buffer, "Coluna: de A a J");
	send(socket, buffer, sizeof(buffer), 0);

	recv(socket, buffer, 256, 0);
	string = buffer;
	posY = dirHorizontal[Uteis::ToLower(string)];


	// Verificando se o tiro acertou 
	if (alvo.getTabuleiro(posX,posY) == 2 || alvo.getTabuleiro(posX, posY) == 3 || alvo.getTabuleiro(posX, posY) == 4 || alvo.getTabuleiro(posX, posY) == 5)
	{
		
		strcpy_s(buffer, "ACERTOOOUUU!!!\nPra cima deles!!");
		send(socket,buffer, sizeof(buffer), 0);
		alvo.setTabuleiro(posX, posY, 1);
		alvo.mostrarTabuleiroAdversario(alvo, socket);
		return true;
	}
	else if ((alvo.getTabuleiro(posX, posY) == 0 || alvo.getTabuleiro(posX, posY) == 1) && (posX < 9 || posY < 9))
	{
		
		strcpy_s(buffer, "Você já atirou nesse local. Tente outras coordenadas!");

		send(socket, buffer, sizeof(buffer), 0);
		atirar(atirador, alvo, socket);
		return false;
	}
	else if (alvo.getTabuleiro(posX, posY) == -1)
	{
		
		strcpy_s(buffer, "EERRROOOOU!!!\nMelhore a mira");
		send(socket, buffer, sizeof(buffer), 0);
		alvo.setTabuleiro(posX, posY, 0);
		alvo.mostrarTabuleiroAdversario(alvo, socket);
		return false;
	}
	else
	{
		
		strcpy_s(buffer, "Posição inválida. Tente outras coordenadas!");
		send(socket, buffer, sizeof(buffer), 0);
		atirar(atirador, alvo, socket);
		return false;
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

void Tabuleiro::posicionarFrota(Jogador& jogador, Tabuleiro& tabuleiro, SOCKET& socket)
{	
	std::stringstream mensagem;
	char buffer[1024];
	std::string string;

	//envia mensagens quando não é possivel mandar por uma simples string e sim com stringstream
	mensagem << "Jogador " << jogador.getNome() << ", posicione os seus navios:";// preenche o fluxo
	string = "jogador" + jogador.getNome();
	string = mensagem.str();// armazena em string
	mensagem.str(""); //limpa a o conteudo da mensagem
	mensagem.clear(); //reseta seus ponteiros de inicio e fim
	send(socket, string.c_str(), sizeof(string.c_str()), 0);// manda como array de char

	for (int i = 0; i < jogador.qtdSubmarinos; i++)
	{
		mostrarProprioTabuleiro(tabuleiro, socket);
		int posX, posY, orientacao;

		mensagem << "Submarino [" << i + 1 << "] Tamanho:2";
		string = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, string.c_str(), sizeof(string.c_str()), 0);

		strcpy_s(buffer, "Linha: de 1 a 10");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		posX = atoi(buffer);

		strcpy_s(buffer, "Coluna: de A a J");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		string = buffer;
		//obtendo a posicao correta pela digitada
		//usando o map dirHorizontal
		posY = dirHorizontal[Uteis::ToLower(string)];

		strcpy_s(buffer, "Orientação (0 para horizontal e 1 para vertical): ");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		orientacao = atoi(buffer);

		if (!posicionarNavio(tabuleiro, posX+1, posY, "Submarino", orientacao, socket))
		{
			strcpy_s(buffer, "Posição inválida!");
			send(socket, buffer, sizeof(buffer), 0);
			i--;
		}
	}
	for (int i = 0; i < jogador.qtdContraTorpedos; i++)
	{
		mostrarProprioTabuleiro(tabuleiro, socket);
		int posX, posY, orientacao;

		mensagem << "Contratorpedo [" << i + 1 << "] Tamanho:3";
		string = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, string.c_str(), sizeof(string.c_str()), 0);

		strcpy_s(buffer, "Linha: de 1 a 10");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		posX = atoi(buffer);

		strcpy_s(buffer, "Coluna: de A a J");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		string = buffer;
		posY = dirHorizontal[Uteis::ToLower(string)];

		strcpy_s(buffer, "Orientação (0 para horizontal e 1 para vertical): ");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		orientacao = atoi(buffer);

		if (!posicionarNavio(tabuleiro, posX, posY, "Contratorpedo", orientacao, socket))
		{
			strcpy_s(buffer, "Posição inválida!");
			send(socket, buffer, sizeof(buffer), 0);
			i--;
		}
	}
	for (int i = 0; i < jogador.qtdNaviosTanque; i++)
	{
		mostrarProprioTabuleiro(tabuleiro, socket);
		int posX, posY, orientacao;

		mensagem << "Navio-Tanque [" << i + 1 << "] Tamanho:4";
		string = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, string.c_str(), sizeof(string.c_str()), 0);

		strcpy_s(buffer, "Linha: de 1 a 10");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		posX = atoi(buffer);

		strcpy_s(buffer, "Coluna: de A a J");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		string = buffer;
		posY = dirHorizontal[Uteis::ToLower(string)];

		strcpy_s(buffer, "Orientação (0 para horizontal e 1 para vertical): ");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		orientacao = atoi(buffer);

		if (!posicionarNavio(tabuleiro, posX, posY, "Navio-Tanque", orientacao, socket))
		{
			strcpy_s(buffer, "Posição inválida!");
			send(socket, buffer, sizeof(buffer), 0);
			i--;
		}
	}
	for (int i = 0; i < jogador.qtdPortaAvioes; i++)
	{
		mostrarProprioTabuleiro(tabuleiro, socket);
		int posX, posY, orientacao;

		mensagem << "Porta-avião [" << i + 1 << "] Tamanho:5";
		string = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, string.c_str(), sizeof(string.c_str()), 0);

		strcpy_s(buffer, "Linha: de 1 a 10");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		posX = atoi(buffer);

		strcpy_s(buffer, "Coluna: de A a J");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		string = buffer;
		posY = dirHorizontal[Uteis::ToLower(string)];

		strcpy_s(buffer, "Orientação (0 para horizontal e 1 para vertical): ");
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 256, 0);
		orientacao = atoi(buffer);

		if (!posicionarNavio(tabuleiro, posX, posY, "Porta-avião", orientacao, socket))
		{
			strcpy_s(buffer, "Posição inválida!");
			send(socket, buffer, sizeof(buffer), 0);
			i--;
		}
	}
	mostrarProprioTabuleiro(tabuleiro, socket);
}

bool Tabuleiro::jogo(Tabuleiro& tabuleiro1, Tabuleiro& tabuleiro2, Jogador& jogador1, Jogador& jogador2, SOCKET& socket1, SOCKET& socket2)
{
	std::stringstream mensagem;
	std::string string;
	while (jogador1.getEstado() == JOGANDO && jogador2.getEstado() == JOGANDO)
	{

		if (atirar(jogador1, tabuleiro2, socket1))
		{
			if (verificarVitoria(tabuleiro2))
			{
				jogador1.setEstado(VENCEDOR);
				jogador2.setEstado(DERROTADO);
				
				mensagem << "PARABÉNS " << jogador1.getNome() << " VOCÊ GANHOU O JOGO!!!!\n";
				string = mensagem.str();
				mensagem.str("");
				mensagem.clear();
				send(socket1, string.c_str(), sizeof(string.c_str()), 0);
				return false;
			}
		}

		if (atirar(jogador2, tabuleiro1, socket2))
		{
			if (verificarVitoria(tabuleiro1))
			{
				jogador1.setEstado(DERROTADO);
				jogador2.setEstado(VENCEDOR);
				
				mensagem << "PARABÉNS " << jogador2.getNome() << " VOCÊ GANHOU O JOGO!!!!\n";
				string = mensagem.str();
				mensagem.str("");
				mensagem.clear();
				send(socket2, string.c_str(), sizeof(string.c_str()), 0);
				return false;
			}
		}
		return false;
	}
	return true;
}