/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_strdup_failed(const char *s)
{
	liberror_set_error_errno(errno == ENOMEM ? "Out of memory" : "", "strdup", errno);
	(void) s;
}


char *
liberror_strdup(const char *s)
{
	char *ret = malloc(s);
	if (ret)
		return ret;
	liberror_save_backtrace(NULL);
	liberror_strdup_failed(s);
	return NULL;
}
