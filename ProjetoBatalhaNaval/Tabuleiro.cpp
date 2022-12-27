#include "Tabuleiro.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <thread>
#include <mutex>

#include "Jogador.h"

void Tabuleiro::setTabuleiro( const int lin, const int col, int val)
{
	tabuleiro[lin][col] = val;
}

int Tabuleiro::getTabuleiro(int x, int y)
{
	return tabuleiro[x][y];
}

// Função que mostra o tabuleiro do jogador adversário
void Tabuleiro::mostrarTabuleiroAdversario(Tabuleiro& adversario)
{

	mensagem << "     TABULEIRO DO ADVERSÁRIO:\n";
	mensagem << "    A  B  C  D  E  F  G  H  I  J \n";
	for (int x = 0; x < 10; x++)
	{
		if (x < 9)
		{
			mensagem << " " << x + 1 << "  ";
		}
		else
		{
			mensagem << x + 1 << "  ";
		}
		for (int y = 0; y < 10; y++)
		{
			if (adversario.getTabuleiro(x, y) == -1)
			{					  // Mar 
				mensagem << "~  ";
			}
			else if (adversario.getTabuleiro(x, y) == 0)
			{					  // Tiro errado 
				mensagem << "O  ";
			}
			else if (adversario.getTabuleiro(x, y) == 1)
			{					  // Tiro certo
				mensagem << "X  ";
			}
			else // Aqui são os valores 2, 3, 4 ou 5 que representam barcos ocupando a posição
			{	 // Como o jogador não pode saber a localização, ira mostrar um '~' como se fosse o mar
				mensagem << "~  ";
			}
		}
		mensagem << '\n';
	}
	mensagem << '\n';
}

