#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "labirinto.h"
#include "jogador.h"

using namespace std;

int main() {

    Labirinto L;
    pair<int, int> posicao;
    tuple<int, int, int> posicaoMatriz;

    //Abre o arquivo e cria os arquivos .txt de cada matriz
    L.abreArquivo();

    //imprime o labirinto
    L.imprimirLabirinto();

    //Inicia o jogo em uma casa aleatória
    posicao = L.comecarLabirinto();

    //Caminhar Labirinto
    posicaoMatriz = {posicao.first, posicao.second, 0};
    do
    {
        posicaoMatriz = L.caminharLabirinto(get<0>(posicaoMatriz),get<1>(posicaoMatriz), get<2>(posicaoMatriz));
        cout << "VIDA:" << L.getVida() << endl;
        cout << "bool:" << L.jogoTerminou(get<0>(posicaoMatriz),get<1>(posicaoMatriz)) << endl;
    } while (L.jogoTerminou(get<0>(posicaoMatriz),get<1>(posicaoMatriz)) == 0 && L.getVida() > 0);
    
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "FIM DE JOGO!" << endl;

    if (L.jogoTerminou(get<0>(posicaoMatriz),get<1>(posicaoMatriz)) == 1)
    {
        cout << "O CAMINHO NÃO TEM MAIS ITENS!" << endl;
    }
    if (L.getVida() == 0)
    {
        cout << "O JOGADOR MORREU!" << endl;
    }
    
    L.imprimirResultado();
    L.juntaArquivos();

    cout << "#########################################################" << endl;
    
    return 0;
}
