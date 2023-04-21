#ifndef JOGADOR_H
#define JOGADOR_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Jogador {
    private:
        int vida; // Variável privada que armazena a vida do jogador
        int saco; // Variável privada que armazena qtd de itens
    public:
        Jogador(); // Constructor
        ~Jogador(); // Destructor
        int getVida(); // Retorna o valor atual da vida do jogador
        int getItens(); // Retorna o valor da soma dos itens do jogador
        void ganhaVida();// Atualiza o valor da vida do jogador
        void perdeVida();// Atualiza o valor da vida do jogador
        void ganhaItem();// Atualiza o valor do item do jogador
        
    };

#endif