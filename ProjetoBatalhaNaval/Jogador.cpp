#include <iostream>

#include "Jogador.h"
#include "Uteis.h"


void Jogador::setEstado(Estado estado)
{
	this->estado = estado;
}

Estado Jogador::getEstado()
{
	return estado;
}

void Jogador::setNome(SOCKET& socket)
{
	char buffer[1024]= "Digite seu nome: ";
	send(socket, buffer, sizeof(buffer), 0);

	recv(socket, buffer, sizeof(buffer), 0);

	this->nome = buffer;
	//this->nome.assign(buffer, sizeof(buffer));
}

std::string Jogador::getNome()
{
	return nome;
}