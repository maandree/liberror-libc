/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_unsetenv_failed(const char *name)
{
	const char *desc = "";
	if (!name)
		desc = "Environment variable name is NULL";
	else if (!*name)
		desc = "Environment variable name is the empty string";
	else if (errno == EINVAL)
		desc = "Environment variable name contains the '=' character";
	liberror_set_error_errno(desc, "unsetenv", errno);
}


int
liberror_unsetenv(const char *name)
{
	if (!unsetenv(name))
		return 0;
	liberror_save_backtrace(NULL);
	liberror_unsetenv_failed(name);
	return -1;
}
