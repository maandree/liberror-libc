/* See LICENSE file for copyright and license details. */
#include "internal.h"


int
liberror_libc_check_kernel_version(long int major, long int minor, long int patch)
{
#if defined(__linux__)

	struct utsname name;
	long int kmajor;
	long int kminor;
	long int kpatch;
	char *p;
	int r;

	r = uname(&name);
	if (r < 0)
		return -1;

	errno = 0;
	p = name.release;
	if (!isdigit(*p))
		return -1;
	kmajor = strtol(p, &p, 10);
	if (kmajor < 0 || errno || *p != '.')
		return -1;
	kminor = strtol(&p[1], &p, 10);
	if (kminor < 0 || errno)
		return -1;
	if (*p != '.') {
		kpatch = 0;
	} else {
		kpatch = strtol(&p[1], &p, 10);
		if (kpatch < 0 || errno)
			return -1;
	}

	return kmajor != major ? kmajor > major :
	       kminor != minor ? kminor > minor : kpatch >= patch;

#else
# error Unsupported kernel
#endif
}
