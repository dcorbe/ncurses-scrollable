#!/bin/sh


if [ "$1" = "clean" ]
then 
    if [ -f "Makefile" ]
    then
	make distclean
    fi

    echo "rm -rf *~ *.scan aclocal.m4 *.cache *.log config.h *.in configure *.status depcomp compile install-sh missing"
          rm -rf *~ *.scan aclocal.m4 *.cache *.log config.h *.in configure *.status depcomp compile install-sh missing
else
    aclocal
    autoconf
    autoheader
    automake --add-missing -c
    automake
fi
