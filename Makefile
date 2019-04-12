.POSIX:

CONFIGFILE = config.mk
include $(CONFIGFILE)

OS = linux
# linux = Linux
# macos = Mac OS
include $(OS).mk

LIB_MAJOR = 1
LIB_MINOR = 0
LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)


HDR =\
	liberror-libc.h\
	liberror.h\
	internal.h

OBJ =\
	abs.o\
	imaxabs.o\
	labs.o\
	llabs.o\
	pipe.o\
	putenv.o\
	set_error_one_file.o\
	setenv.o\
	shutdown.o\
	unsetenv.o

LOBJ = $(OBJ:.o=.lo)


all: liberror-libc.a liberror-libc.$(LIBEXT)
$(OBJ): $(@:.o=.c) $(HDR)
$(LOBJ): $(@:.lo=.c) $(HDR)

liberror-libc.a: $(OBJ)
	-rm -f -- $@
	$(AR) rc $@ $(OBJ)
	$(AR) s $@

liberror-libc.$(LIBEXT): $(LOBJ)
	$(CC) $(LIBFLAGS) -o $@ $(LOBJ) $(LDFLAGS)

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

.c.lo:
	$(CC) -c -o $@ $< -fPIC $(CFLAGS) $(CPPFLAGS)

install: liberror-libc.a liberror-libc.$(LIBEXT)
	mkdir -p -- "$(DESTDIR)$(PREFIX)/lib"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/include"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/licenses/liberror-libc"
	cp -- liberror-libc.a "$(DESTDIR)$(PREFIX)/lib"
	cp -- liberror-libc.$(LIBEXT) "$(DESTDIR)$(PREFIX)/lib/liberror-libc.$(LIBMINOREXT)"
	ln -sf -- liberror-libc.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/liberror-libc.$(LIBMAJOREXT)"
	ln -sf -- liberror-libc.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/liberror-libc.$(LIBEXT)"
	cp -- liberror-libc.h "$(DESTDIR)$(PREFIX)/include"
	cp -- LICENSE "$(DESTDIR)$(PREFIX)/licenses/liberror-libc"

uninstall:
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/liberror-libc."*
	-rm -f -- "$(DESTDIR)$(PREFIX)/include/liberror-libc.h"
	-rm -rf -- "$(DESTDIR)$(PREFIX)/licenses/liberror-libc"

clean:
	-rm -f -- *.o *.lo *.a *.so *.so.* *.su *.test

.SUFFIXES:
.SUFFIXES: .c .o .lo .a

.PHONY: all install uninstall clean
