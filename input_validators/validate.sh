#!/bin/bash

for i in $(seq 1 40);
do
	python3 validate.py < ../data/secret/${i}.in
	RC=$?
	if [ $RC -ne 42 ]; then
		echo "Test case ${i} failed"
	fi
done
