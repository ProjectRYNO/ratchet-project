#ifndef STREAM_H
#define STREAM_H

struct MobyInstance;
struct Stream;

struct StreamInterface { // 0x1
	unsigned int Play(int, int, MobyInstance *, unsigned int) __asm__("Play___dupe2");
	unsigned int Queue(int, int, MobyInstance *, unsigned int) __asm__("Queue");
	unsigned int Start(unsigned int) __asm__("Start");
	unsigned int Stop(unsigned int, float) __asm__("Stop");
	unsigned int GetState(unsigned int, int *) __asm__("GetState");
	unsigned int SetGain(unsigned int, float) __asm__("SetGain");
	void SetGain(Stream *) __asm__("SetGain___dupe2");
	unsigned int StopAll(unsigned int, int, void (*)(void *), void *) __asm__("StopAll___dupe2");
	unsigned int SetMinMaxRange(unsigned int, float, float) __asm__("SetMinMaxRange");
	unsigned int StreamsStopped(Stream **) __asm__("StreamsStopped");
	unsigned int CreateHandle(Stream *) __asm__("CreateHandle");
	void Initialize(Stream *) __asm__("Initialize___dupe3");
	void Start(Stream *) __asm__("Start___dupe2");
	static Stream *GetStreamFromHandle(unsigned int) __asm__("GetStreamFromHandle");
	static void Free(Stream *) __asm__("Free");
	unsigned int Alloc(Stream **) __asm__("Alloc");
	void Update(float) __asm__("Update___dupe54");
	void WaitForStop(Stream **, int, void (*)(void *), void *) __asm__("WaitForStop");
};

#endif
