#!/bin/bash

NAME=game

g++-10 -DEVAL -O2 -std=c++11 -o $NAME grader.cpp $NAME.cpp
