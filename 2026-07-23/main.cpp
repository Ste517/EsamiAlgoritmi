#include <iostream>
#include <utility>
#include <vector>
#include <string>

struct Paziente {
    std::string codice;
    unsigned int priorita;
    unsigned int istante;
    Paziente() : codice(""),priorita(0),istante(0) {}
    // definisco la priorità
    bool operator>(const Paziente& other) {
        if (priorita == other.priorita) {
            if (istante == other.istante) return codice.compare(other.codice) < 0;
            return istante < other.istante;
        }
        return priorita < other.priorita;
    }
};

class Heap {
    std::vector<Paziente> data;
    inline Paziente& at(size_t i) {
        return data.at(i);
    }
    inline void exchange(size_t a, size_t b) {
        std::swap(at(a),at(b));
    }
    inline size_t last() {
        return data.size() - 1;
    }
    inline size_t left_child(size_t i) {
        return 2 * i + 1;
    }
    inline size_t right_child(size_t i) {
        return 2 * i + 2;
    }
    inline size_t parent(size_t i) {
        return i == 0 ? 0 : (i - 1) / 2;
    }
    inline bool is_valid_index(size_t i) {
        return i < data.size();
    }
    void up(size_t i) {
        if (is_valid_index(i)) {
            if (at(i) > at(parent(i))) {
                exchange(i,parent(i));
                up(parent(i));
            }
        }
    }
    void down(size_t i) {
        size_t son = left_child(i);
        if (son == last()) {
            if (at(son) > at(i)) exchange(i,last());
        } else if (son < last()) {
            if (at(son+1)>at(son)) ++son;
            if (at(son) > at(i)) {
                exchange(i,son);
                down(son);
            }
        }
    }
public:
    Heap() {}
    void insert(const Paziente& paz) {
        data.push_back(paz);
        up(last());
    }
    Paziente extract() {
        Paziente paz = at(0);
        exchange(0, last());
        data.pop_back();
        if (!data.empty()) down(0);
        return std::move(paz);
    }
    inline size_t size() const {
        return data.size();
    }
    const Paziente& operator[](size_t i) const {
        return data.at(i);
    }
};

int main() {
    size_t N;
    unsigned int P;
    Paziente temp;
    std::pair<Paziente,unsigned int> temp_estratto;
    char tipo;
    Heap pronto_soccorso;
    std::cin >> N >> P;
    std::vector<std::pair<Paziente,unsigned int>> pazienti_estratti;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> tipo;
        if (tipo == 'I') {
            std::cin >> temp.codice >> temp.priorita >> temp.istante;
            if (temp.priorita < P) pronto_soccorso.insert(temp);
        } else if (tipo == 'E') {
            std::cin >> temp_estratto.second;
            if (pronto_soccorso.size() != 0) {
                temp_estratto.first = pronto_soccorso.extract();
                pazienti_estratti.push_back(temp_estratto);
            }
        }
    }
    
    std::vector<std::pair<std::string,unsigned int>> res(P);
    for (size_t i = 0; i < pazienti_estratti.size(); ++i) {
        unsigned int pri = pazienti_estratti[i].first.priorita;
        unsigned int attesa = pazienti_estratti[i].second - pazienti_estratti[i].first.istante;
        std::pair<std::string,unsigned int> temp_pair;
        if (attesa > res[pri].second || res[pri].first.empty()) {
            res[pri].first = pazienti_estratti[i].first.codice;
            res[pri].second = attesa;
        }
    }
    for (size_t i = 0; i < res.size(); ++i) {
        if (!res[i].first.empty()) std::cout << res[i].first << std::endl;
        else std::cout << "-1\n";
    }
    return 0;
}
