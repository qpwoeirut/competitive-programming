#!/bin/bash

problem=tickets
grader_name=grader

g++ -std=gnu++17 -O2 -Wall -pipe -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
