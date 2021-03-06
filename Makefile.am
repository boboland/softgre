# Author: Jorge Pereira <jpereiran@gmail.com>
# Created: Mon Sep 22 23:14:38 EDT 2014
# Last Change: Seg 27 Out 2014 20:48:20 BRST
####

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = bin share

GIT_BRANCH := $(shell git branch --no-color | grep "^*" | sed -e 's/^\* //')
GIT_HASH   := $(shell git log --pretty=format:"%h" | head -1)
GIT_TAG    := $(shell git name-rev --tags --name-only $(shell git rev-parse HEAD) | cut -f1 -d^)
CUR_TIME    = $(shell date "+%Y%m%d-%H%M%S")

if DEVEL
DEBIAN_PKG_VERSION = $(PACKAGE_VERSION)-$(GIT_HASH)-$(CUR_TIME)
else
DEBIAN_PKG_VERSION = $(PACKAGE_VERSION)-$(GIT_TAG)
endif

if MAINTAINER_MODE
dist-hook: dist-changelog
else
dist-hook: dashboard
endif

# always update the ChangeLog
all: version_header dist-changelog
	
version_header:
	echo "/*Generated automatic ($(shell date))*/" > version.h
	echo "#define CURRENT_COMMIT \"$(GIT_HASH)\"" >> version.h
	echo "#define CURRENT_BRANCH \"$(GIT_BRANCH)\"" >> version.h
	echo "#define CURRENT_TAG    \"$(GIT_TAG)\"" >> version.h

build-package: dist-changelog debian-package

dist-changelog:
	if git --git-dir=$(top_srcdir)/.git --work-tree=$(top_srcdir) \
	log --no-merges --date=short --pretty='tformat:%cd  %an  <%ae>%n%n%s%n%n%b' $(GIT_BRANCH) | \
	$(SED)	-e '/^[12]...-[01].-[0123].  [^<>]*  <[^<>]*>$$/,/^$$/ b' \
	  		-e '/[^	 ]/,/^[	 ]*$$/ !d' \
		    -e 's/^[	 ]*/	/' \
		    -e 's/^[	 ]*$$//' >.ChangeLog.tmp; \
    then mv -f .ChangeLog.tmp "ChangeLog"; \
    else rm -f .ChangeLog.tmp; exit 1; fi

debian-package:
	rm -f ../softgred*.{changes,build,deb,install} debian/changelog
	./autogen.sh
	dch -v "$(DEBIAN_PKG_VERSION)" --package softgred --create debian/changelog
	debuild -us -uc -B

DISTCLEANFILES = \
	intltool-extract \
	intltool-merge \
	intltool-update 

.PHONY: dist-changelog 

