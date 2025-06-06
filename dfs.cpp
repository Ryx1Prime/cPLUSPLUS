#include <iostream>
using namespace std;
struct Node{
    int val;
    Node* next;

    Node(int v, Node* n = nullptr) : val(v), next(n){};
};
class ListStack{
private:
    Node* top;
public:
    ListStack() : top(nullptr){};
    ~ListStack(){
        while (top != nullptr){
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
    void push(int el){
        Node* newNode = new Node(el, top);
        top = newNode;
    }
    bool isEmpty() const{
        return top == nullptr;
    }
    int pop(){
        if (top == nullptr){
            return -1;
        }
        Node* current = top;
        int value = top->val;
        top = top->next;
        delete current;
        return value;
    }
    int peek(){
        if (top == nullptr){
            return -1;
        }
        return top->val;
    }
};
struct adjListNode{
    int vertex;
    adjListNode* next;

    adjListNode(int v, adjListNode* n = nullptr) : vertex(v), next(n){};
};
// смежность везде
void dfs_for_matrix(int** graph, int numVertices, int vertex, bool* visited){
    visited[vertex] = true;
    cout << vertex << " ";
    for (int i = 0; i < numVertices; i++){
        if (graph[vertex][i] && !visited[i]) dfs_for_matrix(graph, numVertices, i, visited);
    }
}
void dfs_for_spisok(adjListNode** graph, int vertex, bool* visited){
    visited[vertex] = true;
    cout << vertex << " ";

    adjListNode* neighbor = graph[vertex];
    while(neighbor != nullptr){
        if (!visited[neighbor->vertex]){
            dfs_for_spisok(graph, neighbor->vertex, visited);
        }
        neighbor = neighbor->next;
    }

}

