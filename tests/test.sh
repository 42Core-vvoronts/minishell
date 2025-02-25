#!/bin/env bash

# VALGRIND="valgrind --trace-children=yes --track-fds=yes --leak-check=full -show-leak-kinds=all --error-limit=no"

# RESULT=$(echo -e "ls" | $VALGRIND --log-file=mini_valgrind.log ../minishell 2> /dev/null)

# echo $RESULT

valgrind ../minishell <<< $(echo -e "ls")
