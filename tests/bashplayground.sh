# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bashplayground.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 03:10:10 by ipetrov           #+#    #+#              #
#    Updated: 2025/01/29 12:23:27 by ipetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

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


INDIR=~/infiles
	INBIG="inbig"
	INEMPTY="inempty"
	INORDINARY="inordinary"
	INPERM="inperm"
	INSPACES="inspaces"
	INNONEXIST="innonexist"

OUTDIR=~/outfiles
	OUTORDINARY="outordinary"
	OUTPERM="outperm"
	OUTNONEXIST="outnonexist"

init_testfiles() {
	local content
	rm -rf "$INDIR" "$OUTDIR";
	mkdir -p $INDIR $OUTDIR $INDIR/f1
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


execute() {
    local brief="$1"
    local prompt="$2"
	local exitcode

	init_testfiles;
	unset before_in
	unset after_in
	unset before_out
	unset after_out

	declare -A before_in=()
	declare -A after_in=()

	declare -A before_out=()
	declare -A after_out=()

	for file in $INDIR/*; do
		stat_output=$(stat "$file")
		before_in["$file"]="$stat_output"
	done;

	for file in $OUTDIR/*; do
		stat_output=$(stat "$file")
		before_out["$file"]="$stat_output"
	done;

    echo -e "\n"
	echo -e "$(printf '%*s' $(tput cols) | tr ' ' -)"
	echo -e "\n"
	output=$(eval "$prompt" 2>&1)
	exitcode=$?
    echo -e "${GREY}Brief:${RESET} $brief"
    echo -e "${GREY}Prompt:${RESET} ${YELLOW}$prompt${RESET}"
	echo -e "${GREY}Code:${RESET} $exitcode"
    echo -e "${GREY}Output:${RESET}"
    echo "$output" | sed 's/^[^:]*:[ ]*line [0-9]*: //' | sed 's/^/\t/';

	for file in $INDIR/*; do
		stat_output=$(stat "$file")
		after_in["$file"]="$stat_output"
	done;

	for file in $OUTDIR/*; do
		stat_output=$(stat "$file")
		after_out["$file"]="$stat_output"
	done;

	all_keys_in=()
	for key in "${!before_in[@]}"; do
		all_keys_in+=("$key")
	done;
	for key in "${!after_in[@]}"; do
		all_keys_in+=("$key")
	done;
	all_keys_in=($(printf "%s\n" "${all_keys_in[@]}" | sort | uniq))

	echo -e "${GREY}Infiles:${RESET}"
	for key in "${all_keys_in[@]}"; do
		diff_output=$(diff <(echo "${before_in[$key]}" | sed '/Access:/d') <(echo "${after_in[$key]}" | sed '/Access:/d'))
		if [[ -n "$diff_output" ]]; then  # Check if diff output is NOT empty
				echo -e "${RED} $(echo "${after_in[$key]}" | grep "File:" | awk '{print $2}') ${RESET}"
				echo "$diff_output" | sed -n 's/^> //p' | sed '/File:/d' | sed 's/^/\t/'

		fi
	done;

	all_keys_out=()
	for key in "${!before_out[@]}"; do
		all_keys_out+=("$key")
	done
	for key in "${!after_out[@]}"; do
		all_keys_out+=("$key")
	done
	all_keys_out=($(printf "%s\n" "${all_keys_out[@]}" | sort | uniq))

	echo -e "${GREY}Outfiles:${RESET}"
	for key in "${all_keys_out[@]}"; do
		diff_output=$(diff <(echo "${before_out[$key]}" | sed '/Access:/d') <(echo "${after_out[$key]}" | sed '/Access:/d'))
		if [[ -n "$diff_output" ]]; then  # Check if diff output is NOT empty
				echo -e "${RED} $(echo "${after_out[$key]}"| grep "File:" | awk '{print $2}') ${RESET}"
				echo "$diff_output" | sed -n 's/^> //p' | sed '/File:/d' | sed 's/^/\t/'
		fi
	done;
}

# ./bashplayground.sh 'ls / > /home/ivan/outfiles/outnonexist > /home/ivan/outfiles/outperm; cat /home/ivan/outfiles/outnonexist '
# Check if arguments are passed
if [ $# -gt 0 ]; then
	for arg in "$@"; do
		execute "Provided command" "$arg"
	done
	rm -rf "$INDIR" "$OUTDIR";
	exit 1
fi

execute \
	"Ordinary command" \
	"ls | cat" \

execute \
	"No permissions to infile" \
	"< $INDIR/$INPERM cat"

execute \
	"No permissions to outfile" \
	"ls > $OUTDIR/$OUTPERM" \


execute \
	"No permissions to infile and outfile" \
	"< $INDIR/$INPERM cat > $OUTDIR/$OUTPERM" \

execute \
	"No permissions to infile while valid out redir" \
	"< $INDIR/$INPERM cat > $OUTDIR/$OUTORDINARY" \

execute \
	"No permissions to infile while valid out redir to non existing file" \
	"< $INDIR/$INPERM cat > $OUTDIR/$OUTNONEXIST" \


execute \
	"All permissions to infile and outfile" \
	"< $INDIR/$INORDINARY cat > $OUTDIR/$OUTORDINARY" \

execute \
	"All permissions to infile and outfile, not valid command" \
	"< $INDIR/$INORDINARY caaat > $OUTDIR/$OUTORDINARY" \

execute \
	"No permissions to infile and outfile, not valid command" \
	"< $INDIR/$INPERM caaat > $OUTDIR/$OUTPERM" \

execute \
	"No permissions to infile, all permissions to outfile, not valid command" \
	"< $INDIR/$INPERM caaat > $OUTDIR/$OUTORDINARY" \

execute \
	"All permissions to infile, no permissions to outfile, not valid command" \
	"< $INDIR/$INORDINARY caaat > $OUTDIR/$OUTPERM" \

execute \
	"All permissions to outfile1, no permissions to outfile2, not valid command" \
	"caaat > $OUTDIR/$OUTORDINARY > $OUTDIR/$OUTPERM" \

execute \
	"All permissions to outfile1, no permissions to outfile2, valid command" \
	"ls / > $OUTDIR/$OUTORDINARY > $OUTDIR/$OUTPERM" \

execute \
	"Nonexisting outfile1, no permissions to outfile2, valid command" \
	"ls / > $OUTDIR/$OUTNONEXIST > $OUTDIR/$OUTPERM" \


execute \
	"No permissions infile, Nonexisting outfile1, no permissions to outfile2, valid command" \
	"< $INDIR/$INPERM ls / > $OUTDIR/$OUTNONEXIST > $OUTDIR/$OUTPERM" \


execute \
	"All permissions infile, No permissions to outfile1, Nonexisting outfile1, valid command" \
	"< $INDIR/$INORDINARY cat > $OUTDIR/$OUTPERM > $OUTDIR/$OUTNONEXIST" \

execute \
	"Infile nonexist" \
	"< $INDIR/$INNONEXIST cat" \

execute \
	"Infile nonexist, Not balid command" \
	"< $INDIR/$INNONEXIST czat" \

execute \
	"Command" \
	"< $INDIR/$INORDINARY cat | cat > $OUTDIR/$OUTORDINARY | caaat" \

execute \
	"Command" \
	"< $INDIR/$INORDINARY cat | cat > $OUTDIR/$OUTORDINARY | caaat > $OUTDIR/$OUTPERM" \

execute \
	"Command" \
	"< $INDIR/$INORDINARY cat | cat > $OUTDIR/$OUTORDINARY | < $INDIR/$INPERM  caaat" \

execute \
	"Command" \
	"< $INDIR/$INORDINARY cat | cat > $OUTDIR/$OUTORDINARY | caaat < $INDIR/$INPERM " \

execute \
	"Vars" \
	'echo $HOME' \

execute \
	"Wildcard without quotes" \
	'echo $HOME/*' \

execute \
	"Wildcard with double quotes" \
	'echo "$HOME/*"' \

SINGLE='$HOME/*'
execute \
	"Wildcard and Var with single quotes" \
	"echo '$SINGLE'" \

execute \
	"Var as part of command" \
	'export VAR="ho Hello"; ec$VAR' \

execute \
	"Wildcard as part of the command" \
	"cd $INDIR/f1/; touch echo; touch zello; *" \

echo -e "\n"
rm -rf "$INDIR" "$OUTDIR";