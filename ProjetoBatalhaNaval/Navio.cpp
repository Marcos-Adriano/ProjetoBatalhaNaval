#include "Navio.h"

int Navio::getTamanho()
{
	return tamanho;
}

void Navio::setTamanho(int tamanho)
{
	this->tamanho = tamanho;
}

TIPO_NAVIO Navio::getTipo()
{
	return tipo;
}

void Navio::setTipo(TIPO_NAVIO tipo)
{
	this->tipo = tipo;
}
