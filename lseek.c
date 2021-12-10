/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_lseek_failed(int fd, _liberror_off_t offset, int whence, const char *fname)
{
	const char *desc;
	int saved_errno = errno;
	switch (saved_errno) {
	case EBADF:
		if (fd < 0)
			desc = "Negative file descriptor number specified";
		else
			desc = "Unassigned file descriptor number specified";
		break;
	case ESPIPE:
		desc = "Unseekable file type (e.g. pipe, socket, or FIFO)";
		break;
	case EOVERFLOW:
		desc = "The resulting offset cannot be represented in an off_t; "
		       "consider compiling with _FILE_OFFSET_BITS=64";
		break;
	case EINVAL:
		if (whence == SEEK_SET || whence == SEEK_END || whence == SEEK_CUR) {
			if (offset < 0)
				desc = "Attempted to seek to a position before the beginning of the file";
			else if (offset > 0)
				desc = "Attempted to seek beyond the end of the device";
			else if (whence == SEEK_SET)
				desc = "Failed, for unknown reason, to seek to the beginning of the file";
			else if (whence == SEEK_END)
				desc = "Failed, for unknown reason, to seek to the end of the device";
			else
				desc = "Failed, for unknown reason, to look up current file offset";
		} else {
			desc = "Unsupported seek mode";
			if (whence == SEEK_DATA || whence == SEEK_HOLE) {
#if defined(__linux__)
				if (!liberror_libc_check_kernel_version(3, 1, 0))
					desc = "Unsupported seek mode; requires Linux 3.1 or newer";
#else
# error Unsupported kernel
#endif
		}
		}
		break;
	case ENXIO:
		if (whence == SEEK_DATA) {
			if (offset < 0) {
				desc = "Attempted seek for data beginning at an offset before the beginning of the file";
			} else {
				desc = "Seeking for data from a hold at the end of the file, or at or after the end of the file";
			}
		} else if (whence == SEEK_HOLE) {
			if (offset < 0) {
				desc = "Attempted seek for a hole beginning at an offset before the beginning of the file";
			} else {
				desc = "Attempted seek for a hole from the end of the file, or after it's end";
			}
		}
		break;
	default:
		desc = "";
		break;
	}
	liberror_libc_set_error_one_file(desc, "sockatmark", "Seekable file", fd, fname);
	errno = saved_errno;
}


void
liberror_lseek_short(int fd, _liberror_off_t offset, int whence, _liberror_uoff_t min,
                     _liberror_uoff_t max, _liberror_off_t returned, const char *fname)
{
	const char *desc;
	struct liberror_error *error;
	int saved_errno = errno;
	liberror_save_backtrace(NULL);
	if (returned < 0 || (size_t)returned < min) {
		desc = "Seek resulted in a new offset in an earlier position than expected";
	} else if (returned > max) {
		desc = "Seek resulted in a new offset in an beyond the expectation";
	} else {
		desc = "Seek resulted in an unexpected new offset";
	}
	liberror_set_error(desc, "recv", "liberror-libc", LIBERROR_LIBC_ERRROR_SHORT_SEEK);
	error = liberror_get_error();
	error->details_type = LIBERROR_DETAILS_ONE_FILE;
	error->details.one_file.fd = fd;
	error->details.one_file.name = fname ? strdup(fname) : NULL;
	error->details.one_file.role = "Seekable file";
	errno = saved_errno;
}


_liberror_off_t
liberror_lseek(int fd, _liberror_off_t offset, int whence, const char *fname)
{
	_liberror_off_t r = lseek(fd, offset, whence);
	if (r >= 0)
		return r;
	liberror_save_backtrace(NULL);
	liberror_lseek_failed(fd, offset, whence, fname);
	return -1;
}


_liberror_off_t
liberror_lseek_require(int fd, _liberror_off_t offset, int whence, _liberror_uoff_t min, _liberror_uoff_t max, const char *fname)
{
	_liberror_off_t r = lseek(fd, offset, whence);
	if (r >= 0 && (_liberror_uoff_t)r >= min && (_liberror_uoff_t)r <= max)
		return r;
	liberror_save_backtrace(NULL);
	if (r < 0)
		liberror_lseek_failed(fd, offset, whence, fname);
	else
		liberror_lseek_short(fd, offset, whence, min, max, r, fname);
	return -1;
}
