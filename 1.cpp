#include <iostream>
#include <climits>
using namespace std;

struct treeNode {
    int data;
    treeNode* pL;
    treeNode* pR;
    treeNode(int val) : data(val), pL(nullptr), pR(nullptr) {}
};

treeNode* joinNode(treeNode* root, int data) {
    if (root == nullptr) {
        return new treeNode(data);
    }
    if (data < root->data) {
        root->pL = joinNode(root->pL, data);
    } else if (data >= root->data) {
        root->pR = joinNode(root->pR, data);
    }
    return root;
}

treeNode* inputTree() {
    treeNode* root = nullptr;
    int data;
    char choice;
    cout << "введите корень-root дерева: ";
    cin >> data;
    root = joinNode(root, data);
    
    do {
        cout << "надо ещё узел? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "введите значение узла: ";
            cin >> data;
            joinNode(root, data);
        }
    } while (choice == 'y' || choice == 'Y');
    
    return root;
}

void printTree(treeNode* root) {
    if (root == nullptr) return;
    printTree(root->pL);
    cout << root->data << " ";
    printTree(root->pR);
}

void deleteTree(treeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->pL);
    deleteTree(root->pR);
    delete root;
}
int treeHeight(treeNode* node) {
    if (node == nullptr) return 0;
    return 1 + max(treeHeight(node->pL), treeHeight(node->pR));
}

// подсчёт узлов
void countNodesAtLevels(treeNode* node, int level, int* counts) {
    if (node == nullptr) return;
    counts[level]++;
    countNodesAtLevels(node->pL, level + 1, counts);
    countNodesAtLevels(node->pR, level + 1, counts);
}
// делится на элемент
bool findDivisibleNode(treeNode* node, int& result) {
    if (node == nullptr) return false;
    if (node->pL != nullptr && node->pL->data != 0 && node->data % node->pL->data == 0) {
        result = node->data;
        return true;
    }
    
    if (node->pR != nullptr && node->pR->data != 0 && node->data % node->pR->data == 0) {
        result = node->data;
        return true;
    }
    return findDivisibleNode(node->pL, result) || findDivisibleNode(node->pR, result);
}

// баланс
bool isBalancedHelper(treeNode* node, int& height) {
    if (node == nullptr) {
        height = 0;
        return true;
    }
    
    int leftHeight, rightHeight;
    bool leftBalanced = isBalancedHelper(node->pL, leftHeight);
    bool rightBalanced = isBalancedHelper(node->pR, rightHeight);
    
    height = max(leftHeight, rightHeight) + 1;
    
    return leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
}
bool isTreeBalanced(treeNode* root) {
    int height;
    return isBalancedHelper(root, height);
}
int minValue(treeNode* node) {
    // 1
    if (node == nullptr) {
        return INT_MAX;
    }
    // 2
    if (node->pL == nullptr && node->pR == nullptr) {
        return node->data;
    }
    int leftMin = minValue(node->pL);
    int rightMin = minValue(node->pR);
    return min(leftMin, rightMin);
}
int main() {
    setlocale(LC_ALL, "RU");
    int choice;
    do {
        cout << "\nМеню:\n"
             << "1. Подсчет количества узлов на каждом уровне\n"
             << "2. Найти элемент, делящийся на своего потомка\n"
             << "3. Проверить сбалансированность дерева\n"
             << "4. Найти минимальный листочек\n"
             << "0. Выход\n"
             << "Выберите: ";
        cin >> choice;
        
        treeNode* root = nullptr;
        
        switch (choice) {
            case 1: {
                cout << "\n=!=!= Подсчет узлов по уровням =!=!=\n";
                root = inputTree();
                
                int height = treeHeight(root);
                int* levelCounts = new int[height]();
                
                countNodesAtLevels(root, 0, levelCounts);
                
                cout << "Количество узлов по уровням:\n";
                for (int i = 0; i < height; i++) {
                    cout << " уровень " << i << ": " << levelCounts[i];
                }
                
                delete[] levelCounts;
                deleteTree(root);
                break;
            }
            case 2: {
                cout << "\n=!=!= Поиск элемента, делящегося на потомка =!=!=\n";
                root = inputTree();
                
                int result;
                if (findDivisibleNode(root, result)) {
                    cout << "Найден элемент: " << result << endl;
                } else {
                    cout << "ничего не нашли\n";
                }
                deleteTree(root);
                break;
            }
            case 3: {
                cout << "\n=!=!= Проверка сбалансированности =!=!=\n";
                root = inputTree();
                
                if (isTreeBalanced(root)) {
                    cout << "Дерево сбалансировано\n";
                } else {
                    cout << "Дерево не сбалансировано\n";
                }
                
                deleteTree(root);
                break;
            }
            case 4:{
                cout << "\n=!=!= Поиск минимального значения среди листьев =!=!=\n";
                root = inputTree();
                int minListochek = minValue(root);
                if (minListochek == INT_MAX) {
                    cout << "Дерево пустое (результат +∞)\n";
                } else {
                    cout << "мин знач: " << minListochek << endl;
                }
                deleteTree(root);
                break;
            }
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 0);
}