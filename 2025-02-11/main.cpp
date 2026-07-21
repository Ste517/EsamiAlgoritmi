#include <cmath>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#define HASH_A 1000
#define HASH_B 2000
#define HASH_P 999149

struct Hotel {
    size_t ID;
    std::string nome;
    size_t n_camere;
    float prezzo_tot;
    Hotel(size_t ID, const std::string& nome) : ID(ID) , nome(nome) , n_camere(0) , prezzo_tot(0) {}
    inline float getAvg() const { return (n_camere > 0) ? (prezzo_tot / n_camere) : NAN; }
};

struct Info {
    float prezzo_medio;
    std::string nome_hotel;
    bool operator<(const Info& other) {
        if (prezzo_medio == other.prezzo_medio) {
            return (nome_hotel.compare(other.nome_hotel) < 0);
        }
        return prezzo_medio < other.prezzo_medio;
    }
};

size_t hash_fun(size_t x, size_t N) {
    return (((HASH_A*x)+HASH_B)%HASH_P)%(N*2);
}

void aggiungiHotel(std::vector<std::list<Hotel>>& hashtable, const Hotel& hotel, size_t N) {
    std::list<Hotel>& lista = hashtable[hash_fun(hotel.ID,N)];
    for (Hotel& elem : lista) {
        if (elem.ID == hotel.ID) return;
    }
    lista.push_front(hotel);
}

void aggiungiPrenotazione(std::vector<std::list<Hotel>>& hashtable, size_t ID_Hotel, size_t N, float prezzo) {
    std::list<Hotel>& lista = hashtable[hash_fun(ID_Hotel,N)];
    for (Hotel& elem : lista) {
        if (elem.ID == ID_Hotel) {
            ++elem.n_camere;
            elem.prezzo_tot += prezzo;
            return;
        }
    }
}

std::vector<std::string> getFirstHotels(const std::vector<std::list<Hotel>>& hashtable, size_t K) {
    std::vector<Info> alberghi;
    for (const std::list<Hotel>& lista :hashtable) {
        for (const Hotel& hotel : lista) {
            Info info;
            info.nome_hotel = hotel.nome;
            info.prezzo_medio = hotel.getAvg();
            alberghi.push_back(info);
        }
    }
    sort(alberghi.begin(),alberghi.end());
    std::vector<std::string> ret_val;
    for (size_t i = 0; i < K && i < alberghi.size(); ++i) {
        ret_val.push_back(alberghi[i].nome_hotel);
    }
    return std::move(ret_val);
}

int main() {
    size_t N, M, K;
    std::cin >> N >> M >> K;
    std::vector<std::list<Hotel>> hashtable(N*2);
    std::string temp_s;
    size_t temp_i;
    float temp_f;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> temp_i >> temp_s;
        aggiungiHotel(hashtable, Hotel(temp_i,temp_s), N);
    }
    for (size_t i = 0; i < M; ++i) {
        std::cin >> temp_i >> temp_f;
        aggiungiPrenotazione(hashtable, temp_i, N, temp_f);
    }
    for (const auto& albergo :getFirstHotels(hashtable, K)) std::cout << albergo << std::endl;
    return 0;
}
