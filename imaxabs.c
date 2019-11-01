/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_imaxabs_failed(intmax_t i)
{
	liberror_set_error_errno("The absolute value of largest negative integer "
	                         "cannot be represented as a signed integer",
	                         "imaxabs", EOVERFLOW);
	(void) i;
}


intmax_t
liberror_imaxabs(intmax_t i)
{
#if INTMAX_MIN == -INTMAX_MAX
	return imaxabs(i);
#else
	if (i != INTMAX_MIN)
		return imaxabs(i);
	liberror_save_backtrace(NULL);
	liberror_imaxabs_failed(i);
	return i;
#endif
}
