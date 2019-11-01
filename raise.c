/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_raise_failed(int sig)
{
	const char *desc = "";
	if (errno == EINVAL)
		desc = "Invalid signal number";
	liberror_set_error_errno(desc, "raise", errno);
	(void) sig;
}


int
liberror_raise(int sig)
{
	if (!raise(sig))
		return 0;
	liberror_save_backtrace(NULL);
	liberror_raise_failed(sig);
	return -1;
}
