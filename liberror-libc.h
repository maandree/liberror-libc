/* See LICENSE file for copyright and license details. */
#ifndef LIBERROR_LIBC_H
#define LIBERROR_LIBC_H

#include <stdint.h>


int liberror_abs(int);
intmax_t liberror_imaxabs(intmax_t);
long int liberror_labs(long int);
long long int liberror_llabs(long long int);
int liberror_pipe(int[2]);
int liberror_putenv(char *);
int liberror_setenv(const char *, const char *, int);
int liberror_shutdown(int, int);
int liberror_unsetenv(const char *);


#endif
