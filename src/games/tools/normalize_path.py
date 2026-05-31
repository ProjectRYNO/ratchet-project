#!/usr/bin/env python3
import sys
import re

path = sys.argv[1] if len(sys.argv) > 1 else ""

m = re.match(r'^([A-Za-z]):\\(.*)', path)
if m:
    drive = m.group(1).lower()
    rest = m.group(2).replace('\\', '/')
    print(f'/mnt/{drive}/{rest}')
else:
    print(path)
