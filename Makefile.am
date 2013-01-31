SUBDIRS = src/genetic/
EXTRA_DIST = AUTHORS TODO README ChangeLog check doc src/*/*.hh src/*.hh

bin_PROGRAMS = genetic-smb-nes
genetic_smb_nes_LDADD = \
    src/genetic/libgenetic.a
genetic_smb_nes_CXXFLAGS = \
    -Isrc/genetic/ \
    $(AM_CXXFLAGS)
genetic_smb_nes_SOURCES = src/init.cc

check:
	./genetic-smb-nes && fceux smb.zip --loadlua smb.lua

last-check:
	fceux smb.zip --loadlua smb.lua

doc:
	doxygen doc/Doxyfile

changelog : ChangeLog

ChangeLog :
	git log --graph --color > ChangeLog

clean-local:
	rm -f smb.lua

allclean: distclean
	rm -f genetic-smb-nes
	rm -f configure
	rm -f src/*/Makefile.in
	rm -f Makefile.in
	rm -f *.dot
	rm -f *.m4
	rm -rf *.cache
	rm -rf build-aux

.PHONY : doc check allclean all
