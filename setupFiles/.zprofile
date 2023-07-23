alias template='~/CompetitiveProgramming/templates/template.py'

export ECC="ubuntu@52.91.19.240"
export ORACLE="ubuntu@192.9.139.142"

cmpl() {
    fname="${1%.*}"
    g++-12 -std=c++17 -I ~/CompetitiveProgramming/setupFiles -Wl,-stack_size -Wl,0x10000000 -O2 -lm -Wall -DLOCAL $fname.cpp -o $fname.out
}

run() {
    fname="${1%.*}"
    g++-12 -std=c++17 -I ~/CompetitiveProgramming/setupFiles -Wl,-stack_size -Wl,0x10000000 -O2 -lm -Wall -DLOCAL $fname.cpp -o temp_$fname.out
    echo "Compiled!"
    $2 ./temp_$fname.out
    rm temp_$fname.out
}

run20() {
    fname="${1%.*}"
    g++-12 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -Wl,-stack_size -Wl,0x10000000 -O2 -lm -Wall -DLOCAL $fname.cpp -o temp_$fname.out
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


##
# Your previous /Users/qpwoeirut/.zprofile file was backed up as /Users/qpwoeirut/.zprofile.macports-saved_2023-03-15_at_23:01:13
##

# MacPorts Installer addition on 2023-03-15_at_23:01:13: adding an appropriate PATH variable for use with MacPorts.
export PATH="/opt/local/bin:/opt/local/sbin:$PATH"
# Finished adapting your PATH environment variable for use with MacPorts.

