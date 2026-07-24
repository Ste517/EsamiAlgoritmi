#include <iostream>
#include <vector>
#include <string>
#include <utility>

struct Paziente {
    std::string codice;
    unsigned int priorita;
    unsigned int istante;
    // l'operatore > definisce il paziente con la priorità maggiore
    bool operator>(const Paziente& paz) {
        if (priorita == paz.priorita) {
            if (istante == paz.istante) {
                return codice.compare(paz.codice) < 0;
            }
            return istante < paz.istante;
        }
        return priorita < paz.priorita;
    }
    Paziente& operator=(const Paziente& paz) {
        priorita = paz.priorita;
        istante = paz.istante;
        codice = paz.codice;
    }
    Paziente() : priorita(0),istante(0),codice("") {}
    Paziente(const Paziente& paz) : priorita(paz.priorita) , istante(paz.istante) , codice(paz.codice) {}
};

class Heap {
    std::vector<Paziente> data;
    inline size_t left_child(size_t i) {
        return (2 * i + 1);
    }
    inline size_t right_child(size_t i) {
        return (2 * i + 2);
    }
    inline size_t parent(size_t i) {
        if (i == 0) return 0;
        return ((i - 1) / 2);
    }
    inline Paziente& at(size_t i) {
        return data.at(i);
    }
    inline void exchange(size_t a, size_t b) {
        std::swap(at(a),at(b));
    }
    inline bool valid_index(size_t i) {
        return i < data.size();
    }
    void up(size_t i) {
        if (valid_index(i)) {
            if (at(i) > at(parent(i))) {
                exchange(i,parent(i));
                up(parent(i));
            }
        }
    }
    void down(size_t i) {
        if (size() == 1) return;
        size_t son = left_child(i);
        if (son == data.size()-1) {
            if (at(son) > at(i)) exchange(i,son);
        } else if (son < (data.size()-1)) {
            if (at(son+1) > at(son)) ++son;
            if (at(son) > at(i)) {
                exchange(i, son);
                down(son);
            }
        }
    }
public:
    Heap() {}
    Paziente extract() {
        Paziente ret = at(0);
        at(0) = at(data.size()-1);
        data.pop_back();
        down(0);
        return std::move(ret);
    }
    void insert(const Paziente& paz) {
        data.push_back(paz);
        up(data.size()-1);
    }
    inline size_t size() {
        return data.size();
    }
};

int main() {
    size_t N;
    unsigned int P;
    char type;
    Paziente temp;
    Heap pronto_soccorso;
    std::vector<std::pair<Paziente, unsigned int> > pazienti_estratti;
    std::pair<Paziente, unsigned int> paziente_estratto;
    std::cin >> N >> P;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> type;
        if (type == 'I') {
            std::cin >> temp.codice >> temp.priorita >> temp.istante;
            if (temp.priorita < P)
                pronto_soccorso.insert(temp);
        } else if (type == 'E') {
            std::cin >> paziente_estratto.second;
            if (pronto_soccorso.size() > 0) {
                paziente_estratto.first = pronto_soccorso.extract();
                pazienti_estratti.push_back(paziente_estratto);
            }
        }
    }
    // Qui nello struct paziente uso istante come tempo di attesa
    std::vector<std::pair<std::string,unsigned int> > pazienti_per_pri(P);
    for (size_t i = 0; i < pazienti_estratti.size(); ++i) {
        unsigned int attesa = pazienti_estratti[i].second - pazienti_estratti[i].first.istante;
        unsigned int prio = pazienti_estratti[i].first.priorita;
        if (pazienti_per_pri[prio].second < attesa) {
            pazienti_per_pri[prio].first = pazienti_estratti[i].first.codice;
            pazienti_per_pri[prio].second = attesa;
        }
    }

    for (size_t i = 0; i < pazienti_per_pri.size(); ++i) {
        if (pazienti_per_pri[i].first != "") std::cout << pazienti_per_pri[i].first << std::endl;
        else std::cout << "-1\n";
    }
    return 0;
}
