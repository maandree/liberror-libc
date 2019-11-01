/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_labs_failed(long int i)
{
	liberror_set_error_errno("The absolute value of largest negative integer "
	                         "cannot be represented as a signed integer",
	                         "labs", EOVERFLOW);
	(void) i;
}


long int
liberror_labs(long int i)
{
#if LONG_MIN == -LONG_MAX
	return labs(i);
#else
	if (i != LONG_MIN)
		return labs(i);
	liberror_save_backtrace(NULL);
	liberror_labs_failed(i);
	return i;
#endif
}
