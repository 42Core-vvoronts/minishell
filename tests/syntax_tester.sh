#!/bin/bash
MINISHELL_DIR=".."
MINISHELL_EXEC="minishell"
TESTCASE_FILE="cases.bnf"
MAKE_CMD="make -C $MINISHELL_DIR"

green='\033[38;2;0;255;0m'      # Green
semigreen='\033[38;2;173;255;47m'  # Yellow-Green
red='\033[38;2;255;0;0m'         # Red
yellow='\033[38;2;255;255;0m'    # Yellow
blue='\033[38;2;0;0;255m'        # Blue
darkgray='\033[38;2;169;169;169m'  # Dark Gray
reset='\033[0m'                 # Reset

$MAKE_CMD

"$MINISHELL_DIR/$MINISHELL_EXEC" &
minishell_pid=$!
sleep 1  # Give minishell time to initialize

while IFS= read -r testcase || [ -n "$testcase" ]; do
    # Skip blank lines and comment lines
    [[ "$testcase" =~ ^[[:space:]]*$ ]] && continue
    [[ "$testcase" =~ ^[[:space:]]*# ]] && continue


    # Run the test case in minishell:
    { echo "$testcase"; echo "exit"; } | "$MINISHELL_DIR/$MINISHELL_EXEC" > minishell_out 2> minishell_err
	minishell_exit=$?
    # Run the same test case in bash
    { echo "$testcase"; echo "exit"; } | bash > bash_out 2> bash_err
    bash_exit=$?

	minishell_result=$(cat minishell_err)
    bash_result=$(cat bash_err)

    # Compare outputs and exit codes.
	if [ -z "$minishell_result" ] && [ -z "$bash_result" ]; then
		echo -e "${green}[OK]${reset} testcase: '$testcase'"
	elif [ -n "$minishell_result" ] && [ -n "$bash_result" ]; then
		echo -e "${semigreen}[OK]${reset} testcase: '$testcase'"
    elif [ "$minishell_result" == "$bash_result" ]; then
       	echo -e "${green}[OK]${reset} testcase: '$testcase'"
    else
        echo -e "${red}[KO]${reset} testcase: '$testcase'"

    fi
	if [ "$minishell_exit" -ne "$bash_exit" ]; then
		echo -e "${darkgray}[KO]${reset} exitcode: expect: $bash_exit got: $minishell_exit \n"
	else
		echo -e "${green}[OK]${reset} exitcode: expect: $bash_exit got: $minishell_exit \n"
	fi
	echo -e "${blue}minishell${reset}:'$minishell_result'"
	echo -e "${blue}bash${reset}:'$bash_result'"
    echo -e "${darkgray}------------------------------------------------------${reset}"
    # Clean up temporary files
    rm -f minishell_out minishell_err bash_out bash_err

done < "$TESTCASE_FILE"