bin_PROGRAMS = alpha
alpha_CPPFLAGS = @QT_CXXFLAGS@
alpha_LDADD = @QT_LIBS@

# moc-generated source files
alpha_MOC_SOURCES =

alpha_SOURCES = \
	$(alpha_MOC_SOURCES) \
	main.cpp

mostlyclean-local:
	rm -f $(alpha_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: %.hpp
	@QT_MOC@ -o $@ $<
