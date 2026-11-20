#ifndef FS_H
#define FS_H

struct Fs { // 0x1
	static void Initialize() __asm__("Initialize");
	static void Reset() __asm__("Reset");
	static void *GetBuffer() __asm__("GetBuffer");
	static unsigned int IsLoading() __asm__("IsLoading");
	static void Sync(unsigned int) __asm__("Sync");
	static void Abort() __asm__("Abort");
	static void Update(float) __asm__("Update___dupe53");
	static unsigned int Load(int type, unsigned int, unsigned int, unsigned int, unsigned int, void (*)(void *, int), void *) __asm__("Load");
	static unsigned int LoadAsync(int type, unsigned int, unsigned int, unsigned int, unsigned int, void (*)(void *, int), void *) __asm__("LoadAsync");
};

#endif
