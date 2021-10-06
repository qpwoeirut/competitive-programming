alias template='~/CompetitiveProgramming/templates/template.py'

cmpl() {
    fname="${1%.*}"
    g++-11 -std=c++17 -Wl,-stack_size -Wl,0x10000000 -O2 -lm -Wall -DLOCAL $fname.cpp -o $fname.out
}

run() {
    fname="${1%.*}"
    g++-11 -std=c++17 -Wl,-stack_size -Wl,0x10000000 -O2 -lm -Wall -DLOCAL $fname.cpp -o temp_$fname.out
    echo "Compiled!"
    $2 ./temp_$fname.out
    rm temp_$fname.out
}

frun() {
    echo "======== INPUT ========"
    cat $1.in
    echo
    echo "======== CERR ========"
    run $1 $2
    echo
    echo "======== OUTPUT ========"
    cat $1.out
}

math() {
    python3 -c "from math import *; print($1)"
}

