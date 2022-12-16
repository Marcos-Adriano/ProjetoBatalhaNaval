#include "Jogador.h"
#include <iostream>
#include "Uteis.cpp"

void Jogador::setEstado(Estado estado)
{
	this->estado = estado;
}

Estado Jogador::getEstado()
{
	return estado;
}

void Jogador::setNome()
{
	std::string nome;
	std::cout << "Digite seu nome:";
	std::cin >> nome;
	this->nome = nome;
}

std::string Jogador::getNome()
{
	return nome;
}