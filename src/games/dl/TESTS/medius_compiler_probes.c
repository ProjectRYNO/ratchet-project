extern void free(void *);
extern void (*gpfFreeCallback)(void *);
extern void *(*gpfMallocCallback)(int);
unsigned rt_strnlen(const char *s,unsigned n){const char *p; const char *end; if(!s)return 0; end=s+n;p=s; while(p<end && *p) ++p; return p-s;}
int rt_memory_get_aligned_address(void **out,void *p,unsigned short a){unsigned rem;if(!out||!p)return 100;*out=p;if(a>1){rem=(unsigned)p%a;if(rem)*out=(void*)((unsigned)p+(a-rem));}return 0;}
int rt_memory_free(void **p){if(*p){if(!gpfFreeCallback){free(*p);*p=0;}else{gpfFreeCallback(*p);*p=0;}}return 0;}
int rt_memory_register_callbacks(void *(*m)(int),void(*f)(void*)){gpfMallocCallback=m;gpfFreeCallback=f;return 0;}
