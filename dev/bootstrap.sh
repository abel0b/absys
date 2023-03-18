#!/bin/bash
TMPDIR=${TMPDIR:-$(mktemp -d)}
PLATFORM=linux
git clone https://github.com/premake/premake-core $TMPDIR/premake
pushd $TMPDIR/premake
make -f Bootstrap.mak $PLATFORM
popd
echo $TMPDIR
