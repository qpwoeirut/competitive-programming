#!/bin/bash

problem=mushrooms
grader_name=stub

g++ -std=gnu++17 -O2 -Wall -pipe -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
