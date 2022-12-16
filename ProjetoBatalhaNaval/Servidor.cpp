#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Uteis.h"
#include "Jogador.h"
#include "Tabuleiro.h"
#include "Navio.h"

constexpr int port = 55555;
constexpr int maxClients = 2;

int ClientSocket[maxClients];
int ActiveClients = 0;

/*
int recebeDados(SOCKET sock, char* buffer, int size)
{
    int byteCount;
    byteCount = recv(sock, buffer, size, 0);
    if (byteCount == SOCKET_ERROR)
    {
        printf("Erro ao receber dados!\n");
        return 1;
    }
    return 0;
}

int enviaDados(SOCKET sock, char* buffer, int size)
{
    int byteCount;
    byteCount = send(sock, buffer, size, 0);
    if (byteCount == SOCKET_ERROR)
    {
        printf("Erro ao enviar dados!\n");
        return 1;
    }
    return 0;
}

void criarServidor()
{
	//Inicializando Winsock
	WSADATA wsData;
	int wsOk = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (wsOk != 0)
	{
		std::cerr << "Nao foi possivel inicializar Winsock. Erro #" << wsOk;
		return;
	}

	//Criando o socket do servidor
	servidorSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (servidorSocket == INVALID_SOCKET)
	{
		std::cerr << "Nao foi possivel criar o socket do servidor. Erro #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	//Bind
	sockaddr_in servidorEndereco{};
	servidorEndereco.sin_family = AF_INET;
	servidorEndereco.sin_port = htons(54000);
	servidorEndereco.sin_addr.S_un.S_addr = INADDR_ANY;

	//Conectando o socket ao endereco
	bind(servidorSocket, (sockaddr*)&servidorEndereco, sizeof(servidorEndereco));

	//Listen
	listen(servidorSocket, SOMAXCONN);
}

void conectarJogadores()
{
	//Aceitando o socket do jogador 1
	sockaddr_in jogador1Endereco;
	int jogador1EnderecoSize = sizeof(jogador1Endereco);
	jogador1Socket = accept(servidorSocket, (sockaddr*)&jogador1Endereco, &jogador1EnderecoSize);

	//Aceitando o socket do jogador 2
	sockaddr_in jogador2Endereco;
	int jogador2EnderecoSize = sizeof(jogador2Endereco);
	jogador2Socket = accept(servidorSocket, (sockaddr*)&jogador2Endereco, &jogador2EnderecoSize);
}
*/

//class Navio
//{
//public:
//	int tam;
//	TIPO_NAVIO tipo;
//	// Vector para armazenar as coordenadas no navio
//	std::vector<std::pair<int, int>> posicoes;
//	Navio(){}
//};

//class Jogador
//{
//public:
//	std::string nome{ NULL };
//	// Quantidades de cada navio disponivel por jogador
//	const int submarinos{ 1 };       //tipo-1
//	const int contraTorpedos{ 0 };   //tipo-2
//	const int naviosTanque{ 0 };     //tipo-3
//	const int portaAvioes{ 0 };      //tipo-4
//
//	Tabuleiro tabuleiro;
//
//	Estado estado;
//	// Nome do jogador
//	void setNome()
//	{
//		std::string nome;
//		std::cout << "Digite seu nome:";
//		std::cin >> nome;
//		this->nome = nome;
//	}
//};

