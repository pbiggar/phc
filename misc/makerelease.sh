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

## Check command line usage

if [ "$1" = "" ]
then
	ERROR "usage: $0 version_number" 
fi

## Names of the generated files and directories

SRC_DIR=phc-$1
DOC_DIR=$SRC_DIR/doc/manual/
TST_DIR=$(readlink -f phc-$1-test)

SRC_TGZ=phc-$1.tar.gz
SRC_BZ2=phc-$1.tar.bz2
DOC_TGZ=phc-$1-html.tar.gz

PDF=phc-$1.pdf

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

set -x

## Export an unversioned copy of the repository

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

make -C $DOC_DIR
tar cfz $DOC_TGZ $DOC_DIR 

## Generate documentation (PDF)

make -C $DOC_DIR manual.pdf
mv $DOC_DIR/manual.pdf $PDF 

## Remove temporary files

rm -rf $SRC_DIR

## Running tests

pushd .
tar xfj $SRC_BZ2
cd $SRC_DIR
./configure --prefix $TST_DIR
make
make installtest
popd

## Finish 

set +x
