#include <iostream>

struct Node {
    Node* left;
    Node* right;
    int id;
    int w;
    Node(int id, int w) : left(NULL),right(NULL),id(id),w(w) {}
};

void aggiungiTappa(int id, int w, Node* &tree) {
    if (id < 0) return;
    if (tree == NULL) tree = new Node(id,w);
    if (id < tree->id) aggiungiTappa(id,w,tree->left);
    if (id > tree->id) aggiungiTappa(id,w,tree->right);
}

void deleteTree(Node* &tree) {
    if (tree == NULL) return;
    deleteTree(tree->left);
    deleteTree(tree->right);
    delete tree;
}

void trovaPercorso(const Node* tree, int carburante_corrente, int passi, int& best_lun, int& best_dest) {
    if (tree == NULL) return;
    if ((carburante_corrente += tree->w) < 0) return;
    if (tree->left == NULL && tree->right == NULL) {
        if (passi > best_lun) {
            best_lun = passi;
            best_dest = tree->id;
        } else if (passi == best_lun) {
            if (best_dest > tree->id) {
                best_dest = tree->id;
            }
        }
        return;
    }
    trovaPercorso(tree->left, carburante_corrente,passi+1,best_lun,best_dest);
    trovaPercorso(tree->right, carburante_corrente,passi+1,best_lun,best_dest);
}

int main() {
    Node* albero = NULL;
    size_t N;
    int C;
    std::cin >> N >> C;
    int id, w;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> id >> w;
        aggiungiTappa(id,w,albero);
    }
    int best_lun = -1, best_dest = -1;
    trovaPercorso(albero,C,-1,best_lun,best_dest);
    std::cout << best_dest << ' ' << best_lun << std::endl;
}
