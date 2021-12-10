/* See LICENSE file for copyright and license details. */
#ifndef LIBERROR_LIBC_H
#define LIBERROR_LIBC_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>


#if defined(__GNUC__)
# define _LIBERROR_GCC_ONLY(...) __VA_ARGS__
#else
# define _LIBERROR_GCC_ONLY(...)
#endif

#define _LIBERROR_WUR _LIBERROR_GCC_ONLY(__attribute__((__warn_unused_result__)))
#define _LIBERROR_MALLOC _LIBERROR_GCC_ONLY(__attribute__((__malloc__)))


#define LIBERROR_LIBC_ERRROR_SHORT_READ -1
#define LIBERROR_LIBC_ERRROR_SHORT_SEEK -2
#define LIBERROR_LIBC_ERRROR_SHORT_WRITE -3


typedef int64_t _liberror_off_t;
typedef uint64_t _liberror_uoff_t;


_LIBERROR_WUR int liberror_abs(int);
void liberror_abs_failed(int);
/* _LIBERROR_WUR _LIBERROR_MALLOC void *liberror_aligned_alloc(size_t, size_t); TODO */
_LIBERROR_WUR _LIBERROR_MALLOC void *liberror_calloc(size_t, size_t);
void liberror_calloc_failed(size_t, size_t);
_LIBERROR_WUR int liberror_chdir(const char *);
void liberror_chdir_failed(const char *);
_LIBERROR_WUR intmax_t liberror_imaxabs(intmax_t);
void liberror_imaxabs_failed(intmax_t);
_LIBERROR_WUR long int liberror_labs(long int);
void liberror_labs_failed(long int);
_LIBERROR_WUR long long int liberror_llabs(long long int);
void liberror_llabs_failed(long long int);
_LIBERROR_WUR _liberror_off_t liberror_lseek(int, _liberror_off_t, int, const char *);
_LIBERROR_WUR _liberror_off_t liberror_lseek_require(int, _liberror_off_t, int, _liberror_uoff_t min,
                                                     _liberror_uoff_t max, const char *);
void liberror_lseek_failed(int, _liberror_off_t, int, const char *);
void liberror_lseek_short(int, _liberror_off_t, int, _liberror_uoff_t min, _liberror_uoff_t max,
                          _liberror_off_t returned, const char *);
_LIBERROR_WUR _LIBERROR_MALLOC void *liberror_malloc(size_t);
void liberror_malloc_failed(size_t);
_LIBERROR_WUR int liberror_pipe(int[2]);
void liberror_pipe_failed(int[2]);
_LIBERROR_WUR int liberror_putenv(char *);
void liberror_putenv_failed(char *);
_LIBERROR_WUR int liberror_raise(int);
void liberror_raise_failed(int);
_LIBERROR_WUR void *liberror_realloc(void *, size_t);
void liberror_realloc_failed(void *, size_t);
_LIBERROR_WUR ssize_t liberror_recv(int, void *, size_t, int, const char *);
_LIBERROR_WUR ssize_t liberror_recv_require(int, void *, size_t, int, size_t min, size_t max, const char *);
void liberror_recv_failed(int, void *, size_t, int, const char *);
void liberror_recv_short(int, void *, size_t, int, size_t min, size_t max, ssize_t returned, const char *);
/* _LIBERROR_WUR void *liberror_posix_memalign(void **, size_t, size_t); TODO */
_LIBERROR_WUR ssize_t liberror_send(int, const void *, size_t, int, const char *);
_LIBERROR_WUR ssize_t liberror_send_require(int, const void *, size_t, int, size_t min, size_t max, const char *);
void liberror_send_failed(int, const void *, size_t, int, const char *);
void liberror_send_short(int, const void *, size_t, int, size_t min, size_t max, ssize_t returned, const char *);
_LIBERROR_WUR int liberror_setenv(const char *, const char *, int);
_LIBERROR_WUR int liberror_shutdown(int, int, const char *);
void liberror_shutdown_failed(int, int, const char *);
_LIBERROR_WUR int liberror_sockatmark(int, const char *);
void liberror_sockatmark_failed(int, const char *);
_LIBERROR_WUR _LIBERROR_MALLOC char *liberror_strdup(const char *);
void liberror_strdup_failed(const char *);
_LIBERROR_WUR int liberror_unsetenv(const char *);
void liberror_unsetenv_failed(const char *);


#endif
