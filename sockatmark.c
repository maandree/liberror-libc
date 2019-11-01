/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_sockatmark_failed(int fd, const char *fname)
{
	const char *desc;
	switch (errno) {
	case EBADF:
		if (fd < 0)
			desc = "Negative file descriptor number specified";
		else
			desc = "Unassigned file descriptor number specified";
		break;
	case ENOTSOCK:
	case ENOTTY:
	case EINVAL:
		desc = "Operation not supported by specified file";
		break;
	default:
		desc = "";
		break;
	}
	liberror_libc_set_error_one_file(desc, "sockatmark", "Socket file", fd, fname);
}


int
liberror_sockatmark(int fd, const char *fname)
{
	if (!sockatmark(fd))
		return 0;
	liberror_save_backtrace(NULL);
	liberror_sockatmark_failed(fd, fname);
	return -1;
}
