#!/usr/bin/env python3
"""Exercise Windows/Linux launchers with a fake Docker executable (no mutations)."""
from pathlib import Path
import os, subprocess, tempfile

ROOT=Path(__file__).resolve().parents[1]
WINDOWS=os.name=='nt'
with tempfile.TemporaryDirectory(prefix='ryno-launcher-') as directory:
    tmp=Path(directory); log=tmp/'calls.txt'
    if WINDOWS:
        fake=tmp/'docker.cmd'
        fake.write_text('''@echo off
>>"%RYNO_TEST_LOG%" echo %CD%^|%*
if "%1 %2"=="image inspect" exit /b %RYNO_IMAGE_EXIT%
if "%1"=="build" exit /b %RYNO_BUILD_EXIT%
if "%1"=="compose" exit /b %RYNO_COMPOSE_EXIT%
exit /b 0
''')
        command=['powershell.exe','-NoProfile','-ExecutionPolicy','Bypass','-File',str(ROOT/'docker-init.ps1')]
        flags={'help':'-help','rebuild':'-rebuild'}
    else:
        fake=tmp/'docker'
        fake.write_text('''#!/bin/bash
printf '%s|%s\\n' "$PWD" "$*" >> "$RYNO_TEST_LOG"
if [[ "$1 ${2:-}" == 'image inspect' ]]; then exit "$RYNO_IMAGE_EXIT"; fi
if [[ "$1" == build ]]; then exit "$RYNO_BUILD_EXIT"; fi
if [[ "$1" == compose ]]; then exit "$RYNO_COMPOSE_EXIT"; fi
exit 0
''')
        fake.chmod(0o755)
        command=['bash',str(ROOT/'docker-init.sh')]
        flags={'help':'--help','rebuild':'--rebuild'}
    cases=[('help',['help'],0,0,0,False,[]),
           ('existing image',[],0,0,0,False,['image inspect','compose run']),
           ('missing image',[],1,0,0,False,['image inspect','build -t','compose run']),
           ('rebuild',['rebuild'],0,0,0,False,['build --no-cache','compose run']),
           ('failed build',['rebuild'],0,23,0,True,['build --no-cache']),
           ('failed first build',[],1,23,0,True,['image inspect','build -t']),
           ('failed compose',[],0,0,17,True,['image inspect','compose run'])]
    for name,args,image,build,compose,fail,expected in cases:
        if log.exists():log.unlink()
        env=dict(os.environ,PATH=str(tmp)+os.pathsep+os.environ['PATH'],RYNO_TEST_LOG=str(log),
                 RYNO_IMAGE_EXIT=str(image),RYNO_BUILD_EXIT=str(build),RYNO_COMPOSE_EXIT=str(compose))
        result=subprocess.run(command+[flags[a] for a in args],cwd=tmp,env=env,capture_output=True,text=True)
        calls=log.read_text().splitlines() if log.exists() else []
        assert (result.returncode!=0)==fail,(name,result.returncode,result.stdout,result.stderr)
        assert len(calls)==len(expected),(name,calls)
        for call,prefix in zip(calls,expected):
            cwd,arg=call.split('|',1)
            assert Path(cwd).resolve()==ROOT.resolve(),(name,cwd)
            assert arg.startswith(prefix),(name,arg,prefix)
        print('PASS:',name)
print('PASS: launcher cases on '+('Windows PowerShell' if WINDOWS else 'Linux Bash'))
