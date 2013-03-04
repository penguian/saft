libmmiodir = $(top_srcdir)/src/libmmio
libsaftdir = $(top_srcdir)/src/libsaft

INCLUDES =			\
	-I$(libmmiodir) 	\
	-I$(libsaftdir)

AM_CPPFLAGS =			\
	-DSAFT_VERSION=\"$(PACKAGE_VERSION)\"

bin_PROGRAMS =	saft

saft_LDADD =				\
	$(libsaftdir)/libsaft.la	\
	$(libmmiodir)/libmmio.la

saft_SOURCES =			\
	saftmain.c

MAINTAINERCLEANFILES =		\
	Makefile.in
