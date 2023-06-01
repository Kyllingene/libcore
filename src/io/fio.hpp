#ifndef _CORE_FIOH
#define _CORE_FIOH

#include "../str/str.hpp"
#include "../types/types.hpp"

namespace core {

    const int O_RDONLY =          00;
    const int O_WRONLY =          01;
    const int O_RDWR =            02;
    const int O_ACCMODE =         03;
    const int O_CREAT =         0100;
    const int O_EXCL =          0200;
    const int O_NOCTTY =        0400;
    const int O_TRUNC =        01000;
    const int O_APPEND =       02000;
    const int O_NONBLOCK =     04000;
    const int O_DSYNC =       010000;
    const int O_ASYNC =       020000;
    const int O_DIRECT =      040000;
    const int O_LARGEFILE =  0200000;
    const int O_DIRECTORY =  0100000;
    const int O_NOFOLLOW =   0400000;
    const int O_NOATIME =   01000000;
    const int O_CLOEXEC =   02000000;
    const int O_SYNC =      04010000;
    const int O_PATH =     010000000;
    const int O_TMPFILE = (020000000 | O_DIRECTORY);

    //! Create a new file or delete existing contents.
    const int O_NEWFILE = (O_WRONLY | O_CREAT | O_TRUNC);
    //! Append to an existing file.
    const int O_APPFILE = (O_WRONLY | O_APPEND);
    //! Read from an existing file.
    const int O_RDFILE = O_RDONLY;

    //! User execute bit.
    const int O_UEX = 00100;
    //! User write bit.
    const int O_UWR = 00200;
    //! User read bit.
    const int O_URD = 00400;
    //! Group execute bit.
    const int O_GEX = 00010;
    //! Group write bit.
    const int O_GWR = 00020;
    //! Group read bit.
    const int O_GRD = 00040;
    //! Other execute bit.
    const int O_OEX = 00001;
    //! Other write bit.
    const int O_OWR = 00002;
    //! Other read bit.
    const int O_ORD = 00004;

    //! Sticky bit.
    const int O_SBT = 01000;

    //! GID bit.
    const int O_GID = 02000;

    //! UID bit.
    const int O_UID = 04000;

    //! Default user file mode (rw-r--r--). 
    const int O_DMODE = (O_URD | O_UWR | O_GRD | O_ORD);

    //! Open a file with default mode (rw-r--r--).
    filed open(const char* filename, int flags);

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

    class ofstream {
        filed fd;

    public:
        ofstream(filed fd);
        ofstream(const char* filename, int flags, int mode);
        ~ofstream();
        
        ofstream operator<<(const char* str);
        ofstream operator<<(char ch);
        ofstream operator<<(ssize_t i);
        ofstream operator<<(int i);
        ofstream operator<<(double d);
    };

    //! Similar to the std::cout object.
    static ofstream cout(1);

#if _WIN32 || _WIN64
    //! A platform-appropriate newline (on Windows, CRLF).
    static const char* endl = "\r\n";
#else
    //! A platform-appropriate newline (on Unix, LF).
    static const char* endl = "\n";
#endif

}

#endif
