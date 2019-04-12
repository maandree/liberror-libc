/* See LICENSE file for copyright and license details. */
#include "liberror-libc.h"

#include <sys/socket.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void liberror_set_error(const char[256], const char[64], const char[64], long long int);
void liberror_set_error_errno(const char[256], const char[64], int);
