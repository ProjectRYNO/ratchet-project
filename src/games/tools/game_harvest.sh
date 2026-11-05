#!/bin/bash
# game_harvest.sh : integrate every exact, not-yet-integrated function from the worker test files.
# Run in the container. Rerun the full checkpoint afterwards; only that proves a match.
cd /ProjectRYNO/dl/build/game-work || exit 1
for f in A[CDE]_*.cpp; do
	python3 /ProjectRYNO/tools/game_test.py "$PWD/$f" 2>&1 | grep EXACT | awk -v f="$f" '{sub(/:/,"",$1); print f, $1}'
done > /tmp/ex.txt
grep -E '^  [A-Za-z_0-9]+: 0x' /ProjectRYNO/dl/config/decompiled_functions.yaml | sed 's/^  //; s/:.*//' | sort -u > /tmp/have.txt
awk 'NR==FNR {have[$1]=1; next} !($2 in have)' /tmp/have.txt /tmp/ex.txt > /tmp/new.txt
echo "new functions: $(awk '{print $2}' /tmp/new.txt | sort -u | wc -l)"
awk '{print $2}' /tmp/new.txt | sort -u | while read -r fn; do
	ls /tmp/ckroot/dl/code/asm/nonmatchings/game/*/"$fn".s 2>/dev/null | head -1 | awk -F/ '{print $(NF-1)}'
done | sort -u > /tmp/objs.txt
cd /ProjectRYNO/dl || exit 1
xargs -r python3 /ProjectRYNO/tools/game_register.py < /tmp/objs.txt | cut -c1-70
python3 /ProjectRYNO/tools/game_integrate.py /tmp/new.txt 2>&1 | cut -c1-200
xargs -r python3 /ProjectRYNO/tools/game_labels.py < /tmp/objs.txt
