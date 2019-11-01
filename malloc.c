/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_malloc_failed(size_t n)
{
	liberror_set_error_errno("Out of memory", "malloc", ENOMEM);
	errno = ENOMEM;
	(void) n;
}


void *
liberror_malloc(size_t n)
{
	void *ret = malloc(n);
	if (ret || !n)
		return ret;
	liberror_save_backtrace(NULL);
	liberror_malloc_failed(n);
	return NULL;
}
