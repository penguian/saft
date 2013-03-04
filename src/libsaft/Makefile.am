AM_CPPFLAGS =			\
	$(GSL_CFLAGS)

libmmiodir = $(top_srcdir)/src/libmmio
libsaftdir = $(top_srcdir)/src/libsaft

INCLUDES =			\
	-I$(libmmiodir) 	\
	-I$(libsaftdir)

lib_LTLIBRARIES =		\
	libsaft.la

libsaft_sources =		\
	safterror.c		\
	saftfasta.c		\
	safthash.c		\
	saftmatrix.c		\
	saftsearch.c		\
	saftsequence.c		\
	saftspectrum.c		\
	saftstats.c

libsaft_headers =		\
	safterror.h		\
	saftfasta.h		\
	safthash.h		\
	saftmatrix.h		\
	saftsearch.h		\
	saftsequence.h		\
	saftspectrum.h		\
	saftstats.h

# FIXME add library version info like that:
#libsaft_la_LDFLAGS =	\
#	-version-info $(LT_VERSION_INFO)
#
libsaft_la_LIBADD =		\
	$(GSL_LIBS)

libsaft_la_SOURCES =		\
	$(libsaft_sources)	\
	$(libsaft_headers)

libsaftincludedir =		\
	$(includedir)/libsaft

libsaftinclude_HEADERS =	\
	$(libsaft_headers)

MAINTAINERCLEANFILES =		\
	Makefile.in
