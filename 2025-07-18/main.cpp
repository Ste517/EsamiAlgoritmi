#include <iostream>
#include <vector>

#define HASH_A 1000
#define HASH_B 2000
#define HASH_P 999149

struct Acquisto {
    size_t id;
    std::string categoria;
};

struct ABR {
    Acquisto acq;
    ABR* left;
    ABR* right;
    ~ABR() {
        delete left;
        delete right;
    }
    inline bool isLeaf() const {
        return (left == NULL) && (right == NULL);
    }
    ABR(const Acquisto& acq) : left(NULL),right(NULL),acq(acq) {}
};

size_t f_c(const std::string& categoria, const ABR* albero) {
    if (albero == NULL) return 0;
    if ((albero->isLeaf()) && (albero->acq.categoria.compare(categoria) == 0)) {
        return 1;
    }
    return f_c(categoria, albero->left) + f_c(categoria, albero->right);
}

void aggiungiAcquisto(const Acquisto& acq, ABR* &albero) {
    if (albero == NULL) {
        albero = new ABR(acq);
        return;
    }
    if (acq.id < albero->acq.id) aggiungiAcquisto(acq,albero->left);
    if (acq.id > albero->acq.id) aggiungiAcquisto(acq,albero->right);
}

inline size_t hash_fun(size_t x, size_t N) {
    return (((HASH_A*x)+HASH_B)%HASH_P)%N;
}

int main() {
    size_t N;
    std::string C;
    std::cin >> N >> C;
    std::vector<ABR*> hashtable(N,NULL);
    for (size_t i = 0; i < N; ++i) {
        Acquisto temp;
        std::cin >> temp.id >> temp.categoria;
        aggiungiAcquisto(temp, hashtable[hash_fun(temp.id, N)]);
    }
    size_t max = 0;
    size_t i_max = 0;
    for (size_t i = 0; i < N; ++i) {
        size_t temp = f_c(C,hashtable[i]);
        if (temp >= max) {
            max = temp;
            i_max = i;
        }
    }
    if (max == 0) std::cout << "-1\n";
    else std::cout << i_max << std::endl;
    for (size_t i = 0; i < N; ++i) delete hashtable[i];
    return 0;
}
