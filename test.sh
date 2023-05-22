#!/bin/bash

# Definiujemy tablicę z zestawami argumentów
args=()
args=("25 0.25 100")
args+=("25 0.5 100")
args+=("25 0.75 100")
args+=("25 0.99 100")
args+=("50 0.25 100")
args+=("50 0.5 100")
args+=("50 0.75 100")
args+=("50 0.99 100")
args+=("100 0.25 100")
args+=("100 0.5 100")
args+=("100 0.75 100")
args+=("100 0.99 100")
args+=("150 0.25 100")
args+=("150 0.5 100")
args+=("150 0.75 100")
args+=("150 0.99 100")
args+=("200 0.25 100")
args+=("200 0.5 100")
args+=("200 0.75 100")
args+=("200 0.99 100")
args+=("250 0.25 100")
args+=("250 0.5 100")
args+=("250 0.75 100")
args+=("250 0.99 100")
# Iterujemy po zestawach argumentów i uruchamiamy program "./bin/main" dla każdego zestawu z przekazaniem argumentów
for i in "${args[@]}"; do
    echo $i
  ./bin/main ${i[@]}
done