AM_CPPFLAGS =			\
	$(GSL_CFLAGS)

lib_LTLIBRARIES =		\
	libmmio.la

libmmio_sources =		\
	mmio.c

libmmio_headers =		\
	mmio.h

# FIXME add library version info like that:
#libmmio_la_LDFLAGS =	\
#	-version-info $(LT_VERSION_INFO)
#
libmmio_la_SOURCES =		\
	$(libmmio_sources)	\
	$(libmmio_headers)

libmmioincludedir =		\
	$(includedir)/libmmio

libmmioinclude_HEADERS =	\
	$(libmmio_headers)

MAINTAINERCLEANFILES =		\
	Makefile.in