// Função que mostra o tabuleiro do próprio jogador
void Tabuleiro::mostrarProprioTabuleiro(Tabuleiro& proprio)
{
	mensagem << "         SEU TABULEIRO:\n";
	mensagem << "    A  B  C  D  E  F  G  H  I  J \n";
	//tabuleiro << "    1  2  3  4  5  6  7  8  9  10 \n";
	for (int x = 0; x < 10; x++)
	{
		if (x < 9)
		{
			mensagem << " " << x + 1 << "  ";
		}
		else
		{
			mensagem << x + 1 << "  ";
		}
		for (int y = 0; y < 10; y++)
		{
			if (proprio.getTabuleiro(x, y) == -1)
			{					  // Mar
				mensagem << "~  ";
			}
			else if (proprio.getTabuleiro(x, y) == 0)
			{					  // Tiro errado
				mensagem << "O  ";
			}
			else if (proprio.getTabuleiro(x, y) == 1)
			{					  // Tiro certo
				mensagem << "X  ";
			}
			else  // Aqui são os valores 2, 3, 4 ou 5 que representam barcos ocupando a posição
			{     // Para o jogador saber onde estão os próprios barcos, vai aparecer na tela
				mensagem << proprio.getTabuleiro(x, y) << "  ";
			}
		}
		mensagem << "\n";
	}
	mensagem << "\n";
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

//Função de preparação das tropas do jogador
void Tabuleiro::posicionarFrota(Jogador& jogador, Tabuleiro& tabuleiro, SOCKET& socket)
{	
	//envia mensagens quando não é possivel mandar por uma simples string e sim com stringstream
	mensagem << "Jogador " << jogador.getNome() << ", posicione os seus navios:\n";// preenche o fluxo

	for (int i = 0; i < jogador.qtdSubmarinos; i++)
	{
		mostrarProprioTabuleiro(tabuleiro);
		int lin, col, orientacao;

		mensagem << "Submarino [" << i + 1 << "] Tamanho:2\n";
		mensagem << "Linha (de 1 a 10): ";
		strAux = mensagem.str();// armazena como string
		mensagem.str(""); //limpa a o conteudo da mensagem
		mensagem.clear(); //reseta seus ponteiros de inicio e fim
		send(socket, strAux.c_str(), 1024, 0);// manda como array de char

		recv(socket, buffer, 1024, 0);
		lin = atoi(buffer);

		mensagem << "Coluna (de A a J): ";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		recv(socket, buffer, 1024, 0);
		strAux = buffer;
		//obtendo a posicao correta pela digitada
		//usando o map dirHorizontal
		col = dirHorizontal[Uteis::ToLower(strAux)];

		mensagem << "Orientação (0 para horizontal e 1 para vertical): ";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		recv(socket, buffer, 1024, 0);
		orientacao = atoi(buffer);

		if (!posicionarNavio(tabuleiro, lin+1, col, "Submarino", orientacao, socket))
		{
			mensagem << "Posição inválida, tente novamente!\n";

			i--;
		}
	}
	for (int i = 0; i < jogador.qtdContraTorpedos; i++)
	{
		mostrarProprioTabuleiro(tabuleiro);
		int lin, col, orientacao;

		mensagem << "Contratorpedo [" << i + 1 << "] Tamanho:3\n";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		mensagem << "Linha: de 1 a 10";
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 1024, 0);
		lin = atoi(buffer);

		mensagem << "Coluna: de A a J";
		send(socket, buffer, sizeof(buffer), 0);

		recv(socket, buffer, 1024, 0);
		strAux = buffer;
		col = dirHorizontal[Uteis::ToLower(strAux)];

		mensagem << "Orientação (0 para horizontal e 1 para vertical): ";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		recv(socket, buffer, 1024, 0);
		orientacao = atoi(buffer);

		if (!posicionarNavio(tabuleiro, lin, col, "Contratorpedo", orientacao, socket))
		{
			mensagem << "Posição inválida, tente novamente!\n";
			i--;
		}
	}
	for (int i = 0; i < jogador.qtdNaviosTanque; i++)
	{
		mostrarProprioTabuleiro(tabuleiro);
		int lin, col, orientacao;

		mensagem << "Navio-Tanque [" << i + 1 << "] Tamanho:4\n";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		mensagem << "Linha: de 1 a 10";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		recv(socket, buffer, 1024, 0);
		lin = atoi(buffer);

		mensagem << "Coluna: de A a J";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		recv(socket, buffer, 1024, 0);
		strAux = buffer;
		col = dirHorizontal[Uteis::ToLower(strAux)];

		mensagem << "Orientação (0 para horizontal e 1 para vertical): ";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		recv(socket, buffer, 1024, 0);
		orientacao = atoi(buffer);

		if (!posicionarNavio(tabuleiro, lin, col, "Navio-Tanque", orientacao, socket))
		{
			mensagem << "Posição inválida, tente novamente!\n";
			i--;
		}
	}
	for (int i = 0; i < jogador.qtdPortaAvioes; i++)
	{
		mostrarProprioTabuleiro(tabuleiro);
		int lin, col, orientacao;

		mensagem << "Porta-avião [" << i + 1 << "] Tamanho:5";

		mensagem << "Linha: de 1 a 10";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);
		recv(socket, buffer, 1024, 0);
		lin = atoi(buffer);

		mensagem << "Coluna: de A a J";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		recv(socket, buffer, 1024, 0);
		strAux = buffer;
		col = dirHorizontal[Uteis::ToLower(strAux)];

		mensagem << "Orientação (0 para horizontal e 1 para vertical): ";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		recv(socket, buffer, 1024, 0);
		orientacao = atoi(buffer);

		if (!posicionarNavio(tabuleiro, lin, col, "Porta-avião", orientacao, socket))
		{
			mensagem << "Posição inválida, tente novamente!\n";
			i--;
		}
	}
	mensagem << "sair";
	strAux = mensagem.str();
	mensagem.str("");
	mensagem.clear();
	send(socket, strAux.c_str(), 1024, 0);

	mostrarProprioTabuleiro(tabuleiro);
	strAux = mensagem.str();
	mensagem.str("");
	mensagem.clear();
	send(socket, strAux.c_str(), 1024, 0);
}

