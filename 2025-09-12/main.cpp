#include <iostream>
#include <string>
#include <vector>

struct Ricercatore {
    size_t matricola;
    size_t numero_articoli;
    std::string SSD;
    bool operator>(const Ricercatore& other) const {
        if (numero_articoli == other.numero_articoli)
            return matricola > other.matricola;
        return numero_articoli > other.numero_articoli;
    }
};

struct ABR {
    Ricercatore ric;
    ABR* left;
    ABR* right;
    ~ABR() {
        delete left;
        delete right;
    }
    explicit ABR(const Ricercatore& ric) : ric(ric),left(NULL),right(NULL) {}
};

void aggiungiRicercatore(const Ricercatore& ric, ABR* &albero) {
    if (albero == NULL) {
        albero = new ABR(ric);
        return;
    }
    if (ric.matricola < albero->ric.matricola) aggiungiRicercatore(ric, albero->left);
    if (ric.matricola > albero->ric.matricola) aggiungiRicercatore(ric, albero->right);
}

template <class T>
class Heap {
    std::vector<T> data;
    inline void exchange(size_t a, size_t b) {
        std::swap(data.at(a),data.at(b));
    }
    void up(size_t i) {
        if (i > 0) {
            if (data.at(i) > data.at((i-1)/2)) {
                exchange(i,(i-1)/2);
                up((i-1)/2);
            }
        }
    }
    void down(size_t i) {
        size_t n = data.size();
        while (true) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t largest = i;

            if (left < n && data.at(left) > data.at(largest)) {
                largest = left;
            }
            if (right < n && data.at(right) > data.at(largest)) {
                largest = right;
            }

            if (largest != i) {
                exchange(i, largest);
                i = largest;
            } else {
                break;
            }
        }
    }
public:
    T extract() {
        T ret = data.at(0);
        data.at(0) = data.at(data.size()-1);
        data.pop_back();
        if (!data.empty()) {
            down(0);
        }
        return std::move(ret);
    }
    inline size_t size() const { return data.size(); }
    void insert(const T& val) {
        data.push_back(val);
        up(data.size()-1);
    }
    Heap() {}
    // Heap(const std::vector<T>& vec) : data(std::vector<T>(vec)){
    //     bool heapified = false;
    //     size_t i = (data.size() / 2) - 1;
    //     while (!heapified) {
    //         down(i);
    //         if (i == 0) heapified = true;
    //         --i;
    //     }
    // }
};

void insertIntoHeap(Heap<Ricercatore>& h, const ABR* tree, const std::string& SSD) {
    if (tree == NULL) return;
    insertIntoHeap(h, tree->left, SSD);
    if (tree->ric.SSD == SSD) h.insert(tree->ric);
    insertIntoHeap(h, tree->right, SSD);
}

int main() {
    size_t N,K;
    std::string SSD;
    ABR* albero = NULL;
    std::cin >> N >> SSD >> K;
    for (size_t i = 0; i < N; ++i) {
        Ricercatore temp;
        std::cin >> temp.matricola >> temp.numero_articoli >> temp.SSD;
        aggiungiRicercatore(temp, albero);
    }
    Heap<Ricercatore> maxHeap;
    insertIntoHeap(maxHeap, albero, SSD);
    for (size_t i = 0; i < K && maxHeap.size() > 0; ++i) {
        std::cout << maxHeap.extract().matricola << std::endl;
    }
    delete albero;
    return 0;
}
