/* See LICENSE file for copyright and license details. */
#include "internal.h"


int
liberror_putenv(char *string)
{
	const char *desc = "";
	if (!string) {
		errno = EINVAL;
		desc = "Environment string is NULL";
		goto error;
	} else if (*string == '=') {
		errno = EINVAL;
		desc = "Environment variable name is the empty string";
		goto error;
	} else if (!strchr(string, '=')) {
		errno = EINVAL;
		desc = "Environment does not contain an '=' symbol";
		goto error;
	} else if (!putenv(string)) {
		return 0;
	}
error:
	liberror_save_backtrace(NULL);
	liberror_set_error_errno(desc, "putenv", errno);
	return -1;
}
