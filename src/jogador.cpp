#include "jogador.h"

// Construtor
Jogador::Jogador() {
    vida = 10;
}

// Destructor
Jogador::~Jogador(){}

// Get
int Jogador::getVida() {
    return vida;
}

void Jogador::ganhaVida() {
    if(vida < 10)
    {
        vida++;
    }
}

void Jogador::perdeVida() {
    if(vida != 0)
    {
        vida--;
    }
}

void Jogador::ganhaItem() {

    saco++;

    if(saco % 4 == 0)
    {
        ganhaVida();
    }
}

int Jogador::getItens() {
    return saco;
}