#!/bin/bash
cmd=$(basename $0)

case "$cmd" in
	ppc)
		pp_c "$@" | lpr
		;;
	ppc++)
		pp_c++ "$@" | lpr
		;;
	ppsh)
		pp_sh "$@" | lpr
		;;
	ppjava)
		pp_java "$@" | lpr
		;;
	*)
		echo "*** Unknown formatter: $cmd"
		exit 1
		;;
esac

