if [[ -z "$1" ]];
then
    for i in $(seq 1 12); do
        g++-14 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -Wl,-stack_size -Wl,0x1000000000 -O3 -mtune=native -march=native -DTEST=$i search.cpp -o search.out
        echo "Starting case $i"
        ./search.out
        rm search.out
    done
else
    g++-14 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -Wl,-stack_size -Wl,0x1000000000 -O3 -mtune=native -march=native -Wall -DLOCAL -DTEST=$1 search.cpp -o search.out
    echo "Starting case $1"
    ./search.out
    rm search.out
fi
