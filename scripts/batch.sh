#!/usr/bin/env bash
# Run from the project root. Interface: bash scripts/batch.sh NEW_OUTPUT INPUT...
if (( $# < 2 )); then
    echo "usage: bash scripts/batch.sh NEW_OUTPUT INPUT..." >&2
    exit 2
fi
out=$1
shift
if [[ -e "$out" ]]; then
    echo "output directory already exists: $out" >&2
    exit 2
fi
mkdir -p -- "$out" || exit 2
# Review scope: processing and final status below.
for input in "$@"; do
    name=$(basename -- "$input")
    ./bin/image-lab "$input" "$out/$name.png" gray
    printf 'DONE %s\n' "$input"
done
exit 0
