#include <iostream>
// stack
using namespace std;
struct Node{
    int data;
    Node* pNext;
};
class Stack{
private:
    Node* top;
public:
    Stack() : top(nullptr){}; 
    void Push(int el){
        Node* pNode = new Node();
        pNode->data = el;
        pNode->pNext = top;
        top = pNode;
    }
    int PoP(){
        if(!top) return -1;
        Node* pTemp = top;
        int val = top->data;
        top = top->pNext;
        delete top;
        return val;
    }
    int PeeK(){
        if (!top) return -1;
        return top->data;
    }
};






                                      /// ОЧЕРЕДЬ
struct qNode{
    int val;
    qNode* qNext;
};
class Queue{
private:
    qNode* head;
    qNode* tail;
public:
    void Enqueue(int el){
        qNode* newNode = new qNode{el, nullptr};
        if (!head) tail = head = newNode;
        else {
            tail->qNext = newNode;
            tail = newNode;
        }
    }
    int Dequeue(){
        if (!head) return -1;
        qNode* qTemp = head;
        int val = head->val;
        head = head->qNext;
        if (!head) tail == nullptr;
        delete qTemp;
        return val;
    }
    int Peek(){
        if (!head) return -1;
        return head->val;
    }
};