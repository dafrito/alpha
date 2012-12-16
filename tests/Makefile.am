check_PROGRAMS = runtest
runtest_CPPFLAGS = @CXX_11_CXXFLAGS@ @QT_CXXFLAGS@ @LUA_CXX_INCLUDE@ @FREETYPE2_CFLAGS@ @LUA_INCLUDE@ @FTGL_CFLAGS@ @GL_CFLAGS@ -I$(top_srcdir)/src @ALPHA_GLOBAL_CXXFLAGS@
runtest_LDADD = @QT_LIBS@ @LUA_CXX_LIBS@ @FREETYPE2_LIBS@ @FTGL_LIBS@ @LUA_LIB@ @GL_LIBS@ ../src/libalpha.la

TESTS = $(check_PROGRAMS)

test_suites =         \
	RotationTests \
	Vector3Tests

runtest_SOURCES =         \
	tests.cpp             \
	RotationTests.h \
	Vector3Tests.h

runtest_MOC_SOURCES = \
	moc_RotationTests.cpp \
	moc_Vector3Tests.cpp

nodist_runtest_SOURCES =      \
	$(runtest_MOC_SOURCES)

mostlyclean-local:
	rm -f $(runtest_MOC_SOURCES)
.PHONY: mostlyclean-local

tests.cpp: make_wrapper.sh $(addsuffix .h, $(test_suites))
	rm -f $@
	$(top_srcdir)/tests/make_wrapper.sh $^ >$@-wip
	mv $@-wip $@
	chmod -w $@

moc_%.cpp: %.h
	@QT_MOC@ -o $@ $<
