#!/bin/bash

problem=horses

fpc -dEVAL -XS -O2 -o$problem grader.pas
