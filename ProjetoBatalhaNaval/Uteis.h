#pragma once

#include <sstream>
#include <vector>
#include <WinSock2.h>
#include <thread>

static constexpr unsigned short port{ 55555 };
static constexpr int maxJogadores{ 2 };

static int clientesAtivos{ 0 };
static SOCKET ClientSocket[maxJogadores]{}; 

static std::thread threadJogador[maxJogadores]{};

static SOCKET servidorSocket{};

namespace Uteis
{
    std::string ToLower(std::string str);

    int recebeDados(SOCKET sock, char* buffer, int size);

    int enviaDados(SOCKET sock, char* buffer, int size);

    std::string codificaComando(std::vector<int>& comandos);

    std::vector<int> decodificaComando(std::string& comandos);

    char* mensagemParaArrayChar(std::stringstream& stringStream);

}
