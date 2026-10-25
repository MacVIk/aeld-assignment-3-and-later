#!/bin/sh

if [ "$#" -ne 2 ]; then 
    echo "Error: expected two parameters" >&2
    exit 1
fi

if [ -d "$1" ]; then
    echo "Directory exists"
else 
    echo "Error: $1 schould be derrectory" >&2
    exit 1
fi

files=$(find "$1" -type f -exec grep -lF -- "$2" {} + | wc -l)
lines=$(find "$1" -type f -exec grep -hF -- "$2" {} + | wc -l)

printf "The number of files are %s and the number of matching lines are %s\n" \
    "$files" "$lines"

exit 0