#!/bin/bash
# game_verify.sh : run the per-function compare on the real code/game sources; print anything not exact.
cd /ProjectRYNO/dl/code/game || exit 1
total=0
for n in $(grep '^GAME_SN_NAMES' /ProjectRYNO/dl/Makefile | sed 's/GAME_SN_NAMES = //' | tr -d '\r'); do
	o=$(python3 /ProjectRYNO/tools/game_test.py "$PWD/$n.cpp" 2>&1)
	echo "$o" | grep -v 'EXACT\|exact$' | sed "s|^|$n: |" | cut -c1-120
	total=$((total + $(echo "$o" | grep -c EXACT)))
done
echo "exact in sources: $total"
