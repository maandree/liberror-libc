/* See LICENSE file for copyright and license details. */
#include "internal.h"


void
liberror_chdir_failed(const char *path)
{
	const char *desc;
	switch (errno) {
	case EFAULT:
		if (!path)
			desc = "Path parameter is NULL";
		else
			desc = "Path parameter is an invalid pointer";
		break;
	case EACCES:
		desc = "Search permission is denied for any component of the path";
		break;
	case ELOOP:
		desc = "A symbolic link chain in the path too long or circular";
		break;
	case ENAMETOOLONG:
		desc = "The canonical path or intermediate result in pathname resolution is too long";
		break;
	case ENOENT:
		if (!*path)
			desc = "Path parameter is the empty string";
		else
			desc = "A component of path does not name an existing directory";
		break;
	case ENOTDIR:
		desc = "A component of path is not a directory";
		break;
	case ENOMEM:
		desc = "Insufficient kernel memory was available";
		break;
	case EIO:
	default:
		desc = "";
		break;
	}
	liberror_libc_set_error_one_file(desc, "chdir", "Directory file", -1, path);
}


int
liberror_chdir(const char *path)
{
	if (!chdir(path))
		return 0;
	liberror_save_backtrace(NULL);
	liberror_chdir_failed(path);
	return -1;
}
