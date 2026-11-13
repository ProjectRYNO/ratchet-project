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
	unsigned int Alloc(Stream **) __asm__("Alloc");
	unsigned int StreamsStoppedAM(Stream **) __asm__("StreamsStopped");
	void Update(float) __asm__("Update___dupe54");
	void WaitForStop(Stream **, int, void (*)(void *), void *) __asm__("WaitForStop");
};
extern Stream m_streams[3] __asm__("StreamInterface_m_streams");
int m_num_open_streams __asm__("D_21F358") GAME_GP_DATA = 0;
unsigned short ms_unique_id __asm__("D_21F35C") GAME_GP_DATA = 0;
extern "C" {
	int snd_ContinueVAGStream(unsigned int);
}
void InitSoundDef(SoundDef *) __asm__("InitSoundDef");



struct StreamInterface2 {
	void Reset() __asm__("Reset___dupe3");
	void PauseAll(unsigned int) __asm__("PauseAll");
	void UnPauseAll(unsigned int) __asm__("UnPauseAll");
	unsigned int Start(unsigned int) __asm__("Start");
	void Update(float) __asm__("Update___dupe54");
	void Initialize(Stream *) __asm__("Initialize___dupe3");
	static void Callback_SoundIsStillPlaying(unsigned int, unsigned long) __asm__("Callback_SoundIsStillPlaying");
};
extern float NtscPalFrameTimeInSecondsFloat __asm__("NtscPalFrameTimeInSecondsFloat");
extern "C" int snd_FlushSoundCommands();

struct StreamInterface3 {
	unsigned int Stop(unsigned int, float) __asm__("Stop");
	unsigned int SetMinMaxVolume(unsigned int, float, float) __asm__("SetMinMaxVolume");
	static void Callback_PlayVAGStreamByLoc(unsigned int, unsigned long) __asm__("Callback_PlayVAGStreamByLoc");
	static void Callback_IsVAGStreamBuffered(unsigned int, unsigned long) __asm__("Callback_IsVAGStreamBuffered");
};
struct SoundChannelHandle {
	/* 0x00 */ unsigned int handle;
};
SoundChannelHandle *sound_GetChannelFromHandle(short) __asm__("sound_GetChannelFromHandle");

/* ===== AM additions ===== */
struct StreamInterfaceAM {
	void SetGain(Stream *) __asm__("SetGain___dupe2");
	unsigned int StopAll(unsigned int, int, void (*)(void *), void *) __asm__("StopAll___dupe2");
	void WaitForStop(Stream **, int, void (*)(void *), void *) __asm__("WaitForStop");
	unsigned int Alloc(Stream **) __asm__("Alloc");
};
extern "C" void *memset(void *, int, unsigned int);
extern "C" int sceGsSyncV(int);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", InitSoundDef);

