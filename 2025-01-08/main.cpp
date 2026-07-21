#include <iostream>
#include <list>

struct Node {
    std::string nome;
    std::string stato;
    Node* left;
    Node* right;
    int ID;
    int costo;
    Node() : ID(0),nome(std::string()),stato(std::string()),costo(0),left(NULL),right(NULL) {}
    Node(const Node& n) : ID(n.ID),nome(n.nome),stato(n.stato),costo(n.costo),left(NULL),right(NULL) {}
    Node(int id, const std::string& nome, const std::string& stato, int costo) : ID(id),nome(nome),stato(stato),costo(costo),left(NULL),right(NULL) {}
};

void deleteTree(Node* tree) {
    if (tree == NULL) return;
    deleteTree(tree->left);
    deleteTree(tree->right);
    delete tree;
}

void aggiungiNodo(const Node& nodoDaAggiungere, Node* &albero) {
    if (albero == NULL) {
        albero = new Node(nodoDaAggiungere);
        return;
    }
    if (nodoDaAggiungere.ID > albero->ID) aggiungiNodo(nodoDaAggiungere, albero->right);
    else aggiungiNodo(nodoDaAggiungere, albero->left);
}

bool raggiungiTappa(std::list<std::string>& stati, int curr_carb, int id, const std::string& citta, const Node* tree) {
    if (tree == NULL) return false;
    if (curr_carb < tree->costo) return false;
    stati.push_back(tree->stato);
    if (citta.compare(tree->nome) == 0) return true;
    if (id > tree->ID) return raggiungiTappa(stati,curr_carb-tree->costo,id,citta,tree->right);
    else return raggiungiTappa(stati,curr_carb-tree->costo,id,citta,tree->right);
}

int main() {
    Node* tree = NULL;
    size_t N;
    int M;
    int id_trovare;
    std::string C;
    std::cin >> N >> M >> C;
    Node nodo;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> nodo.ID >> nodo.nome >> nodo.stato >> nodo.costo;
        aggiungiNodo(nodo,tree);
        if (nodo.nome.compare(C) == 0) id_trovare = nodo.ID;
    }
    std::list<std::string> paesi;
    if (raggiungiTappa(paesi,M,id_trovare,C,tree)) {
        paesi.unique();

    }
    deleteTree(tree);
}
