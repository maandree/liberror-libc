/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_shutdown_failed(int fd, int how, const char *fname)
{
	const char *desc;
	switch (errno) {
	case EBADF:
		if (fd < 0)
			desc = "Negative file descriptor number specified";
		else
			desc = "Unassigned file descriptor number specified";
		break;
	case EINVAL:
		desc = "Invalid value of second parameter";
		break;
	case ENOBUFS:
		desc = "Insufficient resource available in the system to perform the operation";
		break;
	case ENOTCONN:
		desc = "The socket is not connected";
		break;
	case ENOTSOCK:
		desc = "The file descriptor refer to a non-socket file";
		break;
	default:
		desc = "";
		break;
	}
	liberror_libc_set_error_one_file(desc, "shutdown", "Socket file", fd, fname);
}


int
liberror_shutdown(int fd, int how, const char *fname)
{
	if (!shutdown(fd, how))
		return 0;
	liberror_save_backtrace(NULL);
	liberror_shutdown_failed(fd, how, fname);
	return -1;
}
