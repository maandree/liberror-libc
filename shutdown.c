/* See LICENSE file for copyright and license details. */
#include "internal.h"


int
liberror_shutdown(int fd, int how)
{
	const char *desc;
	if (!shutdown(fd, how))
		return 0;
	switch (errno) {
	case EBADF:
		desc = fd < 0 ? "Negative file descriptor number specified" : "Unassigned file descriptor number specified";
		break;
	case EINVAL:
		desc = "Invalid value of second parameter";
		break;
	case ENOTCONN:
		desc = "The socket is not connected";
		break;
	case ENOTSOCK:
		desc = "The specified file is not a socket";
		break;
	case ENOBUFS:
		desc = "Insufficient resource available in the system to perform the operation";
		break;
	default:
		desc = "";
		break;
	}
	liberror_set_error_errno(desc, "shutdown", errno);
	return -1;
}
