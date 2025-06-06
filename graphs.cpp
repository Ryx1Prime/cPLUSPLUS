#include <iostream>
using namespace std;
// Класс графа на основе матрицы смежности
class AdjMatrix{
    int ver;
    int** matrix;
public:
    AdjMatrix(int n){
        ver = n;
        matrix = new int* [n];
        for (int i = 0; i < n; i++){
            matrix[i] = new int[n];
            for (int j = 0; j < n; j++){
                matrix[i][j] = 0;
            }
        }
    }
    ~AdjMatrix(){
        for (int i = 0; i < ver; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void add_edge(int u, int v){
        if (u >= 0 && u < ver && v >= 0 && v < ver){
            matrix[u][v] = 1;
            matrix[v][u] = 1;
        }
    }
    void remove_edge(int u, int v){
        if (u >= 0 && u < ver && v >= 0 && v < ver){
            matrix[u][v] = 0;
            matrix[v][u] = 0;
        }
    }
    bool has_edge(int u, int v){
        if (u >= 0 && u < ver && v >= 0 && v < ver){
            return matrix[u][v] == 1;
        }
        return false;
    }
    int get_vertex() const{
        return ver;
    }
    void print_matrix() const{
        for (int i = 0; i < ver;i++){
            for (int j = 0; j < ver; j++){
                cout << matrix[i][j];
            }
            cout << endl;
        }
    }
};
//  Класс графа на основе матрицы инцидентности
class matrix_Incidentnost{
private:
    int V;
    int E;
    int** matrix;
public:
    matrix_Incidentnost(int ver, int edges) : V(ver), E(edges) {
        matrix = new int* [V];
        for (int i = 0; i < V; i++){
            matrix[i] = new int [E];
            for (int j = 0; j < E; j++){
                matrix[i][j] = 0;
            }
        }
    }
    ~matrix_Incidentnost(){
        for (int i = 0; i < V; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void AddEdge(int u, int v, int edge){
        matrix[u][edge] = 1;
        matrix[v][edge] = -1;
    }
    void print(){
        for (int i = 0; i < V; i++){
            for (int j = 0; j < E; j++){
                cout << matrix[i][j];
            }
        }
    }
};
struct AdjNode{
    int ver;
    AdjNode* next;

    AdjNode(int d) : ver(d), next(nullptr){};
};
class AdjList{
private:
    int V;
    AdjNode** spiski;
public:
    AdjList(int ver) : V(ver){
        spiski = new AdjNode*[V];
        for (int i = 0; i < V;i++){
            spiski[i] = nullptr;
        }
    }
    ~AdjList(){
        for (int i =0;i<V;i++){
            AdjNode* newNode = spiski[i];
            while(newNode){
                AdjNode* temp = newNode;
                newNode = newNode->next;
                delete temp;
            }
        }
        delete[] spiski;
    }
    void add_edge(int u, int v){
        AdjNode* newNode = new AdjNode(v);
        newNode->next = spiski[u];
        spiski[u] = newNode;

        newNode = new AdjNode(u);
        newNode->next = spiski[v];
        spiski[v] = newNode;
    }
    void print(){
        for (int i = 0; i<V;i++){
            cout << "вершина" << i << ": ";
            AdjNode* current = spiski[i];
            while(current){
                cout << " -> " << current->ver;
                current = current->next;
            }
            cout << endl;
        }
    }
};