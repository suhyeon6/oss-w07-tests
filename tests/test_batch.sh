#!/usr/bin/env bash
# Supplied smoke test. Extend with a mixed valid/invalid input case.
work=$(mktemp -d) || exit 2
trap 'rm -rf -- "$work"' EXIT
bash scripts/batch.sh "$work/result" "assets/day one.jpg" "assets/day two.jpg" >"$work/stdout" 2>"$work/stderr"
status=$?
if [[ $status -eq 0 && -s "$work/result/day one.jpg.png" && -s "$work/result/day two.jpg.png" ]]; then
    echo "PASS valid batch"
else
    cat "$work/stdout" "$work/stderr"
    echo "FAIL valid batch" >&2
    exit 1
fi 
bash scripts/batch.sh "$work/mixed" \
"assets/day one.jpg" assets/broken.jpg \
"assets/day two.jpg" \
>"$work/stdout" 2>"$work/stderr"
status=$?
if [[ $status -ne 1 ]]; then
  echo "FAIL mixed status: $status (expected 1)" >&2
  exit 1
fi

[[ -s "$work/mixed/day two.jpg.png" ]] || exit 1
grep -Fxq "FAILED assets/broken.jpg" "$work/stderr" || exit 1
if grep -Fxq "DONE assets/broken.jpg" "$work/stdout"; then
  exit 1
fi
echo "PASS mixed input"