#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <random>
#include <string>
#include "jogador.h"
using namespace std;

class Labirinto {
    private:
        int tamanho;
        int qtd_perigos;
        int qtd_matrizes;
        int qtd_caminho;
        int qtd_posicoes;
        int passouMatrizes;
        bool caminhoZerado;
        pair<int,int>posicaoInicial;
        vector<vector<string>> matriz;
        vector<vector<int>> matriz_visitados;
        Jogador J;
    public:
        Labirinto();
        ~Labirinto();
        void abreArquivo();
        void imprimirLabirinto();
        void imprimirCaminho();
        void imprimirMatriz();
        pair<int, int> randomizaPosição(int i, int j);
        pair<int, int> comecarLabirinto();
        tuple<int, int, int> caminharLabirinto(int i, int j, int k);
        void salvaMatriz(int k);
        void carregaMatriz(int k);
        int getVida();
        int getQtdPerigos();
        pair<int, int> getPosicaoInicial();
        void imprimirResultado();
        bool jogoTerminou(int i, int j);
        void juntaArquivos();
};

#endif

