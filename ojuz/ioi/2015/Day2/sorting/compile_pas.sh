#!/bin/bash

problem=sorting

fpc -dEVAL -XS -O2 -o$problem grader.pas
