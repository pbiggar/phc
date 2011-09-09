#!/bin/bash

##
## Script to generate phc-VERSION.tar.gz, phc-VERSION-html.tar.gz, 
## phc-VERSION.pdf, and phc website
##

## Define an error function

function ERROR 
{
	printf "\033[31mError: $1\033[0m\n"
	exit
}

function full_test
{
	pushd .
	tar xfj $SRC_BZ2
	cd $SRC_DIR
	./configure --prefix $TST_DIR $1
	make
	make installtest
	popd
	rm -rf $SRC_DIR
	rm -rf $TST_DIR
}


set -x

# Get the revision number from AC_INIT

# Get the second column, which is in the form "[version],". Strip the [], from around it.
VERSION=$(grep AC_INIT configure.ac | awk '{print $2}' | sed -e 's/^.\(.*\)..$/\1/g')


## Names of the generated files and directories

SRC_DIR=phc-$VERSION
DOC_DIR=$SRC_DIR/doc/manual/
LATEX_DIR=$DOC_DIR/.build/latex/
TST_DIR=$(readlink -f phc-$VERSION-test)

SRC_TGZ=phc-$VERSION.tar.gz
SRC_BZ2=phc-$VERSION.tar.bz2
DOC_TGZ=phc-$VERSION-html.tar.gz

PDF=phc-$VERSION.pdf

## Check for the existance of directories and files

for dir in $SRC_DIR
do
	if test -d $dir
	then
		ERROR "directory \"$dir\" exists"
	fi
done

for file in $SRC_TGZ $SRC_BZ2 $DOC_TGZ $PDF
do
	if test -f $file
	then
		ERROR "file \"$file\" exists"
	fi
done

## Start generating the release 

## Export an unversioned copy of the repository

svn update
svn export . $SRC_DIR 

## Make sure the timestamps of the files in generated/ are newer than the 
## timestamps in generated_src/

touch $SRC_DIR/src/generated/*

## Dont package up all the benchmarks

rm -Rf $SRC_DIR/test/subjects/benchmarks
## Dont break the tests
sed 's/^benchmarks/#benchmarks/' $SRC_DIR/test/subjects/labels -i

## Generate source package

tar cfz $SRC_TGZ $SRC_DIR
tar cfj $SRC_BZ2 $SRC_DIR

## Generate documentation (HTML)

make -C $DOC_DIR html
tar cfz $DOC_TGZ $DOC_DIR 

## Generate documentation (PDF)

make -C $DOC_DIR latex
make -C $LATEX_DIR all-pdf
mv $LATEX_DIR/manual.pdf $PDF 

## Remove temporary files

rm -rf $SRC_DIR

## Running tests

full_test
full_test --without-php
full_test --without-xerces

## Finish 

set +x
