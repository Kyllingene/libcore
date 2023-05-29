#ifndef _CORE_IOH
#define _CORE_IOH

#include "../types/types.hpp"

#define O_RDONLY          00
#define O_WRONLY          01
#define O_RDWR            02
#define O_ACCMODE         03
#define O_CREAT         0100
#define O_EXCL          0200
#define O_NOCTTY        0400
#define O_TRUNC        01000
#define O_APPEND       02000
#define O_NONBLOCK     04000
#define O_DSYNC       010000
#define O_ASYNC       020000
#define O_DIRECT      040000
#define O_LARGEFILE  0200000
#define O_DIRECTORY  0100000
#define O_NOFOLLOW   0400000
#define O_NOATIME   01000000
#define O_CLOEXEC   02000000
#define O_SYNC      04010000
#define O_PATH     010000000
#define O_TMPFILE (020000000 | O_DIRECTORY)

#define O_NEWFILE (O_WRONLY | O_CREAT | O_TRUNC)
#define O_RDFILE O_RDONLY

#define O_UEX 00100
#define O_UWR 00200
#define O_URD 00400
#define O_GEX 00010
#define O_GWR 00020
#define O_GRD 00040
#define O_OEX 00001
#define O_OWR 00002
#define O_ORD 00004
#define O_SBT 01000
#define O_GID 02000
#define O_UID 04000

#define O_DMODE (O_URD | O_UWR | O_GRD | O_ORD)

//! Print a string with a length, doesn't need to be null-terminated.
void printl(const char* str, size_t len);

//! Print a valid C string.
void print(const char* str);

//! Get a single character from stdin.
char getch();

//! Read a line from stdin.
char* getl();

//! Open a file.
filed open(const char* filename, int flags, int mode);

//! Create a file.
filed create(const char* filename, int mode);

//! Close a file.
void close(filed fd);

//! Read from a file.
ssize_t read(filed fd, char* buf, size_t count);

//! Write to a file.
ssize_t write(filed fd, const char* buf, size_t count);

#endif