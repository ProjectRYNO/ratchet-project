#include "common.h"
#include "game_section.h"


struct MobyInstance;
struct Stream {
	/* 0x00 */ unsigned int m_989_handle;
	/* 0x04 */ unsigned short m_track_id;
	/* 0x06 */ unsigned char m_type;
	/* 0x07 */ unsigned char m_command;
	/* 0x08 */ unsigned char m_state;
	/* 0x09 */ unsigned char m_last_state;
	/* 0x0a */ unsigned char m_internal_flags;
	/* 0x0b */ unsigned char pad8_0[1];
	/* 0x0c */ unsigned short m_sound_handle;
	/* 0x0e */ unsigned short pad16_0[1];
	/* 0x10 */ unsigned short m_unique_id;
	/* 0x12 */ unsigned short m_flags;
	/* 0x14 */ MobyInstance *m_owner;
	/* 0x18 */ unsigned int m_stream_handle;
	/* 0x1c */ unsigned int pad32_0[1];
	/* 0x20 */ float m_master_gain;
	/* 0x24 */ float m_fade_gain;
	/* 0x28 */ float m_fade_time_remaining;
	/* 0x2c */ float m_inv_fade_time;
	/* 0x30 */ float m_sd[8];
};
struct SoundDef {
	/* 0x00 */ float minRange;
	/* 0x04 */ float maxRange;
	/* 0x08 */ int minVolume;
	/* 0x0c */ int maxVolume;
	/* 0x10 */ int minPitch;
	/* 0x14 */ int maxPitch;
	/* 0x18 */ unsigned char loop;
	/* 0x19 */ unsigned char flags;
	/* 0x1a */ short index;
	/* 0x1c */ int bank_index;
};
struct StreamInterface {
	unsigned int Play(int, int, MobyInstance *, unsigned int) __asm__("Play___dupe2");
	unsigned int Queue(int, int, MobyInstance *, unsigned int) __asm__("Queue");
	unsigned int Start(unsigned int) __asm__("Start");
	unsigned int GetState(unsigned int, int *) __asm__("GetState");
	unsigned int SetGain(unsigned int, float) __asm__("SetGain");
	unsigned int SetMinMaxRange(unsigned int, float, float) __asm__("SetMinMaxRange");
	unsigned int StreamsStopped(Stream **) __asm__("StreamsStopped");
	unsigned int CreateHandle(Stream *) __asm__("CreateHandle");
	void Initialize(Stream *) __asm__("Initialize___dupe3");
	void Start(Stream *) __asm__("Start___dupe2");
	static Stream *GetStreamFromHandle(unsigned int) __asm__("GetStreamFromHandle");
	static void Free(Stream *) __asm__("Free");
};
extern Stream m_streams[3] __asm__("StreamInterface_m_streams");
int m_num_open_streams __asm__("D_21F358") GAME_GP_DATA = 0;
unsigned short ms_unique_id __asm__("D_21F35C") GAME_GP_DATA = 0;
extern "C" {
	int snd_ContinueVAGStream(unsigned int);
}
void InitSoundDef(SoundDef *) __asm__("InitSoundDef");



INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", InitSoundDef);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Reset___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", func_00489F98);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", StopAll___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", PauseAll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", UnPauseAll);

GAME_SECTION(Play___dupe2) unsigned int StreamInterface::Play(int track, int type, MobyInstance *owner, unsigned int flags)
{
	unsigned int stream_handle = Queue(track, type, owner, flags);
	if (stream_handle != 0xffffffff) {
		Start(stream_handle);
	}
	return stream_handle;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Queue);

GAME_SECTION(GetState) unsigned int StreamInterface::GetState(unsigned int stream_handle, int *stream_state)
{
	unsigned int ret = 0;
	Stream *stream = GetStreamFromHandle(stream_handle);
	if (stream) {
		if (stream_state) *stream_state = stream->m_state;
		ret = 1;
	}
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", func_0048A280);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Start);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Stop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", SetGain);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", SetMinMaxVolume);

GAME_SECTION(SetMinMaxRange) unsigned int StreamInterface::SetMinMaxRange(unsigned int stream_handle, float min_range, float max_range)
{
	unsigned int ret = 0;
	Stream *stream = GetStreamFromHandle(stream_handle);
	if (stream) {
		stream->m_sd[0] = min_range;
		stream->m_sd[1] = max_range;
		ret = 1;
	}
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", func_0048A488);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Update___dupe54);

GAME_SECTION(StreamsStopped) unsigned int StreamInterface::StreamsStopped(Stream **pp_streams_observed)
{
	unsigned int b_stopped = 1;
	int i;
	for (i = 2; i >= 0; i--) {
		if (*pp_streams_observed && (*pp_streams_observed)->m_state) b_stopped = 0;
		pp_streams_observed++;
	}
	return b_stopped;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", WaitForStop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Alloc);

GAME_SECTION(Free) void StreamInterface::Free(Stream *stream)
{
	m_num_open_streams++;
	stream->m_unique_id = 0xffff;
	stream->m_state = 0;
}

GAME_SECTION(GetStreamFromHandle) Stream *StreamInterface::GetStreamFromHandle(unsigned int handle)
{
	Stream *ret = 0;
	int index = handle & 0xffff;
	if ((handle >> 16) == m_streams[index].m_unique_id && m_streams[index].m_state) {
		ret = &m_streams[index];
	}
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", CreateHandle);

GAME_SECTION(Initialize___dupe3) void StreamInterface::Initialize(Stream *stream)
{
	stream->m_master_gain = 1.0f;
	stream->m_fade_gain = 1.0f;
	stream->m_989_handle = 0xffffffff;
	stream->m_fade_time_remaining = 0.0f;
	stream->m_inv_fade_time = 0.0f;
	stream->m_command = 0;
	stream->m_internal_flags = 0;
	stream->m_owner = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", AcquireResources);

GAME_SECTION(Start___dupe2) void StreamInterface::Start(Stream *stream)
{
	snd_ContinueVAGStream(stream->m_989_handle);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", SetGain___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", GetLocs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Callback_PlayVAGStreamByLoc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Callback_IsVAGStreamBuffered);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", Callback_SoundIsStillPlaying);
