#!/bin/bash

case $(uname -m) in
'x86'*)
  ARCH="x64"
  ;;
'arm'*)
  ARCH="arm"
  ;;
*)
  ARCH="unkn"
  ;;
esac

reset
gcc -c -Wall -Werror -fpic extern.c stagekit.c -DSHARED_LIB
gcc -shared -o ../../libstagekit-$ARCH.so extern.o stagekit.o
rm *.o
