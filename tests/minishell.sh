#!/bin/bash
BLUE="\e[34m"
RESET="\e[0m"
echo -e "${BLUE}\n---- Makefile ----\n${RESET}"
make -C ..
exec 21>&- #ivan vscode opened fd
exec 19>&- #ivan vscode opened fd

VALGRIND_FLAGS="\
	--trace-children=yes \
	--track-fds=yes \
	--error-limit=no \
	--leak-check=full \
	--show-leak-kinds=all \
	--suppressions=valgrind.supp \
	"
	# --gen-suppressions=all \

echo -e "${BLUE}\n---- Valgrind ----\n${RESET}"
valgrind $VALGRIND_FLAGS ../minishell