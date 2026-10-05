#!/usr/bin/env bash
set -euo pipefail

ld_script="$1"
tmp="$(mktemp)"

awk '
    /^SECTIONS/ {
        print "PHDRS"
        print "{"
        print "    main PT_LOAD FLAGS(7);"
        print "    net PT_LOAD FLAGS(7);"
        print "}"
        print
        next
    }

    /^[[:space:]]*\.[A-Za-z0-9_]+/ {
        current = $1
        sub(/ AT\([^)]*\)/, "")
        print
        next
    }

    /build\/code\/game\/lib\.o\(\.text\*\);/ {
        print
        print "        . = ABSOLUTE(0x001574E0);"
        next
    }

    /^[[:space:]]*}$/ && current != "" {
        if (current ~ /^\.net_/) {
            print "    } :net"
        } else {
            print "    } :main"
        }
        current = ""
        next
    }

    { print }
' "$ld_script" > "$tmp"

mv "$tmp" "$ld_script"
