/* See LICENSE file for copyright and license details. */
#include "internal.h"


int
liberror_pipe(int fds[2])
{
	const char *desc;
	if (!fds) {
		desc = "Output parameter is NULL";
		goto error;
	}
	if (!pipe(fds))
		return 0;
	switch (errno) {
	case EFAULT:
		desc = "Output parameter is an invalid pointer";
		break;
	case EMFILE:
		desc = "The process have too many file descriptors open";
		break;
	case ENFILE:
		desc = "The system have too many file descriptors open";
		break;
	default:
		desc = "";
		break;
	}
error:
	liberror_set_error_errno(desc, "pipe", errno);
	return -1;
}
