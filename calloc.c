/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_calloc_failed(size_t n, size_t m)
{
	liberror_set_error_errno("Out of memory", "calloc", ENOMEM);
	errno = ENOMEM;
	(void) n;
	(void) m;
}


void *
liberror_calloc(size_t n, size_t m)
{
	void *ret = calloc(n, m);
	if (ret || !n || !m)
		return ret;
	liberror_save_backtrace(NULL);
	liberror_calloc_failed(n, m);
	return NULL;
}
