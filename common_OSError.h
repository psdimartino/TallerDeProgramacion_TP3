#ifndef COMMON_OSERROR_H_
#define COMMON_OSERROR_H_

#define BUF_LEN 128

class OSError {
    int _errno;
    char msg_error[BUF_LEN] = {0};
 public:
    OSError(const char*fmt, ...) noexcept;
};

#endif  // COMMON_OSERROR_H_
