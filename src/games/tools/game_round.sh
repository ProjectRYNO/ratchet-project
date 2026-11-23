#!/bin/bash
# game_round.sh : harvest worker functions, verify the sources, then build and checkpoint.
# Run in the container. Derives missing data symbols once and rebuilds.
bash /ProjectRYNO/tools/game_harvest.sh 2>&1 | grep -v '^no entry' | cut -c1-150
bash /ProjectRYNO/tools/game_verify.sh 2>&1 | tail -25 | cut -c1-110
bash /tmp/ck_iso.sh 2>&1 | grep -E '^(split|elf|check_main_elf)=|PASS: [0-9]+ changed|FAIL' | cut -c1-120
cd /tmp/ckroot/dl || exit 1
if grep -q 'undefined reference\|defined in discarded section .\.game_' elf.log; then
	python3 /ProjectRYNO/tools/game_tables.py 2>&1 | cut -c1-120
	python3 /ProjectRYNO/tools/game_symbols.py elf.log 2>&1 | cut -c1-700
	bash /tmp/ck_iso.sh 2>&1 | grep -E '^(split|elf|check_main_elf)=|PASS: [0-9]+ changed|FAIL' | cut -c1-120
fi
cd /tmp/ckroot/dl || exit 1
grep -E 'code/game/[a-zA-Z_0-9]*\.cpp:[0-9]+' elf.log | grep -v 'warning\|In function' | cut -c1-110 | head -14
grep -o 'undefined reference to .[A-Za-z_0-9.]*' elf.log | cut -c24- | sort -u | tr '\n' ' ' | cut -c1-500
grep -E 'cannot move|exceeds|undefined symbol' elf.log | head -5 | cut -c1-150
python3 /ProjectRYNO/tools/compare_elf.py /ProjectRYNO/assets/dl/boot.elf build/boot_elf.elf 2>&1 | grep -E 'differences; ' | cut -c1-90
# Worker/test-file tags must never reach the sources (.agents/INSTRUCTIONS.md invariant 11).
grep -nE '\bA[B-Z][0-9]?_[A-Za-z]\w*|\b[A-Za-z_][A-Za-z0-9_]*[a-z0-9]A[J-Z][0-9]?v?\b|===== A[A-Z]' /ProjectRYNO/dl/code/game/*.cpp \
	| grep -vE '\bAA_|\bA[HI]_RSA|\bAI_(PKCS|Feedback)' | sed 's/^/WORKER TAG: /' | cut -c1-150 | head -20
# Shared structs live in one header each (dl/DOCS/types/GAME_HEADERS.md); flag local copies.
python3 /ProjectRYNO/tools/game_headers_index.py --check | head -20
