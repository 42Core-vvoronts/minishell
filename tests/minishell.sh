#!/bin/env bash

# Define color variables
RED="\e[31m"
GREEN="\e[32m"
BLUE="\e[34m"
BOLD="\e[1m"
YELLOW="\033[0;33m"
GREY="\033[38;5;244m"
PURPLE="\033[0;35m"
END="\033[0m"
RESET="\e[0m"

INDIR=./infiles
	INBIG="inbig"
	INEMPTY="inempty"
	INORDINARY="inordinary"
	INPERM="inperm"
	INSPACES="inspaces"
	INNONEXIST="innonexist"

OUTDIR=./outfiles
	OUTORDINARY="outordinary"
	OUTPERM="outperm"
	OUTNONEXIST="outnonexist"

init_testfiles() {
	local content
	rm -rf "$INDIR" "$OUTDIR";
	mkdir -p $INDIR $OUTDIR $INDIR
	head -c 750K /dev/urandom | tr -dc 'A-Za-z0-9 \n' > $INDIR/$INBIG

	content="line1\nline2\nline3"
	echo -e $content > $INDIR/$INORDINARY

	touch  $INDIR/$INEMPTY

	content="inperm content"
	echo -e $content > $INDIR/$INPERM
	chmod 000 $INDIR/$INPERM

	content="😈 😈 😈\nThis will break your minishell\n😈 😈 😈"
	echo -e $content > $INDIR/$INSPACES

	content="initially line1\ninitially line2\ninitially line3"
	echo -e $content > $OUTDIR/$OUTORDINARY

	content="outperm content"
	echo -e $content > $OUTDIR/$OUTPERM
	chmod 000 $OUTDIR/$OUTPERM

}

echo -e "${BLUE}\n---- Makefile ----\n${RESET}"
make --no-print-directory -C .. || exit
exec 21>&- #ivan vscode close opened fd
exec 19>&- #ivan vscode close opened fd
init_testfiles;
if [ "$1" == "-v" ]; then
	echo -e "${BLUE}\n---- Valgrind ----\n${RESET}"
	echo -e "Examine output of valgrind at ./valgrind.log"
	VALGRIND_FLAGS="\
		--trace-children=yes \
		--track-fds=yes \
		--leak-check=full \
		--show-leak-kinds=all \
		--error-limit=no \
		--log-file=valgrind.log \
		--suppressions=valgrind.supp \
		"
		# --gen-suppressions=all \
	echo -e "${BLUE}\n---- Minishell ----\n${RESET}"
	sudo valgrind $VALGRIND_FLAGS ../minishell
else
	echo -e "${BLUE}\n---- Minishell ----\n${RESET}"
	../minishell
fi

# dry run for syntax
if [ "$1" == "-n" ]; then
	echo -e "${BLUE}\n---- Syntax ----\n${RESET}"
	bash -n
fi
rm -rf "$INDIR" "$OUTDIR";