/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_setenv_failed(const char *envname, const char *envval, int overwrite)
{
	const char *desc = "";
	if (!envname) {
		if (!envval)
			desc = "Environment variable name and value are NULL";
		else
			desc = "Environment variable name is NULL";
	} else if (!envval) {
		desc = "Environment variable value is NULL";
	} else if (!*envname) {
		desc = "Environment variable name is the empty string";
	} else if (errno == EINVAL) {
		desc = "Environment variable name contains the '=' character";
	}
	liberror_set_error_errno(desc, "setenv", errno);
	(void) overwrite;
}


int
liberror_setenv(const char *envname, const char *envval, int overwrite)
{
	const char *desc = "";
	if (!envname) {
		errno = EINVAL;
		if (!envval)
			desc = "Environment variable name and value are NULL";
		else
			desc = "Environment variable name is NULL";
		goto error;
	} else if (!envval) {
		errno = EINVAL;
		desc = "Environment variable value is NULL";
		goto error;
	} else if (!setenv(envname, envval, overwrite)) {
		return 0;
	} else if (!*envname) {
		desc = "Environment variable name is the empty string";
	} else if (errno == EINVAL) {
		desc = "Environment variable name contains the '=' character";
	}
error:
	liberror_save_backtrace(NULL);
	liberror_set_error_errno(desc, "setenv", errno);
	return -1;
}
