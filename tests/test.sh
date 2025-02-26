#!/bin/env bash

# VALGRIND="valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --error-limit=no --suppressions=test.supp"
VALGRIND_LOG=valgrind.log
VALGRIND_TMP=tmp.log
VALGRIND="valgrind -q --track-fds=yes --trace-children=yes --leak-check=full --error-limit=no --suppressions=test.supp --log-file=$VALGRIND_TMP"
rm $VALGRIND_LOG

# --show-leak-kinds=all
# RESULT=$(echo -e "ls" | $VALGRIND --log-file=mini_valgrind.log ../minishell 2> /dev/null)

# echo $RESULT

$VALGRIND ./a.out <<< $(echo -e "ls")

sed '/.*tmp\.log\|.*<inherited from parent>\|.*FILE DESCRIPTORS.*\|^==[0-9]\+==[[:space:]]*$/d' "$VALGRIND_TMP" > $VALGRIND_LOG

rm $VALGRIND_TMP
