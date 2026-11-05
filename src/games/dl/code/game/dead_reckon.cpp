#include "common.h"
#include "game_section.h"


typedef int s128 __attribute__((mode(TI)));
struct vec4 {
	/* 0x00 */ s128 q;
};
struct tDR_PositionHistory {
	/* 0x00 */ vec4 pos[2];
	/* 0x20 */ int time[2];
	/* 0x28 */ int count;
	/* 0x2c */ int pad;
};
struct tDR_Vars {
	/* 0x000 */ tDR_PositionHistory Pos_History;
	/* 0x030 */ vec4 Velocity_Tracking;
	/* 0x040 */ vec4 Accel_Tracking;
	/* 0x050 */ vec4 Velocity_Converge;
	/* 0x060 */ vec4 Accel_Converge;
	/* 0x070 */ vec4 Pos_Start;
	/* 0x080 */ vec4 Pos_Converge;
	/* 0x090 */ vec4 Pos_Current;
	/* 0x0a0 */ vec4 Velocity_Current;
	/* 0x0b0 */ vec4 Accel_Current;
	/* 0x0c0 */ char unk0c0[0x34];
	/* 0x0f4 */ int Time_Start;
	/* 0x0f8 */ int Time_Converge;
	/* 0x0fc */ int Time_Current;
	/* 0x100 */ char unk100[0x30];
	/* 0x130 */ int unk130;
	/* 0x134 */ int unk134;
	/* 0x138 */ int unk138;
	/* 0x13c */ int unk13c;
	/* 0x140 */ int Time_ProcessPendingUpdate;
	/* 0x144 */ int Interval_Latency_Offset;
	/* 0x148 */ unsigned int flags;
	/* 0x14c */ int pad;
	/* 0x150 */ int prevKnownSyncedTime;
	/* 0x154 */ int KnownSyncedTime;
	/* 0x158 */ int PreviousUpdateTime;
	/* 0x15c */ int PendingSyncTime;
};
void DR_InitVars(tDR_Vars *, vec4 *, int) __asm__("DR_InitVars");


GAME_SECTION(DR_InitVars) void DR_InitVars(tDR_Vars *drVars, vec4 *posInit, int timeInit)
{
	/* The prototype debug data lists this register variable; retail stores $0 as a quadword. */
	register s128 zero __asm__("$0");
	drVars->unk138 = 0;
	drVars->Interval_Latency_Offset = 0x1e;
	drVars->unk130 = 0;
	drVars->unk134 = 0;
	drVars->Pos_History.pos[0] = *posInit;
	drVars->Pos_History.pos[1] = *posInit;
	drVars->Pos_History.time[0] = timeInit - 0x20;
	drVars->Pos_History.time[1] = timeInit - 0x1f;
	drVars->Pos_History.count = 0;
	drVars->Velocity_Tracking.q = zero;
	drVars->Accel_Tracking.q = zero;
	drVars->Velocity_Converge.q = zero;
	drVars->Accel_Converge.q = zero;
	drVars->Velocity_Current.q = zero;
	drVars->Accel_Current.q = zero;
	drVars->Pos_Start = *posInit;
	drVars->Pos_Converge = *posInit;
	drVars->Pos_Current = *posInit;
	drVars->Time_Start = timeInit - 0x1e;
	drVars->Time_Converge = timeInit - 0x1e;
	drVars->Time_Current = timeInit - 0x1e;
	drVars->PendingSyncTime = -1;
	drVars->PreviousUpdateTime = -1;
	drVars->flags = 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/dead_reckon", func_0054B0A0);
