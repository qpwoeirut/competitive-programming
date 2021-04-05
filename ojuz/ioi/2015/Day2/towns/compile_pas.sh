#!/bin/bash

problem=towns

fpc -dEVAL -XS -O2 -o$problem grader.pas
