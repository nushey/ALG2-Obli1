#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

for i in {1..5}; do
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

        "$exec" < "$infile" > "$actual_out"

        # Comparación robusta ignorando espacios, líneas vacías, y diferencias de CRLF
        if diff -wB "$expected_out" "$actual_out" > /dev/null; then
            echo -e "${GREEN}✔ Test $prefix passed.${NC}"
        else
            echo -e "${RED}✘ Test $prefix failed.${NC}"
            echo "  Diferencias:"
            diff -u --strip-trailing-cr "$expected_out" "$actual_out"
        fi

        rm "$actual_out"
    done
done
