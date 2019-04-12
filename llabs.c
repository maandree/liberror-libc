/* See LICENSE file for copyright and license details. */
#include "internal.h"


long long int
liberror_llabs(long long int i)
{
#if LLONG_MIN == -LLONG_MAX
	return llabs(i);
#else
	if (i != LLONG_MIN)
		return llabs(i);
	liberror_save_backtrace(NULL);
	liberror_set_error_errno("The absolute value of largest negative integer "
	                         "cannot be represented as a signed integer",
	                         "llabs", EOVERFLOW);
	return i;
#endif
}
