# Esami di Algoritmi e Strutture Dati

> [!WARNING]
> **Disclaimer:** Le soluzioni contenute in questo repository sono state scritte personalmente da me a scopo di studio. Di conseguenza, potrebbero non essere ottimali né esenti da errori o imperfezioni.
> Se noti una soluzione migliore o un errore, ti chiedo di **aprire prima una Issue** in cui spiegare il miglioramento proposto, così da tenere traccia delle correzioni effettuate. Successivamente, se lo desideri, puoi anche inviare una **Pull Request (PR)** collegata alla Issue.

Raccolta di tracce, soluzioni in C++ e set di test per le prove d'esame del corso di **Algoritmi e Strutture Dati**.

---

## 📁 Struttura del Repository

Ogni cartella corrisponde a una specifica data d'esame (`YYYY-MM-DD`) e contiene:
- `testo.pdf`: La traccia dell'esercizio proposto durante l'esame.
- `main.cpp`: La soluzione sviluppata in C++ (standard C++11).
- `TestSet/`: Cartella contenente i file di input (`input0.txt`, `input1.txt`, ...) e output atteso (`output0.txt`, `output1.txt`, ...).

Nella radice del repository è inoltre disponibile lo script `eval.sh` per la verifica automatica della correttezza e delle prestazioni della soluzione rispetto al `TestSet`.

---

## 📅 Sessioni d'Esame Presenti

| Data Appello | Strutture Dati / Argomenti Principali | Traccia | Soluzione |
| :--- | :--- | :---: | :---: |
| **2024-06-04** | Alberi Binari di Ricerca (BST / ABR), etichettatura e livelli | [PDF](2024-06-04/testo.pdf) | [main.cpp](2024-06-04/main.cpp) |
| **2024-06-25** | Hash Table con ABR / gestione collisioni | [PDF](2024-06-25/testo.pdf) | [main.cpp](2024-06-25/main.cpp) |
| **2024-07-16** | BST / ricerca del percorso ottimo | [PDF](2024-07-16/testo.pdf) | [main.cpp](2024-07-16/main.cpp) |
| **2024-09-10** | ABR, calcolo foglie e proprietà strutturali | [PDF](2024-09-10/testo.pdf) | [main.cpp](2024-09-10/main.cpp) |
| **2025-01-08** | Alberi Binari, ricerca e gestione nodi | [PDF](2025-01-08/testo.pdf) | [main.cpp](2025-01-08/main.cpp) |
| **2025-01-24** | Tabella Hash (Chaining/ABR) per gestione corsi universitari | [PDF](2025-01-24/testo.pdf) | [main.cpp](2025-01-24/main.cpp) |
| **2025-02-11** | Tabella Hash e ordinamento custom (gestione Hotel) | [PDF](2025-02-11/testo.pdf) | [main.cpp](2025-02-11/main.cpp) |
| **2025-06-09** | Hash Table con ABR per rimborsi/missioni | [PDF](2025-06-09/testo.pdf) | [main.cpp](2025-06-09/main.cpp) |
| **2025-06-27** | Heap prioritario (`heap.hpp`) e Hash Table per servizi | [PDF](2025-06-27/testo.pdf) | [main.cpp](2025-06-27/main.cpp) |
| **2025-07-18** | ABR e Hashing per gestione acquisti | [PDF](2025-07-18/testo.pdf) | [main.cpp](2025-07-18/main.cpp) |
| **2025-09-12** | ABR e ordinamento avanzato per ricercatori | [PDF](2025-09-12/testo.pdf) | [main.cpp](2025-09-12/main.cpp) |
| **2026-07-23** | Coda con priorità / Heap per gestione pazienti | [PDF](2026-07-23/testo.pdf) | [main.cpp](2026-07-23/main.cpp) |

---

## 🛠️ Come Eseguire e Verificare le Soluzioni

### Requisiti
- **Compilatore C++**: `g++` con supporto allo standard C++11 (`-std=c++11`).
- **Ambiente di Shell**: Linux, macOS o Windows (tramite WSL / Git Bash) per l'esecuzione dello script `eval.sh`.

### Esecuzione Automatica dei Test
Per verificare una soluzione tramite lo script `eval.sh`:

1. Aprire la shell e posizionarsi nella cartella dell'appello desiderato:
   ```bash
   cd 2024-06-04
   ```

2. Eseguire lo script `eval.sh` contenuto nella radice:
   ```bash
   ../eval.sh
   ```

Lo script effettua le seguenti operazioni:
- Compila `main.cpp` con la flag `-std=c++11`.
- Esegue l'eseguibile reindirizzando l'input da `TestSet/input*.txt`.
- Confronta l'output generato con quello atteso in `TestSet/output*.txt`.
- Mostra l'esito dei test (`OK` / `FALLITO`) e il tempo di esecuzione in millisecondi.

### Esecuzione Manuale
Per compilare ed eseguire manualmente un singolo esercizio:

```bash
g++ main.cpp -std=c++11 -o main.out
./main.out < TestSet/input0.txt
```

---

*Questo file README.md è stato generato automaticamente dall'IA.*
