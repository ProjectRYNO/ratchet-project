# Emulator smoke-test checklist

This records observations, not an automatic claim of gameplay correctness.
Use for the selected game/revision and the change being tested. Do not overwrite
someone's save data or change their emulator profile to obtain a pass.

## Identify the test

Record game/region/revision, original-disc identifier/hash, tested ELF or ISO path
and SHA-256, source revision/dirty changes, verification report path, emulator
name/version, BIOS identity, relevant settings, and whether cheats/patches are on.
Use a separate test profile and disposable/copied saves where available. Never
include BIOS, disc, or save contents in a public report.

For a rebuilt ISO, confirm its extracted boot ELF matches the compiled ELF first.
For direct ELF boot, identify which disc is mounted. Do not accidentally test the
original ELF merely because its filename resembles the rebuilt one.

## Record PASS / FAIL / NOT RUN for each applicable step

1. Cold boot through the expected logos/menu; check the log for exceptions,
   hangs, unsupported instructions, and unexpected restarts.
2. Navigate menus and exercise controller input. For boot-option changes, test
   the affected display/audio settings and their persistence or transfer.
3. Start a known level/session; verify loading, player spawn, movement, camera,
   primary actions, pause/resume, and exit back to the menu.
4. Exercise the changed subsystem. For sound: effects, music/streams, volume,
   pause/resume, bank/level transitions, and repeated playback. A mocked IOP test
   cannot establish audible output or asynchronous hardware timing.
5. Load a second level/session to catch reload/state cleanup problems. Test
   save/load only with a disposable/copied save and when relevant to the change.
6. Repeat the same path with the original game under equivalent settings when
   comparing a suspected regression. Record the first divergence and reproduction.

Record elapsed time or frame/stage reached, screenshots/log locations where useful,
and any skipped step with its reason. Avoid declaring full gameplay coverage from
initialization alone. Networking, multiplayer, unusual hardware, and long-running
sessions need their own explicitly recorded cases when relevant.

## Result snippet

```text
Artifact/hash:
Verification report:
Emulator/profile/disc:
Scenario and input sequence:
Observed stage and duration:
PASS:
FAIL (first divergence, reproduction, log):
NOT RUN:
Original-game comparison:
```

Use the [handoff template](../../.agents/templates/HANDOFF.md) for the broader task.
