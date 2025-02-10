#!/bin/bash
MINISHELL_DIR=".."
MINISHELL_EXEC="minishell"
TESTCASE_FILE="cases.bnf"
MAKE_CMD="make -C $MINISHELL_DIR"

green='\033[38;2;0;255;0m'     
semigreen='\033[38;2;173;255;47m'  
red='\033[38;2;255;0;0m'  
yellow='\033[38;2;255;255;0m' 
blue='\033[38;2;0;0;255m'       
lightblue='\033[38;2;117;185;255m'
darkgray='\033[38;2;169;169;169m'  
pink='\033[38;2;255;105;180m'  
reset='\033[0m'                

testcases=("VALID" "LIST" "GROUP" "PIPELINE" "REDIRECTION" "WORD")

VALID=(
    		"( < f2 ls / | cat | grep a && ls ) > f1"
    		"( sleep 1 && ls ) > f1"
    		"ls > f1"
			"ls >> f1 > f2"
			"sleep 1 | ls -la"
)

LIST=(
			"&&" "||" "&& ||" 
			"&& ls" 
			"ls || && cat" 
			"ls && ls | cat" 
			"ls | cat && ls | cat && ls | cat" 
			"ls | cat || ls | cat || ls | cat || ls | cat" 
			"ls &&" "ls ||"
)

GROUP=(
			"(" 
			")" 
			"()" 
			"( ls ) )" 
			"((((((((((((()))))))))))))" 
			"( sleep 1 | ls ) > f f2" 
			"( ls | cat )" 
			"( echo abiba > f3 )" 
			"( ( sleep 3 && sleep 1 ) | ls )" 
			"< f ( ls | cat )" 
			"> f ( ls | cat )" 
			">> f ( ls | cat )" 
			">> f > f1 > f2 ( ls | cat )" 
			"echo 'aboba' > f1 > f2 > f3 ls -la"
)

PIPELINE=(
			"|" 
			"| | |" 
			"ls |" 
			"ls | cat" 
			"ls | cat | grep a | grep b | grep c | grep d"
)

REDIRECTION=(
			">" 
			">>" 
			"<" 
			"< <" 
			"> > > > > > > > > >" 
			">>>>>" "<<<<<" 
			"ls > f1 -la" 
			"> f1 echo hello" 
			"ls > f1" "> f1 f2" 
			"> f4 > f5 > f6" 
			"echo 'aboba' > f1 > f2 > f3" 
			"< f7" 
			"< f1 echo 'hello'" 
			"< f1 cat" 
			"< f1 f2 cat"
)

WORD=(
			"ls" 
			"ls /" 
			"ls -la"
)


$MAKE_CMD

"$MINISHELL_DIR/$MINISHELL_EXEC" &
minishell_pid=$!
sleep 1  # Give minishell time to initialize

# while IFS= read -r testcase || [ -n "$testcase" ]; do
for category in "${testcases[@]}"; do
	width=52  # Adjust as needed
	title="TEST $category GRAMMAR"
	padding=$(( (width - ${#title}) / 2 ))
    echo -e "${pink}------------------------------------------------------${reset}"
	printf "${pink}%"$padding"s%s%"$padding"s${reset}\n" "" "$title" ""
    # echo -e "${pink}------------------------------------------------------${reset}"

    eval "tests=(\"\${$category[@]}\")"  # This gets the tests from each category dynamically
	for test in "${tests[@]}"; do
		padding=$(( (width - ${#test}) / 2 ))
    	echo -e "${darkgray}------------------------------------------------------${reset}"
		printf "${lightblue}%"$padding"s%s%"$padding"s${reset}\n" "" "$test" ""
    	echo -e "${darkgray}------------------------------------------------------${reset}"
		
		# Run the test case in minishell:
		{ echo "$test"; echo "exit"; } | "$MINISHELL_DIR/$MINISHELL_EXEC" > minishell_out 2> minishell_err
		minishell_exit=$?
		# Run the same test case in bash
		{ echo "$test"; echo "exit"; } | bash > bash_out 2> bash_err
		bash_exit=$?

		minishell_result=$(cat minishell_err)
		bash_result=$(cat bash_err)

		# Compare exit codes.
		if [ "$minishell_exit" -ne "$bash_exit" ]; then
			echo -e "${red}[KO]${reset} expect: $bash_exit got: $minishell_exit"
		else
			echo -e "${green}[OK]${reset} expect: $bash_exit got: $minishell_exit"
		fi

		# Compare outputs
		if [ "$minishell_result" == "$bash_result" ]; then
			color="${green}"
			status="[OK]"
		elif [ -z "$minishell_result" ] && [ -z "$bash_result" ]; then
			color="${green}"
			status="[OK]"
		elif [ -n "$minishell_result" ] && [ -n "$bash_result" ]; then
			color="${semigreen}"
			status="[OK]"
		else
			color="${red}"
			status="[KO]"
		fi

		echo -e "${color}${status}${reset} minishell: '$minishell_result'"
		echo -e "\nbash '$bash_result'"
		# Clean up temporary files
		rm -f minishell_out minishell_err bash_out bash_err

	done
done


