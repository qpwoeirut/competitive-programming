#!/bin/bash

problem=mushrooms
grader_name=stub
stack_size=960M
heap_size=1024M

java -XX:+UseSerialGC -Xbatch -XX:-TieredCompilation -XX:CICompilerCount=1 "-Xmx${heap_size}" "-Xss${stack_size}" -cp "${problem}.jar" "${grader_name}"
