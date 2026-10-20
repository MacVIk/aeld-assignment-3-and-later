#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Error: less than 2 arguments" >&2
    exit 1
fi

file="$1"
string="$2"

mkdir -p "$(dirname -- "$file")"

if [ -f "$1" ]; then
    echo "$string" >> "$file"
else 
    echo "$string" > "$file"
fi

exit 0

