#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <tchar.h>

#pragma comment (lib, "Ws2_32.lib")

SOCKET clientSocket = INVALID_SOCKET;
char buffer[1024];
constexpr int port = 55555;
int byteCount;

int recebeDados(SOCKET sock, char* buffer, int size)
{
	static int byteCount;
	byteCount = recv(sock, buffer, size, 0);
	if (byteCount == SOCKET_ERROR)
	{
		std::cerr << "Erro ao receber dados!" << std::endl;
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
		std::cerr << "Erro ao enviar dados!" << std::endl;
		return 1;
	}
	return 0;
}

// Concatena todo o vector em uma string com separação de um " " (espaço) e retorna a string 'codificada'
std::string codificaComando(std::vector<int> comandos)
{
	// Cria uma stream de string
	std::stringstream comandoInicial;
	// Percorre todo o vector com um foreach
	for (int i : comandos)
	{
		// Concatena todos os valores do vector separando por um espaço em branco " "
		comandoInicial << i << " ";
	}
	// Transforma a stream numa string normal
	std::string comandoFinal = comandoInicial.str();

	// Retorna a string 'codificada'
	return comandoFinal;
}

// Decodifica uma string para um vector de inteiros
std::vector<int> decodificaComando(std::string comandos)
{
	std::vector<int> comandosFinais;

	std::stringstream comandosIniciais(comandos.c_str());

	int i;
	// Lê um inteiro i a partir da string comandosIniciais usando o operador de extração ">>"
	// Lê cada inteiro de "comandosIniciais" até que não haja mais inteiros para ler
	while (comandosIniciais >> i)
	{
		comandosFinais.push_back(i);
	}

	return comandosFinais;
}

void conectarAoServidor()
{
	std::cout << "======== Bem vindo ao nosso jogo de batalha naval! =========\n";
	//Inicializando Winsock
	WSADATA wsaData;
	int wsaerr = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaerr != 0)
	{
		std::cout << "The winsock dll not found!\n";
		return;
	}

	// Criando o socket do cliente
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket():" << WSAGetLastError() << '\n';
		WSACleanup();
		return;
	}

	// Endereço
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		std::cout << "Client: connect() - Failed to connect." << '\n';
		WSACleanup();
		return;
	}
	else
	{
		std::cout << "Conectado ao servidor com sucesso!\n";
	}
	std::cout << "Esperando o servidor completar as conexões...\n";
}

void definirNome()
{
	recv(clientSocket, buffer, 1024, 0);
	std::cout << buffer;

	std::cin >> buffer;
	std::cin.clear();

	send(clientSocket, buffer, 1024, 0);

	std::cout << "Nome definido!\n";
}

bool preparacao()
{
	recv(clientSocket, buffer, 1024, 0);
	if (strcmp(buffer, "sair") == 0)
	{
		recv(clientSocket, buffer, 1024, 0);
		std::cout << buffer;
		std::cout << "Aguardando sua vez...\n";
		return false;
	}
	std::cout << buffer;

	std::cin >> buffer;
	send(clientSocket, buffer, 1024, 0);
	return true;
}

bool jogo()
{
	recv(clientSocket, buffer, 1024, 0);
	if (strcmp(buffer, "valido") == 0)
	{
		recv(clientSocket, buffer, 1024, 0);
		if (strcmp(buffer, "sair") == 0)
		{
			recv(clientSocket, buffer, 1024, 0);
			std::cout << buffer;

			recv(clientSocket, buffer, 1024, 0);
			std::cout << buffer;

			std::cout << "Obrigado por jogar nosso jogo <3";
			return false;
		}
		std::cout << buffer;
		recv(clientSocket, buffer, 1024, 0);
	}
	std::cout << buffer;

	std::cin >> buffer;
	send(clientSocket, buffer, 1024, 0);
	return true;
}

int main()
{
	setlocale(LC_ALL, "portuguese");
	conectarAoServidor();

	definirNome();
	while (preparacao());
	while (jogo());

	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
