#!/bin/bash

problem_name=tickets
sandbox=$(dirname "$0")

"${sandbox}/${problem_name}.exe" "$@"
