#!/bin/bash

NAME=holiday

/usr/bin/gcc -DEVAL -static -O2 -std=c11 -o $NAME grader.c $NAME.c -lm
