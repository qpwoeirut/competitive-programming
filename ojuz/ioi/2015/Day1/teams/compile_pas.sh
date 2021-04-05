#!/bin/bash

problem=teams

fpc -dEVAL -XS -O2 -o$problem grader.pas
