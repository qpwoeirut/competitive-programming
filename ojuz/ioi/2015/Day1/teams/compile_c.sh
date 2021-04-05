#!/bin/bash

problem=teams

gcc -DEVAL -static -O2 -std=c11 -o $problem -Wall -Wshadow -Wextra -Wconversion grader.c $problem.c -lm
