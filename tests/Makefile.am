check_PROGRAMS = runtest
runtest_CPPFLAGS = @CXX_11_CXXFLAGS@ @QT_CXXFLAGS@ @LUA_CXX_INCLUDE@ @FREETYPE2_CFLAGS@ @LUA_INCLUDE@ @FTGL_CFLAGS@ @GL_CFLAGS@ -I$(top_srcdir)/src @ALPHA_GLOBAL_CXXFLAGS@
runtest_LDADD = @QT_LIBS@ @LUA_CXX_LIBS@ @FREETYPE2_LIBS@ @FTGL_LIBS@ @LUA_LIB@ @GL_LIBS@ ../src/libalpha.la

TESTS = $(check_PROGRAMS)

test_suites = \
	VoxmapTests \
	RotationTests \
	RenderLayerTests \
	Vector3Tests

runtest_SOURCES = tests.cpp $(addsuffix .hpp, $(test_suites))

runtest_MOC_SOURCES = \
	moc_VoxmapTests.cpp \
	moc_RotationTests.cpp \
	moc_RenderLayerTests.cpp \
	moc_Vector3Tests.cpp

nodist_runtest_SOURCES = $(runtest_MOC_SOURCES)

mostlyclean-local:
	rm -f $(runtest_MOC_SOURCES)
.PHONY: mostlyclean-local

tests.cpp: make_wrapper.sh $(addsuffix .hpp, $(test_suites))
	rm -f $@
	$(top_srcdir)/tests/make_wrapper.sh $^ >$@-wip
	mv $@-wip $@
	chmod -w $@

moc_%.cpp: %.hpp
	@QT_MOC@ -o $@ $<
