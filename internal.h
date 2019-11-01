/* See LICENSE file for copyright and license details. */
#include "liberror-libc.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <liberror.h>


#if defined(__GNUC__)
# define GCC_ATTRIBUTES(...) __attribute__((__VA_ARGS__))
#else
# define GCC_ATTRIBUTES(...)
#endif

#define HIDDEN GCC_ATTRIBUTES(__visibility__("hidden"))


HIDDEN void liberror_libc_set_error_one_file(const char[256], const char[64], const char *, int, const char *);
