#include <iostream>
#include <climits>
using namespace std;
int* Deikstra(int** graph, const int n, int start){
    int* distance = new int[n];
    bool* visited = new bool[n];
    for (int i = 0; i < n; i++){
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[start] = 0;
    for (int i = 0; i < n; i++){
        int min = INT_MAX; int u;
        for (int j = 0; j < n; j++){
            if (visited[j] == false && distance[j] < min){
                min = distance[j];
                u = j;
            }
            visited[u] = true;
        }
        
        for (int k = 0; k < n; k++){
            if (graph[u][k] == 0 || visited[i]){
                continue;
            }
            int new_dist = distance[u] + graph[u][k];
            if (new_dist < distance[k]){
                distance[k] = new_dist;
            }
        }
    }
    delete[]visited;
    return distance;
}
int main() {
    const int n = 5;
    int** graph = new int*[n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new int[n] {0}; // Инициализация нулями
    }

    // Заполнение графа (пример)
    graph[0][1] = 4;
    graph[0][2] = 1;
    graph[1][2] = 2;
    graph[1][3] = 5;
    graph[2][1] = 2;
    graph[2][3] = 3;
    graph[3][4] = 2;

    int start = 0;
    int* distances = Deikstra(graph, n, start);

    if (distances != nullptr) {
        std::cout << "Кратчайшие расстояния от вершины " << start << ":\n";
        for (int i = 0; i < n; ++i) {
            std::cout << "До вершины " << i << ": " << distances[i] << "\n";
        }
        delete[] distances; // Освобождаем память
    }

    // Освобождение памяти графа
    for (int i = 0; i < n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
}