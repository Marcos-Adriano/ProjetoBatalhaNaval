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

	// Concatena todo o vector em uma string com separação de um " " (espaço) e retorna a string 'codificada'
	std::string codificaComando(std::vector<int>& comandos)
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

	// Decodifica uma string para vector
	std::vector<int> decodificaComando(std::string& comandos)
	{
		std::vector<int> comandosFinais;

		std::stringstream comandosIniciais(comandos.c_str());

		int i;
		// Lê um inteiro i a partir da string comandosIniciais usando o operador de extração ">>"
		// Lê cada inteiro de "comandosIniciais" até que não haja mais inteiros para ler
		while (comandosIniciais >> i)
		{
			// Coloca todos os elementos num vector
			comandosFinais.push_back(i);
		}

		return comandosFinais;
	}

	// Função que transforma uma stringStream em array de char para melhor leitura no código
	char* mensagemParaArrayChar(std::stringstream& stringStream)
	{
		char buffer[sizeof(stringStream)];
		stringStream.get(buffer, sizeof(buffer));
		return buffer;
	}
}
