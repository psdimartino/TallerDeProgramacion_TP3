#ifndef COMMON_SRC_OSERROR_H_
#define COMMON_SRC_OSERROR_H_

#include <exception>
#define BUF_LEN 128

class OSError : public std::exception {
    int _errno;
    char msg_error[BUF_LEN] = {0};
 public:
    OSError(const char*fmt, ...) noexcept;
    const char * what() const throw();
};

#endif  // COMMON_SRC_OSERROR_H_
