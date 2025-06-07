#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

for i in {10..10}; do
    exec="./ejercicio${i}.exe"
    test_dir="tests/ejercicio${i}"

    # Chequeo de ejecutable
    if [ ! -f "$exec" ]; then
        echo -e "${RED}✘ Ejecutable $exec no encontrado. Saltando.${NC}"
        continue
    fi

    # Chequeo de carpeta de tests
    if [ ! -d "$test_dir" ]; then
        echo -e "${RED}✘ Carpeta de tests $test_dir no encontrada. Saltando.${NC}"
        continue
    fi

    echo -e "\n🔎 Corriendo tests para ${exec}..."

    for infile in "$test_dir"/*.in.txt; do
        filename=$(basename -- "$infile")
        prefix="${filename%%.in.txt}"

        expected_out="${test_dir}/${prefix}.out.txt"
        actual_out="tmp_${prefix}.out"

        # Tomamos tiempo antes
        start_time=$(date +%s.%N)
        
        # Ejecutamos el programa
        "$exec" < "$infile" > "$actual_out" 2>/dev/null

        # Tomamos tiempo después
        end_time=$(date +%s.%N)

        # Calculamos duración en segundos
        elapsed_sec=$(awk "BEGIN {printf \"%.3f\", $end_time - $start_time}")

        # Comparación robusta
        if diff -wB --strip-trailing-cr "$expected_out" "$actual_out" > /dev/null; then
            echo -e "${GREEN}✔ Test $prefix passed${NC} (${elapsed_sec}s)"
        else
            echo -e "${RED}✘ Test $prefix failed${NC} (${elapsed_sec}s)"
        fi

        rm "$actual_out"
    done
done