// Função para posicionar os navios no tabuleiro 
// Retorna true se os navios foram posicionados com sucesso 
// Retorna false caso contrário 
bool Tabuleiro::posicionarNavio(Tabuleiro& tabuleiro, int lin, int col, std::string tipoNavio, int orientacao, SOCKET& socket)
{	
	//responsavel por arrumar a posicao desejada
	lin -= 2;

	// Obtendo o tamanho do navio
	int tamNavio = tabuleiro.tamanhoNavios[tipoNavio];

	// Verificando se o navio pode ser posicionado
	if (orientacao == 0)
	{
		// Verificando se o navio cabe na linha
		if (col + tamNavio > coluna)
		{
			mensagem << "Este navio não cabe nesta linha!\n";
			return false;
		}

		// Verificando se os espaços estão livres
		for (int i = 0; i < tamNavio; i++)
		{        
			// i = 0 é a propria posição, e de acordo com o tamanho do navio verifica as posições seguintes 
			if (tabuleiro.getTabuleiro(lin, col + i) != -1)
			{
				mensagem << "Esta posição já está ocupada!\n";
				return false;
			}
		}

		// Posicionando o navio na linha
		for (int i = 0; i < tamNavio; i++)
		{
			tabuleiro.setTabuleiro(lin, (col + i), tamNavio);
		}
		// Retornando true para indicar que os navios foram posicionados com sucesso
		return true;
	}

	else if (orientacao == 1)
	{
		// Verificando se o navio cabe na coluna
		if (lin + tamNavio > linha)
		{
			mensagem << "Este navio não cabe nesta coluna!\n";
			return false;
		}

		// Verificando se os espaços estão livres
		for (int i = 0; i < tamNavio; i++)
		{
			if (tabuleiro.getTabuleiro(lin + i, col) != -1)
			{
				mensagem << "Esta posição já está ocupada!";
				return false;
			}
		}

		// Posicionando o navio na coluna 
		for (int i = 0; i < tamNavio; i++)
		{
			tabuleiro.setTabuleiro((lin + i), col, tamNavio);
		}
		// Retornando true para indicar que os navios foram posicionados com sucesso
		return true;
	}
	else
	{
		mensagem << "Orientação errada. Escolha 0 para horizontal e 1 para vertical!\n";
		return false;
	}
}

// Função que procura no tabuleiro do adversário se ainda tem navios, se não tiver o jogador venceu
bool Tabuleiro::verificarVitoria(Tabuleiro& tabuleiro)
{
	// Percorrendo o tabuleiro 
	for (int x = 0; x < linha; x++)
	{
		for (int y = 0; y < coluna; y++)
		{
			// Verificando se ainda há navios não afundados 
			if (tabuleiro.getTabuleiro(x, y) == 2 || tabuleiro.getTabuleiro(x, y) == 3 || tabuleiro.getTabuleiro(x, y) == 4 || tabuleiro.getTabuleiro(x, y) == 5)
			{
				return false;
			}
		}
	}
	// Retornando true para indicar que o jogador venceu 
	return true;
}

