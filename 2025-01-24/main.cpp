#include <iostream>
#include <string>
#include <vector>
#include <list>

#define HASH_P 999149
#define HASH_A 1000
#define HASH_B 2000

struct Corso {
    size_t codice;
    size_t iscritti;
};

struct ABR {
    Corso label;
    ABR* left;
    ABR* right;
    explicit ABR(const Corso& corso) : left(NULL),right(NULL),label(corso) {}
    ~ABR() {
        delete left;
        delete right;
    }
};

struct Info {
    std::string cognome_docente;
    size_t max_iscritti = 0;
    bool operator<(const Info& other) const {
        if (max_iscritti == other.max_iscritti) {
            return (cognome_docente.compare(other.cognome_docente) < 0);
        }
        return max_iscritti > other.max_iscritti;
    }
};

void aggiungiIscrizione(size_t cod_corso, ABR* &tree) {
    if (tree == NULL) {
        Corso corso = {cod_corso,1};
        tree = new ABR(corso);
        return;
    }
    if (cod_corso > tree->label.codice) aggiungiIscrizione(cod_corso, tree->right);
    else if (cod_corso < tree->label.codice) aggiungiIscrizione(cod_corso, tree->left);
    else ++(tree->label.iscritti);
}

struct Docente {
    std::string cognome;
    size_t matricola;
    ABR* corsi;
    Docente() : cognome(""),matricola(0),corsi(NULL) {}
    Docente(const std::string& cognome, size_t matricola) : cognome(cognome) , matricola(matricola) {}
    Docente(Docente&& doc) : cognome(std::move(doc.cognome)), matricola(doc.matricola), corsi(doc.corsi) {
        doc.corsi = nullptr;
    }
    ~Docente() { delete corsi; }
};

inline size_t hash_fun(size_t x, size_t N) {
    return (((HASH_A * x) + HASH_B) % HASH_P) % (N * 2);
}

void aggiungiDocente(const std::string& cognome, size_t matricola, std::vector<std::list<Docente>>& hashtable, size_t N) {
    hashtable[hash_fun(matricola,N)].emplace_front(cognome,matricola);
}

ABR** getCorsiDocente(size_t matricola, std::vector<std::list<Docente>>& hashtable,size_t N) {
    for (auto& docente : hashtable[hash_fun(matricola,N)]) {
        if (docente.matricola == matricola) return &docente.corsi;
    }
    return NULL;
}

size_t getMaxIscritti(const ABR* corsi) {
    if (corsi == NULL) return 0;
    size_t max = corsi->label.iscritti;
    size_t left = getMaxIscritti(corsi->left);
    size_t right = getMaxIscritti(corsi->right);
    if (left > max) max = left;
    if (right > max) max = right;
    return max;
}

int main() {
    size_t N, M;
    size_t cod_corso, matricola;
    std::string cognome;
    std::cin >> N >> M;
    std::vector<std::list<Docente>> hashtable(N*2);
    for (size_t i = 0; i < N; ++i) {
        std::cin >> matricola >> cognome;
        aggiungiDocente(cognome,matricola,hashtable,N);
    }
    for (size_t i = 0; i < M; ++i) {
        std::cin >> matricola >> cod_corso;
        ABR** corsiDocente = getCorsiDocente(matricola, hashtable, N);
        if (corsiDocente) aggiungiIscrizione(cod_corso, *corsiDocente);
    }
    Info max_docente;
    bool primo = true;
    for (const auto& elem : hashtable) {
        for (const auto& docente : elem) {
            Info i;
            i.cognome_docente = docente.cognome;
            i.max_iscritti = getMaxIscritti(docente.corsi);
            if (primo || i < max_docente) {
                max_docente = i;
                primo = false;
            }
        }
    }
    if (!primo) {
        std::cout << max_docente.cognome_docente << std::endl;
    }
    return 0;
}
