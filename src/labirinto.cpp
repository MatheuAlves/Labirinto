#include "labirinto.h"

// Construtor
Labirinto::Labirinto() {}

// Destrutor
Labirinto::~Labirinto() {}

// Abre o arquivo e salva em matrizes
void Labirinto::abreArquivo()
{
    // Abre o arquivo
    ifstream arquivo("dataset/input.data");
    if (!arquivo.is_open())
    {
        cout << "Não foi possível abrir o arquivo." << endl;
    }

    // Pegando tamanho da matriz
    string primeiraLinha;

    arquivo >> primeiraLinha;
    arquivo >> primeiraLinha;
    tamanho = stoi(primeiraLinha);
    arquivo >> primeiraLinha;
    qtd_matrizes = stoi(primeiraLinha);
    qtd_posicoes = tamanho * tamanho * qtd_matrizes;

    this-> matriz.resize(tamanho);
    this-> matriz_visitados.resize(tamanho);
    for (int i = 0; i < tamanho; i++)
    {
        this-> matriz[i].resize(tamanho);
        this-> matriz_visitados[i].resize(tamanho);
    }
    
    // Lê as matrizes do arquivo e as salva em arquivos separados
    int numMatrizes = 0;
    while (!arquivo.eof())
    {
        // Lê a matriz do arquivo
        vector<vector<string>> matriz(tamanho, vector<string>(tamanho));
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = 0; j < tamanho; j++)
            {
                if (!(arquivo >> matriz[i][j])) // Finaliza loop de leitura
                {
                    cout << "Li todas matrizes." << endl;
                    arquivo.close();
                    return;
                }
            }
        }

        // Salva a matriz em um arquivo separado
        string nomeArquivo = "dataset/matriz_" + to_string(numMatrizes) + ".txt";
        string nomeArquivoBool = "dataset/bool_" + to_string(numMatrizes) + ".txt";

        ofstream arquivoMatriz(nomeArquivo);
        ofstream arquivoMatrizBool(nomeArquivoBool);

        if (!arquivoMatriz.is_open() && !arquivoMatrizBool.is_open())
        {
            cout << "Não foi possível criar o arquivo " << nomeArquivo << endl;
        }

        for (int i = 0; i < tamanho; i++)
        {
            for (int j = 0; j < tamanho; j++)
            {
                arquivoMatriz << matriz[i][j] << "\t";
                arquivoMatrizBool << 0 << "\t";
            }
            arquivoMatriz << endl;
            arquivoMatrizBool << endl;
        }
        arquivoMatriz.close();
        arquivoMatrizBool.close();
        numMatrizes++;
    }
    arquivo.close();
}

// Função para imprimir a matriz
void Labirinto::imprimirLabirinto()
{
    for (int k = 0; k < qtd_matrizes; k++) {
        ifstream arquivo("dataset/matriz_" + to_string(k) + ".txt");
        string elemento;
        cout << "Matriz " << k << ":" << endl;
        for (int i = 0; i < tamanho; i++) {
            for (int j = 0; j < tamanho; j++) {
                arquivo >> elemento;
                cout << elemento << "\t"; // imprime o elemento (i,j) da matriz
            }
            cout << endl;
        }
        cout << endl;
        arquivo.close();
    }
}

// Função para imprimir a matriz bool
void Labirinto::imprimirCaminho()
{
    for (int k = 0; k < qtd_matrizes; k++) {
        ifstream arquivo("dataset/bool_" + to_string(k) + ".txt");
        string elemento;
        cout << "Bool " << k << ":" << endl;
        for (int i = 0; i < tamanho; i++) {
            for (int j = 0; j < tamanho; j++) {
                arquivo >> elemento;
                cout << elemento << "\t"; // imprime o elemento (i,j) da matriz
            }
            cout << endl;
        }
        cout << endl;
        arquivo.close();
    }
}

