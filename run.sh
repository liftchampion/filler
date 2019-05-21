#!/bin/bash

pattern="^[1-3]$"
if ! [[ $1 =~ $pattern ]]; then
	echo "Please, write map size (1-3)"
	exit 0;
fi
./filler_vm -f maps/map0$(($1 - 1)) -p1 ./ggerardy.filler -p2 ./ggerardy.filler | ./visualizer/filler_visualizer
