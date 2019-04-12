/* See LICENSE file for copyright and license details. */
#include "internal.h"


long int
liberror_labs(long int i)
{
#if LONG_MIN == -LONG_MAX
	return labs(i);
#else
	if (i != LONG_MIN)
		return labs(i);
	liberror_set_error_errno("The absolute value of largest negative integer "
	                         "cannot be represented as a signed integer",
	                         "labs", EOVERFLOW);
	return i;
#endif
}
