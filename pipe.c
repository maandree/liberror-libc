/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_pipe_failed(int fds[2])
{
	const char *desc;
	switch (errno) {
	case EFAULT:
		if (!fds)
			desc = "Output parameter is NULL";
		else
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
	liberror_set_error_errno(desc, "pipe", errno);
	(void) fds;
}


int
liberror_pipe(int fds[2])
{
	if (!pipe(fds))
		return 0;
	liberror_save_backtrace(NULL);
	liberror_pipe_failed(fds);
	return -1;
}
