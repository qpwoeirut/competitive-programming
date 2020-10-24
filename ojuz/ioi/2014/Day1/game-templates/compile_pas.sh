#!/bin/bash

NAME=game

/usr/bin/fpc -dEVAL -XS -O2 -o$NAME grader.pas
