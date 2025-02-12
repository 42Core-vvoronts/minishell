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

# Define the input file
old_main="../src/main.c"
backup_old_main="../src/main.c.orig"

# Define the input file
new_main="../src/execution/expansion/wildcard.c"
backup_new_main="../src/execution/expansion/wildcard.c.orig"

# Use sed to comment out the main function
cp $old_main $backup_old_main || exit
cp $new_main $backup_new_main || exit
sed -i '/int[[:space:]]\+main[[:space:]]*(.*)/,/^}/ {
    /^\/\//! s/^/\/\/ /
}'  "$old_main"
sed -i '/int[[:space:]]\+main[[:space:]]*(.*)/,/^}/ s#^// ##' "$new_main"

echo -e "${BLUE}\n---- Makefile ----\n${RESET}"
make --no-print-directory -C .. || exit

rm -f "$old_main" "$new_main"
mv $backup_old_main $old_main
mv $backup_new_main $new_main

../minishell