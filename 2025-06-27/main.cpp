#include <iostream>
#include "heap.hpp"

struct Servizio {
    std::string ID;
    std::string categoria;
    int indice_gradimento;
    bool operator>(const Servizio& other) const {
        if (indice_gradimento == other.indice_gradimento) return ID < other.ID;
        return indice_gradimento > other.indice_gradimento;
    }
};

size_t hash_fun(const std::string& ID, size_t N) {
    size_t sum = 0;
    for (size_t i = 0; i < ID.length(); ++i) {
        sum += static_cast<size_t>(ID[i]);
    }
    return sum % (N/2);
}

struct Info {
    std::string categoria;
    size_t NElementi;
    bool operator>(const Info& other) const {
        if (NElementi == other.NElementi) return (categoria.compare(other.categoria) < 0);
        return NElementi > other.NElementi;
    }
};

int main() {
    size_t N,K;
    std::cin >> N >> K;
    std::vector<Heap<Servizio>> hashtable(N/2);
    for (size_t i = 0; i < N; ++i) {
        Servizio temp;
        std::cin >> temp.ID >> temp.categoria >> temp.indice_gradimento;
        hashtable[hash_fun(temp.ID, N)].push(temp);
    }
    std::vector<Servizio> temp;
    for (size_t i = 0; i < N/2; ++i) {
        size_t how_many = hashtable[i].size();
        if (K < how_many) how_many = K;
        for (size_t j = 0; j < how_many; ++j) {
            temp.push_back(hashtable[i].pop());
        }
    }
    std::vector<Info> temp_info;
    for (const auto& serv : temp) {
        bool trovato = false;
        for (auto& info : temp_info) {
            if (info.categoria == serv.categoria) {
                trovato = true;
                ++info.NElementi;
            }
        }
        if (!trovato) {
            Info temp;
            temp.NElementi = 1;
            temp.categoria = serv.categoria;
            temp_info.push_back(temp);
        }
    }
    Info best = temp_info[0];
    for (const auto& info : temp_info) {
        if (info > best) best = info;
    }
    std::cout << best.categoria << std::endl;
    return 0;
}
