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
failed=0
for input in "$@"; do
    name=$(basename -- "$input")
    if ./bin/image-lab "$input" "$out/$name.png" gray; then
        printf 'DONE %s\n' "$input"
    else
        printf 'FAILED %s\n' "$input" >&2
        failed=1
    fi
done
exit "$failed"