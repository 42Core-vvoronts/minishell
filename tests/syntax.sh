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


LEXER=(
			"((((ls)"
			">>>>>>>>>>>>>>"
			"(((ls)))"
			"( ( ( ls)))"
			"( ( ( ls ) ) )"
			"(ls)"
			"|"
			"	| echo oi"
			"| |"
			# "| $"
			"| >"
			">"
			">>"
			">>>"
			"<"
			"<<"
			"echo hi <"
			"cat    <| ls"
			"echo hi | >"
			"echo hi | > >>"
			"echo hi | < |"
			"echo hi |   |"
			# "echo hi |  \"|\"  |"
)

VALID=(
    		"(<f2 ls / | cat | grep a && ls ) > f1"
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
			"ls&&sleep 1"
)

GROUP=(
			"(" 
			")" 
			"()" 
			"( ls ) )" 
			"((((((((((((()))))))))))))" 
			"(sleep 1 | ls ) > f f2" 
			"(ls|cat )" 
			"( echo abiba >f3 )" 
			"( ( sleep 3 &&sleep 1 ) | ls )" 
			"< f ( ls | cat )" 
			"> f ( ls |cat )" 
			">> f ( ls| cat )" 
			">> f> f1> f2 ( ls | cat )" 
			"echo 'aboba' >f1 > f2 > f3 ls -la"
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
			"ls > f1 -la > f2"
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
			"ls " 
			"ls -la"
			"a aa aaa"
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

testcases=("LEXER" "VALID" "LIST" "GROUP" "PIPELINE" "REDIRECTION" "WORD")

printf "%s\n" "${wpink}---------------------------------------------------------------------------------------------------------------"
printf "%-30s | %-03s | %-40s | %-03s | %-40s\n" "Test Case" "B" "Bash Output" "M" "Mini Output"
printf "%s\n" "---------------------------------------------------------------------------------------------------------------${wreset}"
for category in "${testcases[@]}"; do
	# echo "--------------------------"
    # echo "Category: $category"
    eval "inputs=(\"\${${category}[@]}\")"
    for test in "${inputs[@]}"; do

        mini_result=$("$MINIDIR/$MINIEXEC" "$test" 2>&1)
		mini_exit=$?

		bash_result=$(echo $test | bash 2>&1)
		bash_exit=$?
		if [ "$bash_exit" == 0 ]; then
			bash_result=""
		fi


		print_row "$test" "$bash_exit" "$bash_result" "$mini_exit" "$mini_result"

    done
done



# for category in "${testcases[@]}"; do
#     eval "inputs=(\"\${${category}[@]}\")"  # Indirect expansion to get the correct array
# 	width=52  # Adjust as needed
# 	title="$category"
# 	padding=$(( (width - ${#title}) / 2 ))
# 	echo -e "${darkgray}------------------------------------------------------${reset}"
# 	printf "${pink}%"$padding"s%s%"$padding"s${reset}\n" "" "$title" ""
# 	echo -e "${darkgray}------------------------------------------------------${reset}"

#     for test in "${inputs[@]}"; do
# 		padding=$(( (width - ${#test}) / 2 ))
#     	echo -e "${darkgray}------------------------------------------------------${reset}"
# 		printf "${lightblue}%"$padding"s%s%"$padding"s${reset}\n" "" "$test" ""
#     	echo -e "${darkgray}------------------------------------------------------${reset}"


#         # Run minishell with the input string as an argument and capture both stdout and stderr
#         mini_result=$("$MINIDIR/$MINIEXEC" "$test" 2>&1)
# 		mini_exit=$?

#         # Check the syntax of the test using bash without executing it
#         bash_result=$(bash -n -c "$test" 2>&1)
# 		bash_exit=$?


# 		if [ "$mini_exit" -ne "$bash_exit" ]; then
# 			echo -e "${red}[KO]${reset} expect: $bash_exit got: $mini_exit"
# 		else
# 			echo -e "${green}[OK]${reset} expect: $bash_exit got: $mini_exit"
# 		fi

# 		if [ "$mini_result" == "$bash_result" ]; then
# 			color="${green}"
# 			status="[OK]"
# 		elif [ -z "$mini_result" ] && [ -z "$bash_result" ]; then
# 			color="${green}"
# 			status="[OK]"
# 		elif [ -n "$mini_result" ] && [ -n "$bash_result" ]; then
# 			color="${semigreen}"
# 			status="[OK]"
# 		else
# 			color="${red}"
# 			status="[KO]"
# 		fi

# 		echo -e "${color}${status}${reset} minishell: '$mini_result'"
# 		echo -e "\nbash '$bash_result'"
#     done
# done
# echo -e "${darkgray}------------------------------------------------------${reset}"


 