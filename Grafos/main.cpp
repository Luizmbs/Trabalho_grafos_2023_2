#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void zera_matriz(int **matriz, int linha, int coluna){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            matriz[i][j] = 0;
        }
    }
}

int matriz_adjacencia(int tamanho, int **grafo, int **adjacencia, bool digrafo){
    int arestas = 0;
    if(!digrafo){
        int coluna = 1;
        for(int i = 0; i < tamanho-1; i++){
            for(int j = coluna; j < tamanho; j++ ){
                if(grafo[i][j] != 0 && grafo[i][j] != 999 ){
                    adjacencia[i][j] = adjacencia[j][i] = 1;
                    arestas++;
                } 
            }
            coluna++;
        }
    } else {
        for(int i = 0; i < tamanho; i++){
            for(int j = 0; j < tamanho; j++){
                if(grafo[i][j] != 0 && grafo[i][j] != 999){
                    adjacencia[i][j] = 1;
                    arestas++;
                } else{
                    adjacencia[i][j] = 0;
                }
            }
        }
    }
    return arestas;
}

void get_matriz_incidencia(int tamanho,int num_aresta, int **grafo, int**matriz_incidencia, bool digrafo){
    int coluna_insercao = 0;
    if(!digrafo){
        int coluna = 1;
        for(int i = 0; i < tamanho-1; i++){
            for(int j = coluna; j < tamanho; j++ ){
                if(grafo[i][j] != 0 && grafo[i][j] != 999 ){
                    matriz_incidencia[i][coluna_insercao] = matriz_incidencia[j][coluna_insercao] = 1;
                    coluna_insercao++;
                } 
            }
            coluna++;
        } 
    } else {
        for(int i = 0; i < tamanho; i++){
            for(int j = 0; j < tamanho; j++){
                if(grafo[i][j] != 0 && grafo[i][j] != 999){
                    matriz_incidencia[i][coluna_insercao] = 1;
                    matriz_incidencia[j][coluna_insercao] = -1;
                    coluna_insercao++;
                }
            }
        }
    }
}

int main() {
    
    ifstream arquivo_entrada;
    char separador = ' ';
    arquivo_entrada.open("grafo.txt");

    if(arquivo_entrada.is_open()){
        cout << "arquivo_entrada Aberto"<< endl;
    } else {
        cout << "Falha ao abrir o arquivo_entrada" << endl;
    }
    string linhas;
    string n_nos;
    string elemento;
    vector<string> linha{};

    getline(arquivo_entrada,n_nos);
    int tamanho_grafo = stoi(n_nos);
    int **matriz = new int*[tamanho_grafo];
    for(int i = 0; i < tamanho_grafo; i++){
        matriz[i]= new int[tamanho_grafo];
    }
    int contador = 0;
    n_nos.erase();

    while(getline(arquivo_entrada,linhas)){ 

        istringstream sstream(linhas);
        while(getline(sstream,elemento,separador)){
            linha.push_back(elemento);
        }

        for(int i=0; i<tamanho_grafo; i++){
            matriz[contador][i] = stoi(linha[i]);
        }
        contador++;
        linha.clear();
    }

    int **adjacencia = new int*[tamanho_grafo];
    for(int i = 0; i < tamanho_grafo; i++){
        adjacencia[i]= new int[tamanho_grafo];
    }

    zera_matriz(adjacencia,tamanho_grafo,tamanho_grafo);
    int num_aresta = matriz_adjacencia(tamanho_grafo,matriz,adjacencia,true);

    int **matriz_incidencia = new int*[tamanho_grafo];
    for(int i = 0; i < num_aresta; i++){
        matriz_incidencia[i] = new int[num_aresta];
    }
    
    zera_matriz(matriz_incidencia,tamanho_grafo,num_aresta);
    get_matriz_incidencia(tamanho_grafo,num_aresta, matriz,matriz_incidencia, true);

    for (int i = 0; i< tamanho_grafo; i++){
        for(int j = 0; j < num_aresta; j++){
            cout << matriz_incidencia[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Numero de arestas do grafo: " << num_aresta << endl;
    return 0;
} 