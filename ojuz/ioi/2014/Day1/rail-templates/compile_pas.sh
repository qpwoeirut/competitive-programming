#!/bin/bash

NAME=rail

/usr/bin/fpc -dEVAL -XS -O2 -o$NAME grader.pas
