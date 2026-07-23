GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo "Compilazione in corso..."

if g++ ./main.cpp -std=c++11 -o ./main.out > ./compilazione.log 2>&1; then
    echo -e "${GREEN}Compilazione eseguita con successo${NC}\n"

    echo "---------------------------------"
    echo -e "Esecuzione dei test:\n"

    passed=0
    total=0

    for file in $(ls TestSet/input*.txt | sort -V); do
        ((total++))
        i=$(echo "$file" | grep -oE '[0-9]+')

        start=$EPOCHREALTIME

        ./main.out < "$file" | diff -q - "TestSet/output$i.txt" > /dev/null
        exit_code=$?

        end=$EPOCHREALTIME

        start_us=$(echo "$start" | tr -d '.')
        end_us=$(echo "$end" | tr -d '.')
        elapsed=$(( (end_us - start_us) / 1000 ))

        if [ $exit_code -eq 0 ]; then
            echo -e "Test $i: ${GREEN}OK${NC} (${elapsed} ms)"
            ((passed++))
        else
            echo -e "Test $i: ${RED}FALLITO${NC} (${elapsed} ms)"
            echo "Output completo del programma:"
            echo -e "---------------------------------"
            ./main.out < "$file"
            echo -e "\n---------------------------------"
        fi
    done

    echo -e "\n---------------------------------"
    echo "Esito: $passed/$total test superati."
else
    echo -e "${RED}La compilazione non è andata a buon fine${NC}, vedi compilazione.log per maggiori dettagli."
fi