GAME_SECTION(Reset___dupe3) void StreamInterface2::Reset()
{
	Stream *stream;
	m_num_open_streams = 3;
	stream = m_streams;
	do {
		Initialize(stream);
		stream->m_state = 0;
		stream++;
	} while ((int)stream < (int)&m_streams[3]);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", func_00489F98);

GAME_SECTION(StopAll___dupe2) unsigned int StreamInterfaceAM::StopAll(unsigned int synchronous, int timeout_vsyncs, void (*func)(void *), void *arg)
{
	Stream *pp_streams[3];
	int i;
	memset(pp_streams, 0, sizeof(pp_streams));
	for (i = 0; i < 3; i++) {
		if (m_streams[i].m_state) {
			pp_streams[i] = &m_streams[i];
			m_streams[i].m_command |= 8;
		}
	}
	if (synchronous) {
		WaitForStop(pp_streams, timeout_vsyncs, func, arg);
	}
	return 1;
}

GAME_SECTION(PauseAll) void StreamInterface2::PauseAll(unsigned int synchronous)
{
	Stream *stream;
	stream = m_streams;
	do {
		if (stream->m_state) stream->m_command |= 2;
		stream++;
	} while ((int)stream < (int)&m_streams[3]);
	if (synchronous) {
		Update(NtscPalFrameTimeInSecondsFloat);
		snd_FlushSoundCommands();
	}
}

GAME_SECTION(UnPauseAll) void StreamInterface2::UnPauseAll(unsigned int synchronous)
{
	Stream *stream;
	stream = m_streams;
	do {
		if (stream->m_state) stream->m_command |= 4;
		stream++;
	} while ((int)stream < (int)&m_streams[3]);
	if (synchronous) {
		Update(NtscPalFrameTimeInSecondsFloat);
		snd_FlushSoundCommands();
	}
}

GAME_SECTION(Play___dupe2) unsigned int StreamInterface::Play(int track, int type, MobyInstance *owner, unsigned int flags)
{
	unsigned int stream_handle = Queue(track, type, owner, flags);
	if (stream_handle != 0xffffffff) {
		Start(stream_handle);
	}
	return stream_handle;
}

GAME_SECTION(Queue) unsigned int StreamInterface::Queue(int track, int type, MobyInstance *owner, unsigned int flags)
{
	unsigned int handle = 0xffffffff;
	Stream *stream = 0;
	if (Alloc(&stream)) {
		Initialize(stream);
		stream->m_flags = flags;
		stream->m_type = type;
		stream->m_track_id = track;
		stream->m_owner = owner;
		stream->m_state = 1;
		handle = CreateHandle(stream);
	}
	return handle;
}

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

GAME_SECTION(Start) unsigned int StreamInterface2::Start(unsigned int stream_handle)
{
	unsigned int ret = 0;
	Stream *stream = StreamInterface::GetStreamFromHandle(stream_handle);
	if (stream && stream->m_state != 5 && stream->m_state != 6 && stream->m_state != 7) {
		ret = 1;
		stream->m_command |= 1;
	}
	return ret;
}

GAME_SECTION(Stop) unsigned int StreamInterface3::Stop(unsigned int stream_handle, float fade_time_s)
{
	unsigned int ret = 0;
	Stream *stream = StreamInterface::GetStreamFromHandle(stream_handle);
	if (stream) {
		stream->m_fade_time_remaining = fade_time_s;
		stream->m_command |= 8;
		stream->m_inv_fade_time = 1.0f / fade_time_s;
		ret = 1;
	}
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", SetGain);

GAME_SECTION(SetMinMaxVolume) unsigned int StreamInterface3::SetMinMaxVolume(unsigned int stream_handle, float min_volume, float max_volume)
{
	unsigned int ret = 0;
	Stream *stream = StreamInterface::GetStreamFromHandle(stream_handle);
	if (stream) {
		((int *)stream->m_sd)[2] = (int)(min_volume * 1024.0f);
		((int *)stream->m_sd)[3] = (int)(max_volume * 1024.0f);
		ret = 1;
	}
	return ret;
}

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

GAME_SECTION(WaitForStop) void StreamInterface::WaitForStop(Stream **pp_streams_observed, int timeout_vsyncs, void (*func)(void *), void *arg)
{
	int i;
	for (; !StreamsStopped(pp_streams_observed) && timeout_vsyncs != 0; timeout_vsyncs--) {
		if (func) {
			func(arg);
		}
		Update(NtscPalFrameTimeInSecondsFloat);
		snd_FlushSoundCommands();
		sceGsSyncV(0);
	}
	if (!StreamsStopped(pp_streams_observed)) {
		for (i = 0; i < 3; i++) {
			if (m_streams[i].m_state) {
				Free(&m_streams[i]);
			}
		}
	}
}

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

GAME_SECTION(SetGain___dupe2) void StreamInterfaceAM::SetGain(Stream *stream)
{
	int gain = (int)(stream->m_master_gain * stream->m_fade_gain * 1024.0f);
	SoundChannelHandle *ch;
	if (gain > 1024) {
		gain = 1024;
	}
	ch = sound_GetChannelFromHandle(stream->m_sound_handle);
	if (ch) {
		((short *)ch)[6] = gain;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stream", GetLocs);

GAME_SECTION(Callback_PlayVAGStreamByLoc) void StreamInterface3::Callback_PlayVAGStreamByLoc(unsigned int _989_handle, unsigned long data)
{
	Stream *stream = StreamInterface::GetStreamFromHandle(data);
	if (stream) {
		if (_989_handle != 0) {
			SoundChannelHandle *channel = sound_GetChannelFromHandle(stream->m_sound_handle);
			if (channel) {
				channel->handle = _989_handle;
				stream->m_989_handle = _989_handle;
				stream->m_state = 3;
			}
		} else {
			StreamInterface::Free(stream);
		}
	}
}

GAME_SECTION(Callback_IsVAGStreamBuffered) void StreamInterface3::Callback_IsVAGStreamBuffered(unsigned int ret_val, unsigned long data)
{
	Stream *stream = StreamInterface::GetStreamFromHandle(data);
	if (stream && ret_val != 0 && ret_val != 0xffffffff && stream->m_state == 3) {
		stream->m_state = 4;
	}
}

GAME_SECTION(Callback_SoundIsStillPlaying) void StreamInterface2::Callback_SoundIsStillPlaying(unsigned int ret_val, unsigned long data)
{
	Stream *stream = StreamInterface::GetStreamFromHandle(data);
	if (stream && ret_val == 0 && stream->m_989_handle != 0xffffffff) {
		StreamInterface::Free(stream);
	}
}
