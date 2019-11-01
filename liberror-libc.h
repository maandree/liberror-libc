/* See LICENSE file for copyright and license details. */
#ifndef LIBERROR_LIBC_H
#define LIBERROR_LIBC_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>


int liberror_abs(int);
void liberror_abs_failed(int);
/* void *liberror_aligned_alloc(size_t, size_t); TODO */
void *liberror_calloc(size_t, size_t);
void liberror_calloc_failed(size_t, size_t);
int liberror_chdir(const char *);
void liberror_chdir_failed(const char *);
intmax_t liberror_imaxabs(intmax_t);
void liberror_imaxabs_failed(intmax_t);
long int liberror_labs(long int);
void liberror_labs_failed(long int);
long long int liberror_llabs(long long int);
void liberror_llabs_failed(long long int);
void *liberror_malloc(size_t);
void liberror_malloc_failed(size_t);
int liberror_pipe(int[2]);
void liberror_pipe_failed(int[2]);
int liberror_putenv(char *);
void liberror_putenv_failed(char *);
int liberror_raise(int);
void liberror_raise_failed(int);
void *liberror_realloc(void *, size_t);
void liberror_realloc_failed(void *, size_t);
ssize_t liberror_recv(int, void *, size_t, int, const char *);
void liberror_recv_failed(int, void *, size_t, int, const char *);
/* void *liberror_posix_memalign(void **, size_t, size_t); TODO */
ssize_t liberror_send(int, const void *, size_t, int, const char *);
void liberror_send_failed(int, const void *, size_t, int, const char *);
int liberror_setenv(const char *, const char *, int);
int liberror_shutdown(int, int, const char *);
void liberror_shutdown_failed(int, int, const char *);
int liberror_sockatmark(int, const char *);
void liberror_sockatmark_failed(int, const char *);
int liberror_unsetenv(const char *);
void liberror_unsetenv_failed(const char *);


#endif
