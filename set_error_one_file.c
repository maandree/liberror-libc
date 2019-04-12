/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_libc_set_error_one_file(const char desc[256], const char source[64], const char *frole, int fd, const char *fname)
{
	struct liberror_error *error;
	int saved_errno = errno;
	liberror_set_error_errno(desc, source, saved_errno);
	error = liberror_get_error();
	error->details_type = LIBERROR_DETAILS_ONE_FILE;
	error->details.one_file.fd = fd;
	error->details.one_file.name = fname ? strdup(fname) : NULL;
	error->details.one_file.role = frole;
	errno = saved_errno;
}
