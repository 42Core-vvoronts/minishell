#!/bin/bash
MINIDIR=".."
MINIEXEC="minishell"
MAKEMINI="make -C $MINIDIR"
$MAKEMINI

green='\033[38;2;0;255;0m'     
semigreen='\033[38;2;173;255;47m'  
red='\033[38;2;255;0;0m'  
yellow='\033[38;2;255;255;0m' 
blue='\033[38;2;0;0;255m'       
lightblue='\033[38;2;117;185;255m'
darkgray='\033[38;2;169;169;169m'  
pink='\033[38;2;255;105;180m'  
reset='\033[0m'

wgreen=$(tput setaf 2)       # Green  
wsemigreen=$(tput setaf 10)   # Semi-green (if supported)  
wred=$(tput setaf 1)         # Red  
wyellow=$(tput setaf 3)      # Yellow  
wblue=$(tput setaf 4)        # Blue  
wlightblue=$(tput setaf 6)   # Light blue (cyan is closest)  
wdarkgray=$(tput setaf 8)    # Dark gray  
wpink=$(tput setaf 5)        # Pink (magenta is closest)  
wreset=$(tput sgr0)          # Reset  


# prompt="../minishell (((ls)))"
# result=$(expr '../minishell (((ls)))')
# echo $result
# ../minishell $(echo "((((ls)))")
# $MINIDIR/$MINIEXEC $test
LEXER=(
			# "$"
			# "?"
			"*"
			"&"
			">"
			"<"
			"/"
			"."
			"_"
			"-"
			"|"
			"||"
			"&&"
			"ab*de"
			""
			" "
)

NONOBV=(
    		"(<f2 ls / | cat | grep a && ls) > f1"
			"echo A && (echo B || echo C) echo F)"
			">new.file | <other.file <other.file <other.file <new.file echo SUCCESS"
			">other.file >other.file >new.file | <new.file echo FAIL_IF_NOT_ERROR"

)

LIST=(
			"&& ||" 
			"ls &&"
			"ls || && cat" 
			"ls && ls | cat" 
			"ls&&sleep 1"
)

GROUP=(
			"(" 
			")" 
			"()"
			")ls("
			"(ls"
			")ls)"
			"( ls ) )" 
			'(((ls)))'
			'((ls))'
			'(ls)'
			"((((((((((((()))))))))))))" 
			"(sleep 1 | ls) > f f2" 
			"((sleep 3 &&sleep 1) | ls)" 
			"< f ( ls | cat )" 
)

PIPELINE=(
			"|" 
			"| | |" 
			"ls |" 
			"ls | cat" 
			"ls | cat | grep a | grep b | grep c | grep d"
)

REDIRECTION=(
			"< <" 
			"> > > > > > > > > >" 
			">>>>>>>>>>>>>>>"
			">>>>>" "<<<<<" 
			"> f4 > f5 > f6" 
			"ls >f1 -la" 
			"ls > f1 -la > f2"
			"ls > f1" "> f1 f2" 
			"echo 'aboba' > f1 > f2 > f3" 
			"< f1 f2 cat"
)

WORD=(
			# "ls" 
			# "ls " 
			# "ls -la"
)

#!/bin/bash

COLUMN_WIDTH=30  # Adjust this for different column sizes

split_long_word() {
    local text="$1"
    local width="$2"
    local output=""

    while [ ${#text} -gt 0 ]; do
        output+="${text:0:$width}"$'\n'
        text="${text:$width}"
    done

    echo "$output"
}

# Function to print table rows
print_row() {
    local test="$1"
    local bash_exit="$2"
    local bash_result="$3"
    local mini_exit="$4"
    local mini_result="$5"

    # Split long words
    test=$(split_long_word "$test" 30)
    bash_result=$(split_long_word "$bash_result" "$COLUMN_WIDTH")
    mini_result=$(split_long_word "$mini_result" "$COLUMN_WIDTH")

    # Find max lines needed
    local max_lines=$(echo -e "$test\n$bash_result\n$mini_result" | wc -l)

	
	if [ "$mini_exit" -ne "$bash_exit" ]; then
		ecolor="${wred}"
	else
		ecolor="${wgreen}"
	fi

	if [ "$mini_result" == "$bash_result" ]; then
		color="${wgreen}"
		status="[OK]"
	elif [ -z "$mini_result" ] && [ -z "$bash_result" ]; then
		color="${wgreen}"
		status="[OK]"
	elif [ -n "$mini_result" ] && [ -n "$bash_result" ]; then
		color="${wsemigreen}"
		status="[OK]"
	else
		color="${wred}"
		status="[KO]"
	fi

	status_raw="$status"  
	status="${color}${status_raw}${wreset}"  
	status_stripped=$(echo -e "$status_raw" | sed "s/\x1B\[[0-9;]*m//g")  

	printf "%-30s | %-03s | %-40s | %-03s | %-40s\n" \
		"$test" "$bash_exit" "$(echo "$bash_result" | sed -n '1p')" \
		"$ecolor $mini_exit $wreset" "$(echo "$status $mini_result" | sed -n '1p')"

    # Print additional lines
    for ((i=2; i<=max_lines; i++)); do
        printf "%-30s | %-03s | %-40s | %-03s | %-40s\n" "$(echo "$test" | sed -n "${i}p")" "" "$(echo "$bash_result" | sed -n "${i}p")" "" "$(echo "$mini_result" | sed -n "${i}p")"
    done

    printf "%s\n" "---------------------------------------------------------------------------------------------------------------"
}

# testcases=("LEXER")
testcases=("LEXER" "NONOBV" "LIST" "GROUP" "PIPELINE" "REDIRECTION" "WORD")

printf "%s\n" "${wpink}---------------------------------------------------------------------------------------------------------------"
printf "%-30s | %-03s | %-40s | %-03s | %-40s\n" "Test Case" "B" "Bash Output" "M" "Mini Output"
printf "%s\n" "---------------------------------------------------------------------------------------------------------------${wreset}"
for category in "${testcases[@]}"; do
	# echo "--------------------------"
    # echo "Category: $category"
    eval "inputs=(\"\${${category}[@]}\")"
    for test in "${inputs[@]}"; do
		# result=$(expr '../minishell (((ls)))')
		# echo $result
        mini_result=$("$MINIDIR/$MINIEXEC" $test 2>&1)
		mini_exit=$?

		bash_result=$(echo $test | timeout 5 bash 2>&1)
		bash_exit=$?
		if [ "$bash_exit" == 0 ]; then
			bash_result=""
		fi


		print_row "$test" "$bash_exit" "$bash_result" "$mini_exit" "$mini_result"

    done
done
