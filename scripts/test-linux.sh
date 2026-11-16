#!/bin/bash
set -e

# Run from the repository root
cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.."

echo "=== Create build directory ==="
mkdir -p build

echo "=== Build simulator ==="
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    src/main.cpp -o build/conveyor

echo "=== Build controller tests ==="
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    tests/controller_tests.cpp -o build/controller_tests

echo "=== Run controller tests ==="
./build/controller_tests

echo "=== Check pause scenario ==="
    bash tests/check-pause.sh

echo "PASS: all Linux checks passed"