// função para randomizar i e j
pair<int, int> Labirinto::randomizaPosição(int i, int j){
    random_device rd;           // usado para obter um seed inicial aleatório
    mt19937 rng(rd());         // gerador de números aleatórios (Mersenne Twister)
    int escolha; // gera um número aleatório entre 0 e 2
    int aux_i = i;
    int aux_j = j;
    int num = tamanho-1;
    uniform_int_distribution<int> dist(0, tamanho-1); // distribuidor de inteiros entre 0 e tamanho
    uniform_int_distribution<int> dist1(0, 7); // distribuidor de inteiros entre 0 e 7

    if (i == num || i == 0 || j == num || j == 0) // Valor aleatório para entrar na nova matriz
    {
        // aleatoriza i
        escolha = dist(rng);
        aux_i = escolha;

        // aleatoriza j
        escolha = dist(rng);
        aux_j = escolha;

        return make_pair(aux_i, aux_j);
    }
    else
    {
        // Randomiza case
        escolha = dist1(rng);

        switch(escolha) {
            case 0: // Incremento em i
                if (i < tamanho-1) { // Verifica se é possível incrementar i
                    aux_i++;
                }
                break;
            case 1: // Decremento em i
                if (i > 0) { // Verifica se é possível decrementar i
                    aux_i--;
                }
                break;
            case 2: // Incremento em j
                if (j < tamanho-1) { // Verifica se é possível decrementar j
                    aux_j++;
                }
                break;
            case 3: // Decremento em j
                if (j > 0) { // Verifica se é possível decrementar j
                    aux_j--;
                }
                break;
            case 4: // Incremento em i e Incremento em j
                if (i < tamanho-1 && j < tamanho-1) { // Verifica se é possível decrementar j
                    aux_i++;
                    aux_j++;
                }
                break;
            case 5: // Incremento em i e Decremento em j
                if (i < tamanho-1 && j > 0) { // Verifica se é possível decrementar j
                    aux_i++;
                    aux_j--;
                }
                break;
            case 6: // Decremento em i e Incremento em j
                if (i > 0 && j < tamanho-1) { // Verifica se é possível decrementar j
                    aux_i--;
                    aux_j++;
                }
                break;
            case 7: // Decremento em i e Decremento em j
                if (i > 0 && j > 0) { // Verifica se é possível decrementar j
                    aux_i--;
                    aux_j--;
                }
                break;
        }
        return make_pair(aux_i, aux_j);
    }
}

// Função para começar o jogo
pair<int, int> Labirinto::comecarLabirinto(){
    pair<int,int> posicao = {0,0};

    qtd_caminho = 0;
    qtd_perigos = 0;
    caminhoZerado = true;
    passouMatrizes = 0;
    //Carrega Matriz
    carregaMatriz(0);

    do
    {
        posicao = randomizaPosição(posicao.first,posicao.second);

    } while (matriz[posicao.first][posicao.second] == "#");// Enquanto não for #

    if (matriz_visitados[posicao.first][posicao.second] != 1)
    {
        qtd_caminho++;
    }
    
    matriz_visitados[posicao.first][posicao.second] = 1;

    cout<< "Começou o jogo:"        << endl;
    cout << "Posição:"<<posicao.first<<","<< posicao.second     << endl;
    cout << "Elemento:"<<matriz[posicao.first][posicao.second]  << endl;

    posicaoInicial.first  = posicao.first;
    posicaoInicial.second = posicao.second;

    return posicao;
}

// Função para caminhar pela matriz
tuple<int, int, int> Labirinto::caminharLabirinto(int i, int j, int k)
{
    pair<int,int> posicao = {i,j};

    if (matriz_visitados[posicao.first][posicao.second] != 1)
    {
        qtd_caminho++;
    }
    matriz_visitados[posicao.first][posicao.second] = 1;

    if (matriz[posicao.first][posicao.second] != "*")
    {
        if (matriz[posicao.first][posicao.second] != "0")
        {
            J.ganhaItem();
            matriz[posicao.first][posicao.second] = to_string(stoi(matriz[posicao.first][posicao.second])-1);
            caminhoZerado = false;
        }
    }
    else
    {
        J.perdeVida();
        qtd_perigos++;
    }
    
    // Aleatorizar i e j
    if (i == 0 || j == 0 || i == tamanho-1 || j == tamanho-1)
    {
        //Muda a matriz linearmente
        passouMatrizes++;
        //Salva Matriz
        salvaMatriz(k);

        if (k == qtd_matrizes-1)
        {
            k = 0;
        }
        else
        {
            k++;
        }
        
        //Carrega Matriz;
        carregaMatriz(k);
        
        // Recebe um i e j aleatório
        do
        {
            posicao = randomizaPosição(posicao.first,posicao.second);

        } while (matriz[posicao.first][posicao.second] == "#");// Enquanto não for #
        
    }
    // Portal
    else
    {
        // Recebe um i e j anterior
        do
        {
            posicao = randomizaPosição(posicao.first,posicao.second);

        } while (matriz[posicao.first][posicao.second] == "#");// Enquanto não for #
    }

    cout << "\nContinua o jogo:"        <<endl;
    cout << "Matriz = "     << k     <<endl;
    cout << "Posição:"<<posicao.first<<","<<posicao.second  <<endl;
    cout << "Elemento:"<<matriz[posicao.first][posicao.second]   <<endl;

    return make_tuple(posicao.first, posicao.second, k);
}

