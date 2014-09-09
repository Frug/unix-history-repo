#!/bin/sh
# $FreeBSD: head/tools/regression/pjdfstest/tests/mkfifo/07.t 211352 2010-08-15 21:24:17Z pjd $

desc="mkfifo returns ELOOP if too many symbolic links were encountered in translating the pathname"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..6"

n0=`namegen`
n1=`namegen`

expect 0 symlink ${n0} ${n1}
expect 0 symlink ${n1} ${n0}
expect ELOOP mkfifo ${n0}/test 0644
expect ELOOP mkfifo ${n1}/test 0644
expect 0 unlink ${n0}
expect 0 unlink ${n1}
