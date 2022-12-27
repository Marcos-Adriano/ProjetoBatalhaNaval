#include <iostream>
#include <map>
#include <WS2tcpip.h>
#include <thread>
#include <mutex>

#include "Uteis.h"
#include "Jogador.h"
#include "Tabuleiro.h"
#include "Navio.h"

#pragma comment(lib, "ws2_32.lib")

Jogador jogador[maxJogadores];
Tabuleiro tabuleiro[maxJogadores];
//inicializa o mutex
static std::mutex Mutex;

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
	servidorSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servidorSocket == INVALID_SOCKET)
	{
		std::cerr << "Nao foi possivel criar o socket do servidor. Erro #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	//Bind: Preencher os dados do servidor
	sockaddr_in servidorEndereco{};
	servidorEndereco.sin_family = AF_INET;
	servidorEndereco.sin_addr.S_un.S_addr = INADDR_ANY;
	servidorEndereco.sin_port = htons(port);

	//Bind: Conectando o socket ao endereço
	wsOk = bind(servidorSocket, (sockaddr*)&servidorEndereco, sizeof(servidorEndereco));
	if (wsOk == SOCKET_ERROR)
	{
		std::cerr << "Falha ao associar o socket: " << WSAGetLastError() << std::endl;
		closesocket(servidorSocket);
		WSACleanup();
		return;
	}

	//Listen esperando o pedido dos clientes para se conectarem
	wsOk = listen(servidorSocket, maxJogadores);

	if (wsOk == SOCKET_ERROR)
	{
		std::cerr << "Erro ao entrar em modo de espera de conexões: " << WSAGetLastError() << std::endl;
		closesocket(servidorSocket);
		WSACleanup();
		return;
	}
	std::cout << "Esperando os jogadores se conectarem..." << std::endl;
}

// Função em loop que aceita os jogadores
void conectarJogadores()
{
	while (clientesAtivos < maxJogadores)
	{
		// Aceitando o socket dos jogadores
		sockaddr_in jogadorEndereco;
		int jogadorEnderecoSize = sizeof(jogadorEndereco);
		ClientSocket[clientesAtivos] = accept(servidorSocket, (SOCKADDR*)&jogadorEndereco, &jogadorEnderecoSize);
		if (ClientSocket[clientesAtivos] == INVALID_SOCKET)
		{
			std::cout << "Accept falhou:" << WSAGetLastError() << std::endl;
			closesocket(servidorSocket);
			WSACleanup();
			return;
		}
		std::cout << "Jogador " << ++clientesAtivos << " conectado com sucesso!" << std::endl;

	}
	std::cout << "Todos os jogadores já se conectaram!\n";
	
}

//preparação individual de cada jogador
void prepararJogo(int id)
{
	tabuleiro[id].iniciarTabuleiro(tabuleiro[id], jogador[id]);
	jogador[id].setNome(ClientSocket[id]);
	std::cout << jogador[id].getNome()<< " está posicionando suas tropas..." << std::endl;
	tabuleiro[id].posicionarFrota(jogador[id], tabuleiro[id], ClientSocket[id]);
	std::cout << jogador[id].getNome()<< " preparado(a)!" << std::endl;
}

//criação das threads que possibilita ambos os jogadores se prepararem ao mesmo tempo
void criaThreads()
{
	for (int id = 0; id < maxJogadores; id++)
	{
		threadJogador[id] = std::thread(prepararJogo, id);
	}
}

void esperaThreads()
{
	for (int id = 0; id < maxJogadores; id++)
	{
		threadJogador[id].join();
	}
}

void fecharConexoes()
{
	static int byteCount;
	while (true)
	{
		for (int i = 0; i < maxJogadores; i++)
		{
			if (byteCount = recv(ClientSocket[i], buffer, 1024, 0) == 0)
			{
				closesocket(ClientSocket[i]);
				return;
			}
		}
	}
}

int main()
{
	// Configurando para português
	setlocale(LC_ALL, "portuguese");

	///Criando o servidor
	criarServidor();

	//Espera a conexão de dois jogadores para prosseguir
	conectarJogadores();

	criaThreads();

	esperaThreads();

	// Aqui o jogo em si começa a rodar
	tabuleiro[0].jogo(tabuleiro[0], tabuleiro[1], jogador[0], jogador[1], ClientSocket[0], ClientSocket[1]);
	
	//fecharConexoes();
	closesocket(servidorSocket);
	WSACleanup(); 
	std::cout << "O jogo terminou!\n";
	return 0;
}
