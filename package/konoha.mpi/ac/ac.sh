#!/bin/sh

PKGDIR="."

echo ... start $PKGDIR/ac/${0##*/} ...

if [ ! -e $PKGDIR/ac/${0##*/} ]; then
    echo "!!! PKGDIR is incorrect"
    exit 0
fi

if [ ! -e `which mpikonoha` ]; then
    echo "!!!  MPI binary file doesn't exist"
    exit 0
fi

logfile=ac.log

if [ -e $PKGDIR/$logfile ] ;then
    rm $PKGDIR/$logfile
fi

for utest in `find $PKGDIR/ac -name "*.k" -maxdepth 1`; do
    echo $utest
    mpirun -np 1 mpikonoha -l "+$PKGDIR/$logfile" $utest
done

for utest in `find $PKGDIR/ac/pt2pt -name "*.k"`; do
    echo $utest
    mpirun -np 2 mpikonoha -l "+$PKGDIR/$logfile" $utest
done

for utest in `find $PKGDIR/ac/collective -name "*.k"`; do
    echo $utest
    mpirun -np 3 mpikonoha -l "+$PKGDIR/$logfile" $utest
done

echo ... all tests were done ...
