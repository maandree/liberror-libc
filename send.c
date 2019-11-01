/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_send_failed(int fd, const void *buf, size_t n, int flags, const char *fname)
{
	const char *desc;
	int saved_errno, val;
	struct sockaddr_storage addr;
	socklen_t len = 0;
	switch (errno) {
	case EACCES:
		desc = "The calling process does not have appropriate privileges";
		saved_errno = errno;
		if (getsockopt(fd, SOL_SOCKET, SO_DOMAIN, &val, &(socklen_t){(socklen_t)sizeof(val)})) {
			/* Do nothing */
		} else if (val == PF_LOCAL) {
			desc = "Write or search permission to the destination socket file is denied";
		} else if (val != PF_INET && val != PF_INET6) {
			/* Do nothing */
		} else if (getsockopt(fd, SOL_SOCKET, SO_TYPE, &val, &(socklen_t){(socklen_t)sizeof(val)})) {
			/* Do nothing */
		} else if (val != SOCK_DGRAM) {
			/* Do nothing */
		} else if (getsockopt(fd, SOL_SOCKET, SO_PROTOCOL, &val, &(socklen_t){(socklen_t)sizeof(val)})) {
			/* Do nothing */
		} else if (val == IPPROTO_UDP) {
			desc = "An attempt was made to send to a network/broadcast address as though it was a unicast address";
		}
		errno = saved_errno;
		break;
#if defined(EAGAIN)
	case EAGAIN:
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EAGAIN != EWOULDBLOCK)
	case EWOULDBLOCK:
#endif
#if defined(EAGAIN) || defined(EWOULDBLOCK)
		desc = "Attempting to send in nonblocking mode but the operation would block "
			"or the socket is unbound and all ephemeral ports are currently in used";
# if defined(EAGAIN)
#  if defined(EWOULDBLOCK) && (EAGAIN != EWOULDBLOCK)
		if (errno == EAGAIN) {
#  endif
			saved_errno = errno;
			if (getsockopt(fd, SOL_SOCKET, SO_TYPE, &val, &(socklen_t){(socklen_t)sizeof(val)})) {
				/* Do nothing */
			} else if (val != SOCK_DGRAM) {
				goto first_case_in_eagain;
			} else if (getsockopt(fd, SOL_SOCKET, SO_DOMAIN, &val, &(socklen_t){(socklen_t)sizeof(val)})) {
				/* Do nothing */
			} else if (val != PF_INET && val != PF_INET6) {
				goto first_case_in_eagain;
			} else if (len = 0, getsockname(fd, (void *)&addr, &len)) {
				/* Do nothing */
			} else if ((len && addr.ss_family == AF_INET && ((struct sockaddr_in *)&addr)->sin_port) ||
				   (len && addr.ss_family == AF_INET6 && ((struct sockaddr_in6 *)&addr)->sin6_port)) {
			first_case_in_eagain:
				desc = "Attempting to send in nonblocking mode but the operation would block";
			}
			errno = saved_errno;
#  if defined(EWOULDBLOCK) && (EAGAIN != EWOULDBLOCK)
		} else {
			goto first_case_in_eagain:
		}
#  endif
# endif
		break;
#endif
	case EALREADY:
		desc = "Another Fast Open is already in progress";
		break;
	case EBADF:
		if (fd < 0)
			desc = "Negative file descriptor number specified";
		else
			desc = "Unassigned file descriptor number specified";
		break;
	case ECONNRESET:
		desc = "The peer has closed the connection without reading all received messages";
		break;
	case EDESTADDRREQ:
		desc = "The no peer address is set";
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
		else
			desc = "Non-existing flag is specified";
		break;
	case EIO:
		desc = "An I/O error occurred while reading from or writing to the file system";
		break;
	case EISCONN:
		desc = "The recipient is specified but the socket is already connected";
		break;
	case EMSGSIZE:
		desc = "Message is to large to be sent atomically as required by the socket type";
		break;
	case ENETDOWN:
		desc = "All local network interfaces that can be used to reach the destination are down";
		break;
	case ENETUNREACH:
		desc = "No route to the network it present";
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
	case EPIPE:
		desc = "The socket is shut down for writing or is no longer connected";
		saved_errno = errno;
		if (getsockopt(fd, SOL_SOCKET, SO_TYPE, &val, &(socklen_t){(socklen_t)sizeof(val)})) {
			/* Do nothing */
		} else if (val == SOCK_DGRAM) {
			desc = "The socket is shut down";
		} else if (getpeername(fd, (void *)&addr, &len) && errno == ENOTCONN) {
			desc = "The socket is no longer connected";
		}
		errno = saved_errno;
		break;
	default:
		desc = "";
		break;
	}
	liberror_libc_set_error_one_file(desc, "send", "Socket file", fd, fname);
}


ssize_t
liberror_send(int fd, const void *buf, size_t n, int flags, const char *fname)
{
	ssize_t r = send(fd, buf, n, flags);
	if (r >= 0)
		return r;
	liberror_save_backtrace(NULL);
	liberror_send_failed(fd, buf, n, flags, fname);
	return -1;
}
