/* See LICENSE file for copyright and license details. */
#include "liberror-libc.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <ctype.h>
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

HIDDEN void liberror_libc_set_error_one_file(const char *, const char *, const char *, int, const char *);
HIDDEN int liberror_libc_check_kernel_version(long int, long int, long int);
