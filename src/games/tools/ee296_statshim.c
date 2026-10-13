/*
 * LD_PRELOAD shim for the 32-bit Sony ee-gcc 2.96 binaries.
 *
 * Those binaries call the legacy __xstat/__fxstat entry points, whose struct
 * stat has a 32-bit st_ino. Docker Desktop bind mounts report 64-bit inode
 * numbers, so glibc fails every stat with EOVERFLOW and the compiler cannot
 * open its sources. This shim performs the 64-bit call and folds the inode
 * into 32 bits. Nothing else about the compiler is altered.
 *
 * Build: gcc -m32 -shared -fPIC -O2 -o ee296_statshim.so ee296_statshim.c
 */
#define _LARGEFILE64_SOURCE
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

static int fill(struct stat *out, const struct stat64 *in)
{
    if (in->st_size > 0x7FFFFFFFLL) {
        errno = EOVERFLOW;
        return -1;
    }
    memset(out, 0, sizeof(*out));
    out->st_dev = in->st_dev;
    out->st_ino = (ino_t)(in->st_ino ^ (in->st_ino >> 32));
    out->st_mode = in->st_mode;
    out->st_nlink = in->st_nlink;
    out->st_uid = in->st_uid;
    out->st_gid = in->st_gid;
    out->st_rdev = in->st_rdev;
    out->st_size = (off_t)in->st_size;
    out->st_blksize = in->st_blksize;
    out->st_blocks = in->st_blocks;
    out->st_atime = in->st_atime;
    out->st_mtime = in->st_mtime;
    out->st_ctime = in->st_ctime;
    return 0;
}

int __xstat(int ver, const char *path, struct stat *buf)
{
    struct stat64 st;
    (void)ver;
    if (stat64(path, &st)) return -1;
    return fill(buf, &st);
}

int __lxstat(int ver, const char *path, struct stat *buf)
{
    struct stat64 st;
    (void)ver;
    if (lstat64(path, &st)) return -1;
    return fill(buf, &st);
}

int __fxstat(int ver, int fd, struct stat *buf)
{
    struct stat64 st;
    (void)ver;
    if (fstat64(fd, &st)) return -1;
    return fill(buf, &st);
}
