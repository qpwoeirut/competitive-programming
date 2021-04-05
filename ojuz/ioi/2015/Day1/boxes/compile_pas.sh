#!/bin/bash

problem=boxes

fpc -dEVAL -XS -O2 -o$problem grader.pas
