#!/bin/bash

problem=plants
grader_name=grader

g++-9 -std=c++17 -O2 -Wall -lm -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
