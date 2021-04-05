#!/bin/bash

problem=scales

fpc -dEVAL -XS -O2 -o$problem grader.pas
