#include "Uteis.h"
#include <iostream>
#include <algorithm>

namespace Uteis
{
	std::string ToLower(std::string str)
	{
		std::transform(std::begin(str), std::end(str), std::begin(str), [](unsigned char c) { return std::tolower(c); });

		return str;
	}

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
		static int byteCount;
		byteCount = send(sock, buffer, size, 0);
		if (byteCount == SOCKET_ERROR)
		{
			std::cerr << "Erro ao enviar dados!" << std::endl;
			return 1;
		}
		return 0;
	}

	// Concatena todo o vector em uma string com separa��o de um " " (espa�o) e retorna a string 'codificada'
	std::string codificaComando(std::vector<int>& comandos)
	{
		// Cria uma stream de string
		std::stringstream comandoInicial;
		// Percorre todo o vector com um foreach
		for (int i : comandos)
		{
			// Concatena todos os valores do vector separando por um espa�o em branco " "
			comandoInicial << i << " ";
		}
		// Transforma a stream numa string normal
		std::string comandoFinal = comandoInicial.str();

		// Retorna a string 'codificada'
		return comandoFinal;
	} 

	// Decodifica uma string para vector
	std::vector<int> decodificaComando(std::string& comandos)
	{
		std::vector<int> comandosFinais;

		std::stringstream comandosIniciais(comandos.c_str());

		int i;
		// L� um inteiro i a partir da string comandosIniciais usando o operador de extra��o ">>"
		// L� cada inteiro de "comandosIniciais" at� que n�o haja mais inteiros para ler
		while (comandosIniciais >> i)
		{
			// Coloca todos os elementos num vector
			comandosFinais.push_back(i);
		}

		return comandosFinais;
	}

	// Fun��o que transforma uma stringStream em array de char para melhor leitura no c�digo
	char* mensagemParaArrayChar(std::stringstream& stringStream)
	{
		char buffer[sizeof(stringStream)];
		stringStream.get(buffer, sizeof(buffer));
		return buffer;
	}
}
