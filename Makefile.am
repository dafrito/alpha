ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src include demos tests

pkgdata_DATA = \
	alpha.m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = alpha.pc

export RPMDIR ?= $$HOME/rpmbuild

RPMFLAGS ?= --ba
rpm: rpm.spec dist-gzip | $(RPMDIR)
	cp -u $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz $(RPMDIR)/SOURCES
	cp -u rpm.spec $(RPMDIR)/SPECS/$(PACKAGE_NAME).spec
	rpmbuild $(RPMFLAGS) $(RPMDIR)/SPECS/$(PACKAGE_NAME).spec
	for package in `rpm -q --specfile ./rpm.spec`; do \
		arch=`echo $$package | grep -E -o '[^.]+$$'`; \
		filename="$(RPMDIR)/RPMS/$$arch/$$package.rpm"; \
		[ -e `basename $$filename` ] || ln -s $$filename; \
done
.PHONY: rpm

$(RPMDIR):
	mkdir -p $@
	cd $@ && mkdir -p SOURCES SPECS BUILD RPMS SRPMS