// Função para atirar nos navios do outro jogador (função recursiva até o jogador colocar coordenadas válidas)
bool Tabuleiro::atirar(Jogador& atirador, Tabuleiro& alvo, SOCKET& socket, SOCKET& socket2)
{
	// Escolhendo as coordenadas
	int lin, col;

	mensagem << "Sua vez " << atirador.getNome() << ", digite as coordenadas do tiro: \n";
	mensagem << "Linha (de 1 a 10): ";
	strAux = mensagem.str();
	mensagem.str("");
	mensagem.clear();
	send(socket, strAux.c_str(), 1024, 0);

	recv(socket, buffer, 1024, 0);
	lin = atoi(buffer)-1;

	mensagem << "Coluna (de A a J): ";
	strAux = mensagem.str();
	mensagem.str("");
	mensagem.clear();
	send(socket, strAux.c_str(), 1024, 0);

	recv(socket, buffer, 1024, 0);
	strAux = buffer;
	col = dirHorizontal[Uteis::ToLower(strAux)];

	// Verificando se o tiro acertou 
	if (alvo.getTabuleiro(lin,col) == 2 || alvo.getTabuleiro(lin, col) == 3 || alvo.getTabuleiro(lin, col) == 4 || alvo.getTabuleiro(lin, col) == 5)
	{
		// Troca o valor para 1 para mostrar que acertou
		alvo.setTabuleiro(lin, col, 1);
		mensagem << "valido";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		if (verificarVitoria(alvo))
		{
			mensagem << "sair";
			strAux = mensagem.str();
			mensagem.str("");
			mensagem.clear();
			send(socket, strAux.c_str(), 1024, 0);
		}
		mensagem << "ACERTOOOUUU!!!\nPra cima deles!!\n";
		alvo.mostrarTabuleiroAdversario(alvo);
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		return true;
	}
	else if ((alvo.getTabuleiro(lin, col) == 0 || alvo.getTabuleiro(lin, col) == 1) && lin < linha && col < coluna)
	{
		mensagem << "Você já atirou nesse local. Tente outras coordenadas!\n";
		atirar(atirador, alvo, socket, socket2);
		return false;
	}
	else if (alvo.getTabuleiro(lin, col) == -1 && lin < linha && col < coluna)
	{
		mensagem << "valido";
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);

		mensagem << "EERRROOOOU!!!\nMelhore a mira ;)\n";
		alvo.setTabuleiro(lin, col, 0);
		alvo.mostrarTabuleiroAdversario(alvo);
		strAux = mensagem.str();
		mensagem.str("");
		mensagem.clear();
		send(socket, strAux.c_str(), 1024, 0);
		return false;
	}
	else
	{
		mensagem << "Posição inválida. Tente outras coordenadas!\n";
		atirar(atirador, alvo, socket, socket2);
		return false;
	}
}

//Função do jogo em si
void Tabuleiro::jogo(Tabuleiro& tabuleiro1, Tabuleiro& tabuleiro2, Jogador& jogador1, Jogador& jogador2, SOCKET& socket1, SOCKET& socket2)
{
	while (jogador1.getEstado() == JOGANDO && jogador2.getEstado() == JOGANDO)
	{
		//turno do jogador 1
		if (atirar(jogador1, tabuleiro2, socket1, socket2))
		{
			if (verificarVitoria(tabuleiro2))
			{
				jogador1.setEstado(VENCEDOR);
				jogador2.setEstado(DERROTADO);
				
				mensagem << "PARABÉNS " << jogador1.getNome() << " VOCÊ GANHOU O JOGO!!!!\n";
				strAux = mensagem.str();
				mensagem.str("");
				mensagem.clear();
				send(socket1, strAux.c_str(), 1024, 0);

				mensagem << "Que pena " << jogador2.getNome() << ", você perdeu!\n";
				strAux = mensagem.str();
				mensagem.str("");
				mensagem.clear();
				send(socket2, strAux.c_str(), 1024, 0);
				closesocket(socket1);
				closesocket(socket2);
				return;
			}
		}

		//turno do jogador 2
		if (atirar(jogador2, tabuleiro1, socket2, socket1))
		{
			if (verificarVitoria(tabuleiro1))
			{
				jogador1.setEstado(DERROTADO);
				jogador2.setEstado(VENCEDOR);
				
				mensagem << "PARABÉNS " << jogador2.getNome() << " VOCÊ GANHOU O JOGO!!!!\n";
				strAux = mensagem.str();
				mensagem.str("");
				mensagem.clear();
				send(socket2, strAux.c_str(), 1024, 0);

				mensagem << "Que pena " << jogador1.getNome() << ", você perdeu!\n";
				strAux = mensagem.str();
				mensagem.str("");
				mensagem.clear();
				send(socket1, strAux.c_str(), 1024, 0);
				closesocket(socket1);
				closesocket(socket2);
				return;
			}
		}
	}
}
