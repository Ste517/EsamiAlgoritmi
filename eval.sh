for i in {0..12}; do
    ./main.out < "TestSet/input$i.txt" | diff -q - "TestSet/output$i.txt" > /dev/null && echo "Test $i: OK" || echo "Test $i: FALLITO ❌"
done

