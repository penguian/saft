ACLOCAL_AMFLAGS =			\
	-I m4

libsaftdir = $(top_srcdir)/src/libsaft

AM_CPPFLAGS =				\
	-I. -I$(libsaftdir)

noinst_LTLIBRARIES = libtest_harness.la
libtest_harness_la_SOURCES = test_harness.c

noinst_PROGRAMS =			\
	test_safterror			\
	test_saftfasta			\
	test_safthash			\
	test_saftsearch			\
	test_saftsearchenginednaarray	\
	test_saftsearchenginednahash	\
	test_saftsearchenginegeneric	\
	test_saftsearchengines		\
	test_saftsequence		\
	test_saftstats			\
	test_fasta			\
	test_fasta_speed		\
	test_search2seqs		\
	test_mean_var			\
	test_pgamma			\
	test_BH

test_safterror_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_safterror_SOURCES = test_safterror.c

test_saftfasta_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_saftfasta_SOURCES = test_saftfasta.c

test_safthash_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_safthash_SOURCES = test_safthash.c

test_saftsearch_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_saftsearch_SOURCES = test_saftsearch.c

test_saftsearchenginednaarray_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_saftsearchenginednaarray_SOURCES = test_saftsearchenginednaarray.c

test_saftsearchenginednahash_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_saftsearchenginednahash_SOURCES = test_saftsearchenginednahash.c

test_saftsearchenginegeneric_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_saftsearchenginegeneric_SOURCES = test_saftsearchenginegeneric.c

test_saftsearchengines_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_saftsearchengines_SOURCES = test_saftsearchengines.c

test_saftsequence_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_saftsequence_SOURCES = test_saftsequence.c

test_saftstats_LDADD = ./libtest_harness.la $(libsaftdir)/libsaft.la
test_saftstats_SOURCES = test_saftstats.c


test_fasta_LDADD = $(libsaftdir)/libsaft.la
test_fasta_SOURCES = test_fasta.c

test_fasta_speed_LDADD = $(libsaftdir)/libsaft.la
test_fasta_speed_SOURCES = test_fasta_speed.c

test_search2seqs_LDADD = $(libsaftdir)/libsaft.la
test_search2seqs_SOURCES = test_search2seqs.c

test_mean_var_LDADD = $(libsaftdir)/libsaft.la
test_mean_var_SOURCES = test_mean_var.c

test_pgamma_LDADD = $(libsaftdir)/libsaft.la
test_pgamma_SOURCES = test_pgamma.c

test_BH_LDADD = $(libsaftdir)/libsaft.la
test_BH_SOURCES = test_BH.c

MAINTAINERCLEANFILES =			\
	Makefile.in
