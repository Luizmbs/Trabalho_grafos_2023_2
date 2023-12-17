#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>


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
                    adjacencia[i][j] = adjacencia[j][i] = grafo[i][j];
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

void get_matriz_incidencia(int tamanho,int num_aresta, int **grafo, int**matriz_incidencia,vector<vector<int>> &lista_adjacencia, bool digrafo){
    int coluna_insercao = 0;
    if(!digrafo){
        int coluna = 1;
        for(int i = 0; i < tamanho-1; i++){
            for(int j = coluna; j < tamanho; j++ ){
                if(grafo[i][j] != 0 && grafo[i][j] != 999 ){
                    matriz_incidencia[i][coluna_insercao] = matriz_incidencia[j][coluna_insercao] = 1;
                    lista_adjacencia[i].push_back(j);
                    lista_adjacencia[j].push_back(i);
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
                    lista_adjacencia[i].push_back(j);
                    coluna_insercao++;
                }
            }
        }
    }
}

void busca_largura(int **matriz_adjacencia, int numNo, int no_comeco){
    // Vetor para marcar os nós visitados
    bool* visited = new bool[numNo]();  // Inicializado com false

    // Fila para armazenar os nós a serem visitados
    std::queue<int> q;

    // Marca o nó inicial como visitado e o adiciona à fila
    visited[no_comeco] = true;
    q.push(no_comeco);

    while (!q.empty()) {
        // Obtém o nó da frente da fila
        int currentNode = q.front();
        std::cout << currentNode << " ";

        // Remove o nó da frente da fila
        q.pop();
        for (int neighbor = 0; neighbor < numNo; ++neighbor) {
            if (matriz_adjacencia[currentNode][neighbor] == 1 && !visited[neighbor]) {
                // Marca o vizinho como visitado e o adiciona à fila
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    delete[] visited;

}

void busca_profundidade(int** matriz_adjacencia, bool* visitado, int numNo, int no_atual) {
    // Marca o nó atual como visitado
    visitado[no_atual] = true;
    cout << no_atual << " ";

    // Percorre os vizinhos do nó atual
    for (int visinho = 0; visinho < numNo; ++visinho) {
        if (matriz_adjacencia[no_atual][visinho] == 1 && !visitado[visinho]) {
            // Chama a DFS recursivamente para o vizinho não visitado
            busca_profundidade(matriz_adjacencia, visitado, numNo, visinho);
        }
    }
}

void busca_profundidade_aux(int** matriz_adjacencia, int numNo, int no_comeco) {
    // Vetor para marcar os nós visitados
    bool* visitado = new bool[numNo]();  // Inicializado com false

    cout << "Busca em largura iniciado pelo no " << no_comeco << ": ";
    busca_profundidade(matriz_adjacencia, visitado, numNo, no_comeco);

    delete[] visitado;
}



struct Aresta {
    int origem;
    int destino;
    int peso;

    Aresta(int ori, int dest, int p) : origem(ori), destino(dest), peso(p) {}
};

struct CompareEdges {
    bool operator()(const Aresta& a, const Aresta& b) const {
        return a.peso > b.peso; // Min heap, menor peso tem maior prioridade
    }
};

void prim(int** adjacencia, int numNo) {
    int peso_arvore = 0;
    vector<bool> na_arvore(numNo, false);
    priority_queue<Aresta, std::vector<Aresta>, CompareEdges> pq;

    // Inclui o primeiro nó na árvore
    na_arvore[0] = true;

    // Adiciona as arestas do primeiro nó à fila de prioridade
    for (int vizinho = 0; vizinho < numNo; ++vizinho) {
        if (adjacencia[0][vizinho] != 0) {
            pq.push(Aresta(0, vizinho, adjacencia[0][vizinho]));
        }
    }

    cout << "Arestas da Árvore Geradora Mínima (Prim):\n";

    while (!pq.empty()) {
        Aresta no_atual = pq.top();
        pq.pop();

        if (na_arvore[no_atual.origem] && !na_arvore[no_atual.destino]) {
            // Aresta faz parte da árvore mínima
            cout << "Aresta: " << no_atual.origem << " - " << no_atual.destino << " Peso: " << no_atual.peso << endl;
            peso_arvore += no_atual.peso;
            na_arvore[no_atual.destino] = true;

            // Adiciona as arestas do nó recém-incluído à fila de prioridade
            for (int vizinho = 0; vizinho < numNo; ++vizinho) {
                if (adjacencia[no_atual.destino][vizinho] != 0 && !na_arvore[vizinho]) {
                    pq.push(Aresta(no_atual.destino, vizinho, adjacencia[no_atual.destino][vizinho]));
                }
            }
        }
    }
    cout << "Peso total da arvore: " << peso_arvore << endl; 
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
    int num_aresta = matriz_adjacencia(tamanho_grafo,matriz,adjacencia,false);

    prim(adjacencia,tamanho_grafo);
    //busca_largura(adjacencia,tamanho_grafo,0);

    //busca_profundidade_aux(adjacencia,tamanho_grafo,0);

    /*int **matriz_incidencia = new int*[tamanho_grafo];
    for(int i = 0; i < num_aresta; i++){
        matriz_incidencia[i] = new int[num_aresta];
    }
    
    zera_matriz(matriz_incidencia,tamanho_grafo,num_aresta);
    vector<vector<int>> lista_adjacencia(tamanho_grafo);
    get_matriz_incidencia(tamanho_grafo,num_aresta, matriz,matriz_incidencia,lista_adjacencia ,false);

    // for (int i = 0; i< tamanho_grafo; i++){
    //     for(int j = 0; j < num_aresta; j++){
    //         cout << matriz_incidencia[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for(int i = 0; i < lista_adjacencia.size(); i++){
        for(int j = 0; j < lista_adjacencia[i].size(); j++){
            cout << lista_adjacencia[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Numero de arestas do grafo: " << num_aresta << endl;*/
    return 0;
} 
