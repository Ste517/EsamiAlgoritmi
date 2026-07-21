#include <algorithm>
#include <iostream>
#include <vector>

#define HASH_A 1000
#define HASH_B 2000
#define HASH_P 999149

inline size_t hash_fun(size_t x, size_t C) {
    return (((HASH_A*x)+HASH_B)%HASH_P)%C;
}

struct Missione {
    size_t matricola;
    size_t categoria;
    double spesa;
};

struct ABR {
    Missione label;
    ABR* left;
    ABR* right;
    explicit ABR(const Missione& miss) : label(miss),left(NULL),right(NULL) {}
    ~ABR() {
        delete left;
        delete right;
    }
};

struct Info {
    size_t C;
    size_t numero_missioni;
    double spesa_tot;
    std::vector<size_t> matricole;
    double getAvg() const { return numero_missioni > 0 ? (spesa_tot / numero_missioni) : 0; }
    Info() : C(0),numero_missioni(0),spesa_tot(0),matricole(std::move(std::vector<size_t>())) {}
    bool operator>(const Info& other) const {
        double avg1 = getAvg();
        double avg2 = other.getAvg();

        if (avg1 == avg2) {
            return C < other.C;
        }
        return avg1 > avg2;
    }
};

void addNode(const Missione& missione, ABR* &abr) {
    if (abr == NULL) {
        abr = new ABR(missione);
        return;
    }
    if (missione.matricola < abr->label.matricola) addNode(missione,abr->left);
    if (missione.matricola > abr->label.matricola) addNode(missione,abr->right);
}

void calcolaInfo(std::vector<Info>& info, const ABR* tree) {
    if (tree == NULL) return;
    if (info.size() <= tree->label.categoria) info.resize(tree->label.categoria+1);
    Info& temp = info[tree->label.categoria];
    temp.C = tree->label.categoria;
    temp.matricole.push_back(tree->label.matricola);
    temp.spesa_tot += tree->label.spesa;
    ++temp.numero_missioni;
    calcolaInfo(info,tree->left);
    calcolaInfo(info,tree->right);
}

std::vector<size_t> getMatricoleMaxC(const std::vector<Info>& info) {
    Info max = info[0];
    for (const Info& x : info) {
        if (x > max) {
            max = x;
        }
    }
    std::sort(max.matricole.begin(),max.matricole.end());
    return max.matricole;
}

void aggiungiMissione(const Missione& missione, std::vector<ABR*>& hashtable, size_t C) {
    addNode(missione,hashtable[hash_fun(missione.matricola,C)]);
}

int main() {
    size_t N,C;
    std::cin >> N >> C;
    Missione temp;
    std::vector<ABR*> hashtable(C, NULL);
    for (size_t i = 0; i < N; ++i) {
        std::cin >> temp.matricola >> temp.categoria >> temp.spesa;
        aggiungiMissione(temp, hashtable, C);
    }
    for (size_t i = 0; i < hashtable.size(); ++i) {
        if (hashtable[i] != NULL) {
            std::vector<Info> temp;
            calcolaInfo(temp, hashtable[i]);
            for (size_t t : getMatricoleMaxC(temp)) {
                std::cout << t << ' ';
            }
        }
        std::cout << std::endl;
    }
    for (ABR* node : hashtable) {
        delete node;
    }
    return 0;
}