// Get Vida
int Labirinto::getVida() {
    return J.getVida();
}

// Salvar Matriz
void Labirinto::salvaMatriz(int k){
    ofstream arquivo("dataset/matriz_" + to_string(k) + ".txt");
    ofstream arquivoBool("dataset/bool_" + to_string(k) + ".txt");
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            arquivo << matriz[i][j] << "\t";
            arquivoBool << matriz_visitados[i][j] << "\t";
        }
        arquivo << endl;
        arquivoBool << endl;
    }
    arquivo.close();
    arquivoBool.close();
}

// Carrega Matriz
void Labirinto::carregaMatriz(int k){
    ifstream arquivo("dataset/matriz_" + to_string(k) + ".txt");
    ifstream arquivoBool("dataset/bool_" + to_string(k) + ".txt");

    if (!arquivoBool.is_open())
    {
        cout << "Não foi possível abrir o arquivo." << endl;
    }

    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            arquivo >> matriz[i][j];
            arquivoBool >> matriz_visitados[i][j];
        }
    }
    arquivo.close();
    arquivoBool.close();
}

// Imprime Matriz
void Labirinto::imprimirMatriz(){

    cout << "Matriz:" << endl;
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

// Get Quantidade de Perigos
int Labirinto::getQtdPerigos(){
    return qtd_perigos;
}

// Get Posição Inicial
pair<int,int> Labirinto::getPosicaoInicial(){
    return posicaoInicial;
}

// Imprime o resultado final
void Labirinto::imprimirResultado(){

    cout << endl;
    cout << "A - " << qtd_caminho               << "\tcasas percorridas!"  << endl;
    cout << "B - " << J.getItens()              << "\titens capturados! "  << endl;
    cout << "C - " << qtd_posicoes-qtd_caminho  << "\tcasas sem percorrer!"<< endl;
    cout << "D - " << qtd_perigos               << "\tperigos enfrentados!"<< endl;
}

// Verifica se o jogo Acabou
bool Labirinto::jogoTerminou(int i, int j){

    if (i == posicaoInicial.first && j == posicaoInicial.second && passouMatrizes >= qtd_matrizes && caminhoZerado == true)
    {
        return true;
    }
    return false;
}

// Junta todos os arquivos em um só
void Labirinto::juntaArquivos(){
    
    ofstream arquivo("dataset/output.data");

    arquivo << tamanho << " ";
    arquivo << tamanho << " ";
    arquivo << qtd_matrizes << endl;

    for (int k = 0; k < qtd_matrizes; k++)
    {
        carregaMatriz(k);
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = 0; j < tamanho; j++)
            {
                arquivo << matriz[i][j] << "\t";
            }
            arquivo << endl;
        }
        arquivo << endl;
        remove(("dataset/matriz_" + to_string(k) + ".txt").c_str());
    }

    arquivo << "Matriz de Caminhos:" << endl;
    arquivo << endl;

    for (int k = 0; k < qtd_matrizes; k++)
    {
        carregaMatriz(k);
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = 0; j < tamanho; j++)
            {
                arquivo << matriz_visitados[i][j] << "\t";
            }
            arquivo << endl;
        }
        arquivo << endl;
        remove(("dataset/bool_" + to_string(k) + ".txt").c_str());
    }
    arquivo.close();
}