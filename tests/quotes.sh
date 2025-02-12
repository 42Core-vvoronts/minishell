#!/bin/bash



test="(((ls)))"



result=$(eval "../minishell '(ls)'")

echo $result
