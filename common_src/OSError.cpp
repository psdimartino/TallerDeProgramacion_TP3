#include <iostream>
#include <string.h>
#include <errno.h>
#include <cstdio>
#include <cstdarg>

#include "../common_src/OSError.h"

OSError::OSError(const char* fmt, ...) noexcept {
    _errno = errno;
    va_list args;
    va_start(args, fmt);
    int s = vsnprintf(msg_error, BUF_LEN, fmt, args);
    va_end(args);
    strncpy(msg_error+s, strerror(_errno), BUF_LEN-s);
    msg_error[BUF_LEN-1] = 0;
}

const char * OSError::what() const throw() {
    return msg_error;
}
