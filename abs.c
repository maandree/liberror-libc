/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_abs_failed(int i)
{
	liberror_set_error_errno("The absolute value of largest negative integer "
	                         "cannot be represented as a signed integer",
	                         "abs", EOVERFLOW);
	(void) i;
}


int
liberror_abs(int i)
{
#if INT_MIN == -INT_MAX
	return abs(i);
#else
	if (i != INT_MIN)
		return abs(i);
	liberror_save_backtrace(NULL);
	liberror_abs_failed(i);
	return i;
#endif
}
