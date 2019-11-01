/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_realloc_failed(void *ptr, size_t n)
{
	liberror_set_error_errno("Out of memory", "realloc", ENOMEM);
	errno = ENOMEM;
	(void) ptr;
	(void) n;
}


void *
liberror_realloc(void *ptr, size_t n)
{
	void *ret = realloc(ptr, n);
	if (ret || !n)
		return ret;
	liberror_save_backtrace(NULL);
	liberror_realloc_failed(ptr, n);
	return NULL;
}
