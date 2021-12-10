/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_recv_failed(int fd, void *buf, size_t n, int flags, const char *fname)
{
	const char *desc;
	int saved_errno, val;
	struct timeval tv;
	switch (errno) {
#if defined(EAGAIN)
	case EAGAIN:
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EAGAIN != EWOULDBLOCK)
	case EWOULDBLOCK:
#endif
#if defined(EAGAIN) || defined(EWOULDBLOCK)
		saved_errno = errno;
		if (flags & MSG_OOB) {
			desc = "Attempting to receive in nonblocking mode but the operation would block, "
			       "attempting to receive with time out and the operation timed out "
			       "or the socket does not support blocking to await out-of-band data";
			if (flags & MSG_DONTWAIT) {
			msg_oob_nonblocking:
				desc = "Attempting to receive in nonblocking mode but the operation would block or"
				       " the socket does not support blocking to await out-of-band data";
			} else if ((val = fcntl(fd, F_GETFL)) < 0) {
				/* Do nothing */
			} else if (val & O_NONBLOCK) {
				goto msg_oob_nonblocking;
			} else if (getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, &(socklen_t){(socklen_t)sizeof(tv)}) ||
			           tv.tv_sec || tv.tv_usec) {
				desc = "Attempting to receive with time out and the operation timed out or"
				       " the socket does not support blocking to await out-of-band data";
			} else {
				desc = "The socket does not support blocking to await out-of-band data";
			}
		} else {
			desc = "Attempting to receive in nonblocking mode but the operation would block "
			       "or attempting to receive with time out and the operation timed out";
			if (flags & MSG_DONTWAIT) {
			no_msg_oob_nonblocking:
				desc = "Attempting to receive in nonblocking mode but the operation would block";
			} else if ((val = fcntl(fd, F_GETFL)) < 0) {
				/* Do nothing */
			} else if (val & O_NONBLOCK) {
				goto no_msg_oob_nonblocking;
			} else if (!getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, &(socklen_t){(socklen_t)sizeof(tv)}) &&
			           !tv.tv_sec && !tv.tv_usec) {
				desc = "Attempting to receive with time out and the operation timed out";
			}
		}
		errno = saved_errno;
		break;
#endif
	case EBADF:
		if (fd < 0)
			desc = "Negative file descriptor number specified";
		else
			desc = "Unassigned file descriptor number specified";
		break;
	case ECONNREFUSED:
		desc = "The remote host refused to allow the network connection";
		break;
	case ECONNRESET:
		desc = "The connection was forcibly closed by a peer";
		break;
	case EFAULT:
		desc = "Invalid user space address specified in the second argument";
		break;
	case EINTR:
		desc = "System call was interrupted by a signal or machine suspension";
		break;
	case EINVAL:
		if (fd < 0)
			desc = "Negative file descriptor number specified";
		else if ((flags & ~(MSG_PEEK | MSG_WAITALL)) == MSG_OOB)
			desc = "No out-of-band data is available";
		else if (flags & MSG_OOB)
			desc = "No out-of-band data is available or non-existing flag is specified";
		else
			desc = "Non-existing flag is specified";
		break;
	case EIO:
		desc = "An I/O error occurred while reading from or writing to the file system";
		break;
	case ENOBUFS:
		desc = "Insufficient resource available in the system to perform the operation";
		break;
	case ENOMEM:
		desc = "Out of memory";
		break;
	case ENOTCONN:
		desc = "The socket is not connected";
		break;
	case ENOTSOCK:
		desc = "The file descriptor refer to a non-socket file";
		break;
	case EOPNOTSUPP:
		desc = "A flag that is not supported for the socket protocol is specified";
		break;
	case ETIMEDOUT:
		desc = "The connection timed out during connection establishment, "
		       "or due to a transmission timeout on active connection";
		break;
	default:
		desc = "";
		break;
	}
	liberror_libc_set_error_one_file(desc, "recv", "Socket file", fd, fname);
}


void
liberror_recv_short(int fd, void *buf, size_t n, int flags, size_t min, size_t max, ssize_t returned, const char *fname)
{
	const char *desc;
	struct liberror_error *error;
	int saved_errno = errno;
	liberror_save_backtrace(NULL);
	if (returned < 0 || (size_t)returned < min) {
		desc = "Received message was shorter than expected";
	} else if (returned > max) {
		desc = "Received message was larger than expected";
	} else {
		desc = "Received message was of an unexpected size";
	}
	liberror_set_error(desc, "recv", "liberror-libc", LIBERROR_LIBC_ERRROR_SHORT_READ);
	error = liberror_get_error();
	error->details_type = LIBERROR_DETAILS_ONE_FILE;
	error->details.one_file.fd = fd;
	error->details.one_file.name = fname ? strdup(fname) : NULL;
	error->details.one_file.role = "Socket file";
	errno = saved_errno;
}


ssize_t
liberror_recv(int fd, void *buf, size_t n, int flags, const char *fname)
{
	ssize_t r = recv(fd, buf, n, flags);
	if (r >= 0)
		return r;
	liberror_save_backtrace(NULL);
	liberror_recv_failed(fd, buf, n, flags, fname);
	return -1;
}


ssize_t
liberror_recv_require(int fd, void *buf, size_t n, int flags, size_t min, size_t max, const char *fname)
{
	ssize_t r = recv(fd, buf, n, flags);
	if (r >= min && r <= max)
		return r;
	liberror_save_backtrace(NULL);
	if (r < 0)
		liberror_recv_failed(fd, buf, n, flags, fname);
	else
		liberror_recv_short(fd, buf, n, flags, min, max, r, fname);
	return -1;
}