//class Tabuleiro : public Jogador, public Navio
//{
//public:
//	static const int linha{ 10 };
//	static const int coluna{ 10 };
//	int tabuleiro[linha][coluna]{ -1 };
//
//	Tabuleiro(){}
//
//	void setTabuleiro(Tabuleiro& tabuleiro, const int posX, const int posY, int val)
//	{
//		tabuleiro.tabuleiro[posX][posY] = val;
//	}
//
//	// Função que mostra o tabuleiro do jogador adversário
//	void mostrarTabuleiroAdversario(Tabuleiro& tabuleiro)
//	{
//		std::cout << "    TABULEIRO DO ADVERSÁRIO:\n";
//		std::cout << "   A  B  C  D  E  F  G  H  I  J \n";
//
//		for (int x = 0; x < 10; x++)
//		{
//			std::cout << x + 1 << "  ";
//			for (int y = 0; y < 10; y++)
//			{
//				if (tabuleiro.tabuleiro[x][y] == -1)
//				{					  // Mar 
//					std::cout << "~  ";
//				}
//				else if (tabuleiro.tabuleiro[x][y] == 0)
//				{					  // Tiro errado 
//					std::cout << "O  ";
//				}
//				else if (tabuleiro.tabuleiro[x][y] == 1)
//				{					  // Tiro certo
//					std::cout << "X  ";
//				}
//				else // Aqui são os valores 2, 3, 4 ou 5 que representam barcos ocupando a posição
//				{	 // Como o jogador não pode saber a localização, ira mostrar um '~' como se fosse o mar
//					std::cout << "~  ";
//				}
//			}
//			std::cout << '\n';
//		}
//		std::cout << "\n";
//	}
//
//	// Função que mostra o tabuleiro do próprio jogador
//	void mostrarProprioTabuleiro(Tabuleiro& tabuleiro)
//	{
//		std::cout << "\t SEU TABULEIRO:\n";
//		//std::cout << "   A  B  C  D  E  F  G  H  I  J \n";
//		std::cout << "   1  2  3  4  5  6  7  8  9  10 \n";
//		for (int x = 0; x < 10; x++)
//		{
//			std::cout << x + 1 << "  ";
//			for (int y = 0; y < 10; y++)
//			{
//				if (tabuleiro.tabuleiro[x][y] == -1)
//				{					  // Mar
//					std::cout << "~  ";
//				}
//				else if (tabuleiro.tabuleiro[x][y] == 0)
//				{					  // Tiro errado
//					std::cout << "O  ";
//				}
//				else if (tabuleiro.tabuleiro[x][y] == 1)
//				{					  // Tiro certo
//					std::cout << "X  ";
//				}
//				else  // Aqui são os valores 2, 3, 4 ou 5 que representam barcos ocupando a posição
//				{     // Para o jogador saber onde estão os próprios barcos, vai aparecer na tela
//					std::cout << tabuleiro.tabuleiro[x][y] << "  ";
//				}
//			}
//			std::cout << "\n";
//		}
//		std::cout << "\n";
//	}
//
//	// Inicia ou limpa todo o tabuleiro com -1 para indicar mar (posição vazia)
//	void iniciarTabuleiro(Tabuleiro& tabuleiro)
//	{
//		for (int x = 0; x < linha; x++)
//		{
//			for (int y = 0; y < coluna; y++)
//			{
//				tabuleiro.setTabuleiro(tabuleiro, x, y, -1);
//			}
//		}
//		// Inicializando o estado do jogador como jogando
//		tabuleiro.estado = JOGANDO;
//	}
//
//	// Função para posicionar os navios no tabuleiro 
//	// Retorna true se os navios foram posicionados com sucesso 
//	// Retorna false caso contrário 
//	bool posicionarNavio(Tabuleiro& tabuleiro, int posX, int posY, std::string tipoNavio, int orientacao)
//	{
//		// Obtendo o tamanho do navio
//		int tamNavio = navios[tipoNavio];
//
//		// Verificando se o navio pode ser posicionado
//		if (orientacao == 0)
//		{
//			// Verificando se o navio cabe na linha
//			if (posY + tamNavio > linha)
//			{
//				std::cout << "Este navio não cabe nesta linha!\n";
//				return false;
//			}
//
//			// Verificando se os espaços estão livres
//			for (int i = 0; i < tamNavio; i++)
//			{
//				if (tabuleiro.tabuleiro[posX][posY + i] != -1)
//				{
//					std::cout << "Esta posição já está ocupada!\n";
//					return false;
//				}
//			}
//
//			// Posicionando o navio na linha
//			for (int i = 0; i < tamNavio; i++)
//			{
//				setTabuleiro(tabuleiro, posX, (posY + i), tamNavio);
//			}
//			// Retornando true para indicar que os navios foram posicionados com sucesso
//			return true;
//		}
//
//		else if (orientacao == 1)
//		{
//			// Verificando se o navio cabe na coluna
//			if (posX + tamNavio > coluna)
//			{
//				std::cout << "Este navio não cabe nesta coluna!\n";
//				return false;
//			}
//
//			// Verificando se os espaços estão livres
//			for (int i = 0; i < tamNavio; i++)
//			{
//				if (tabuleiro.tabuleiro[posX + i][posY] != -1)
//				{
//					std::cout << "Esta posição já está ocupada!\n";
//					return false;
//				}
//			}
//
//			// Posicionando o navio na coluna 
//			for (int i = 0; i < tamNavio; i++)
//			{
//				setTabuleiro(tabuleiro, (posX + i), posY, tamNavio);
//			}
//			// Retornando true para indicar que os navios foram posicionados com sucesso 
//			return true;
//		}
//		else
//		{
//			std::cout << "Orientação errada. Escolha 0 para horizontal e 1 para vertical!\n";
//			return false;
//		}
//	}
//
//	// Função para atirar nos navios do outro jogador 
//	bool atirar(Jogador& atirador, Tabuleiro& alvo)
//	{
//		// Escolhendo as coordenadas 
//		int posX, posY;
//		std::cout << atirador.nome << " digite as coordenadas do tiro: \n";
//		std::cout << "Linha: ";
//		std::cin >> posX;
//		std::cout << "Coluna: ";
//		std::cin >> posY;
//
//		// Verificando se o tiro acertou 
//		if (alvo.tabuleiro[posX][posY] == 2 || alvo.tabuleiro[posX][posY] == 3 || alvo.tabuleiro[posX][posY] == 4 || alvo.tabuleiro[posX][posY] == 5)
//		{
//			std::cout << "ACERTOOOUUU!!!\nPra cima deles!!\n";
//			alvo.tabuleiro[posX][posY] = 1;
//			mostrarTabuleiroAdversario(alvo);
//			return true;
//		}
//		else if ((alvo.tabuleiro[posX][posY] == 0 || alvo.tabuleiro[posX][posY] == 1) && (posX < 9 || posY < 9))
//		{
//			std::cout << "Você já atirou nesse local. Tente outras coordenadas!\n";
//			atirar(atirador, alvo);
//		}
//		else if (alvo.tabuleiro[posX][posY] == -1)
//		{
//			std::cout << "EERRROOOOU!!!\nMelhore a mira ;)\n";
//			alvo.tabuleiro[posX][posY] = 0;
//			mostrarTabuleiroAdversario(alvo);
//			return false;
//		}
//		else
//		{
//			std::cout << "Posição inválida. Tente outras coordenadas!\n";
//			atirar(atirador, alvo);
//		}
//		return false; // Pro compilador não reclamar
//	}
//
//	// Função que procura no tabuleiro do adversário se ainda tem navios se não tiver o jogador venceu
//	bool verificarVitoria(Tabuleiro& tabuleiro)
//	{
//		// Percorrendo o tabuleiro 
//		for (int x = 0; x < linha; x++)
//		{
//			for (int y = 0; y < coluna; y++)
//			{
//				// Verificando se ainda há navios não afundados 
//				if (tabuleiro.tabuleiro[x][y] != -1 && tabuleiro.tabuleiro[x][y] != 0 && tabuleiro.tabuleiro[x][y] != 1)
//				{
//					return false;
//				}
//			}
//		}
//		// Retornando 1 para indicar que o jogador venceu 
//		return true;
//	}
//
//	void posicionarFrota(Tabuleiro& tabuleiro, Jogador& jogador)
//	{
//		std::cout << "Jogador " << jogador.nome << ", posicione os seus navios:\n";
//		for (int i = 0; i < tabuleiro.submarinos; i++)
//		{
//			mostrarProprioTabuleiro(tabuleiro);
//
//			int posX, posY, orientacao;
//			std::cout << "Submarino: " << i + 1 << ":\n";
//			std::cout << "Linha: ";
//			std::cin >> posX;
//			std::cout << "Coluna: ";
//			std::cin >> posY;
//			std::cout << "Orientação (0 para horizontal e 1 para vertical): ";
//			std::cin >> orientacao;
//			if (!posicionarNavio(tabuleiro, posX, posY, "Submarino", orientacao))
//			{
//				std::cout << "Posição inválida!\n";
//				i--;
//			}
//		}
//		for (int i = 0; i < tabuleiro.contraTorpedos; i++)
//		{
//			mostrarProprioTabuleiro(tabuleiro);
//			int posX, posY, orientacao;
//			std::cout << "ContraTorpedo: " << i + 1 << ":" << std::endl;
//			std::cout << "Linha: ";
//			std::cin >> posX;
//			std::cout << "Coluna: ";
//			std::cin >> posY;
//			std::cout << "Orientação (0 para horizontal e 1 para vertical): ";
//			std::cin >> orientacao;
//			if (!posicionarNavio(tabuleiro, posX, posY, "Contratorpedo", orientacao))
//			{
//				std::cout << "Posição inválida!\n";
//				i--;
//			}
//		}
//		for (int i = 0; i < tabuleiro.naviosTanque; i++)
//		{
//			mostrarProprioTabuleiro(tabuleiro);
//			int posX, posY, orientacao;
//			std::cout << "Navio-Tanque: " << i + 1 << ":" << std::endl;
//			std::cout << "Linha: ";
//			std::cin >> posX;
//			std::cout << "Coluna: ";
//			std::cin >> posY;
//			std::cout << "Orientação (0 para horizontal e 1 para vertical): ";
//			std::cin >> orientacao;
//			if (!posicionarNavio(tabuleiro, posX, posY, "Navio-Tanque", orientacao))
//			{
//				std::cout << "Posição inválida!\n";
//				i--;
//			}
//		}
//		for (int i = 0; i < tabuleiro.portaAvioes; i++)
//		{
//			mostrarProprioTabuleiro(tabuleiro);
//			int posX, posY, orientacao;
//			std::cout << "Porta-avião: " << i + 1 << ":\n";
//			std::cout << "Linha: ";
//			std::cin >> posX;
//			std::cout << "Coluna: ";
//			std::cin >> posY;
//			std::cout << "Orientação (0 para horizontal e 1 para vertical): ";
//			std::cin >> orientacao;
//			if (!posicionarNavio(tabuleiro, posX, posY, "Porta-Avião", orientacao))
//			{
//				std::cout << "Posição inválida!\n";
//				i--;
//			}
//		}
//		mostrarProprioTabuleiro(tabuleiro);
//	}
//
//	void jogo(Tabuleiro& tabuleiro1, Tabuleiro& tabuleiro2, Jogador& jogador1, Jogador& jogador2)
//	{
//		while (tabuleiro1.estado == JOGANDO && tabuleiro2.estado == JOGANDO)
//		{
//			if (atirar(jogador1, tabuleiro2))
//			{
//				if (verificarVitoria(tabuleiro2))
//				{
//					tabuleiro1.estado = VENCEDOR;
//					tabuleiro2.estado = DERROTADO;
//					std::cout << "PARABÉNS " << jogador1.nome << " VOCÊ GANHOU O JOGO!!!!\n";
//				}
//			}
//			if (atirar(jogador2, tabuleiro1))
//			{
//				if (verificarVitoria(tabuleiro1))
//				{
//					tabuleiro2.estado = VENCEDOR;
//					tabuleiro1.estado = DERROTADO;
//					std::cout << "PARABÉNS " << jogador2.nome << " VOCÊ GANHOU O JOGO!!!!\n";
//				}
//			}
//		}
//	}
//};

int main()
{
	setlocale(LC_ALL, "portuguese");
	Tabuleiro tabuleiro1;
	Tabuleiro tabuleiro2;
	Jogador jogador1;
	Jogador jogador2;
	//tabuleiro1.iniciarDirecaoHorizontal();
	//tabuleiro2.iniciarDirecaoHorizontal();

	tabuleiro1.iniciarTabuleiro(tabuleiro1, jogador1);
	tabuleiro2.iniciarTabuleiro(tabuleiro2, jogador2);

	jogador1.setNome();
	jogador2.setNome();
	tabuleiro1.posicionarFrota(tabuleiro1, jogador1);
	tabuleiro2.posicionarFrota(tabuleiro2, jogador2);
	while(tabuleiro1.jogo(tabuleiro1, tabuleiro2, jogador1, jogador2))

	return 0;
}
