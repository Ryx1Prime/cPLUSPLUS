#include <iostream>
using namespace std;
class BST{
public:
    struct Node{
        int val;
        Node* left;
        Node* right;
        Node(int v) : val(v), left(nullptr), right(nullptr){};

    };
    Node* root = nullptr;
    void insert(int val){
        Node* n = new Node(val);
        if (root == nullptr) root = n;
        else{
            Node* temp = root;
            while (temp != nullptr){
                if (val >= temp->val){
                    if (temp->right == nullptr){
                        temp->right = n;
                        return;
                    }
                    temp = temp->right;
                }else{
                    if(temp->left == nullptr){
                        temp->left = n;
                        return;
                    }
                    temp = temp->left;
                }
            }
        }
    }
    bool search(int val){
        Node* temp = root;
        while (temp != nullptr){
            if (val == temp->val){
                return true;
            }
            if (val> temp->val){
                temp = temp->right;
            }
            else{
                temp = temp->left;
            }
        }
        return false;

    }
    void remove(int val){
        root = remove(root, val);
    }
private:
    Node* remove(Node*n, int val){
        if (n == nullptr){
            return nullptr;
        }
        if (n->val > val){
            n->right = remove(n->right, val);
        }
        else if (val < n->val){
            n->left = remove(n->left, val);
        }
        else{
            if (n->left == nullptr && n->right == nullptr){
                delete n;
                n = nullptr;
            }
            else if (n->left == nullptr){
                Node* temp = n;
                n = n->right;
                delete temp;
            }
            else if (n->right == nullptr){
                Node* temp = n;
                n = n->left;
                delete temp;
            }
            else{
                Node* temp = findMin(n->right);
                n->val = temp->val;
                n->right = remove(n->right, temp->val);
            }
        }
        return n;
    }
    Node* findMin(Node* n){
        while(n->left != nullptr) n = n->left;
        return n;
    }
};