/* See LICENSE file for copyright and license details. */
#include "internal.h"


int
liberror_unsetenv(const char *name)
{
	const char *desc = "";
	if (!name) {
		errno = EINVAL;
		desc = "Environment variable name is NULL";
		goto error;
	} else if (!unsetenv(name)) {
		return 0;
	} else if (!*name) {
		desc = "Environment variable name is the empty string";
	} else if (errno == EINVAL) {
		desc = "Environment variable name contains the '=' character";
	}
error:
	liberror_set_error_errno(desc, "setenv", errno);
	return -1;
}
