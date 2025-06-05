#include <iostream>
using namespace std;
class HashTable{
private:
    static const int Table_Size = 10;
    struct Node{
        int key;
        int value;
        Node* next;

        Node(int k, int v) : key(k), value(v), next(nullptr){};
    };
    Node* table[Table_Size];
    int hash_Func(int key){
        return key % Table_Size;
    }
public:
    HashTable(){
        for (int i = 0; i < Table_Size; i++){
            table[i] = nullptr;
        }
    }
    ~HashTable(){
        for (int i = 0; i < Table_Size; i++){
            Node* current = table[i];
            while(current != nullptr){
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    void Append(int key, int value){
        int index = hash_Func(key);
        Node* current = table[index];
        while(current != nullptr){
            if (current->key == key){
                current->value = value; 
                return;
            }
            current = current->next;
        }
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }
    bool get(int key, int& value){
        int index = hash_Func(key);
        Node* current = table[index];
        while(current != nullptr){
            if (current->key == key){
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    bool remove(int key){
        int index = hash_Func(key);
        Node* current = table[index];
        Node* prev = nullptr;
        while(current != nullptr){
            if (current->key == key){
                if (prev == nullptr){
                    table[index] = current->next;
                }else{
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
            }
            return false;
        }
    void Print(){
        for (int i = 0; i < Table_Size; i++) {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                cout << "[" << current->key << ":" << current->value << "] -> ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }
    }
};