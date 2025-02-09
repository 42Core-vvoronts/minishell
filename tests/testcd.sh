#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    testcd.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 10:07:47 by ipetrov           #+#    #+#              #
#    Updated: 2025/02/07 10:07:47 by ipetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

mv ../src/main.c ../src/main.c.orig &&

# Write the provided C code to the temporary file
<< EOF cat > ../src/main.c
#include "../../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_node  *node;
    t_ctx   *ctx;

    (void)argc;
    (void)argv;
    (void)envp;
    (void)ctx;
    (void)node;

    init_ctx(&ctx, envp);

	node = malloc(sizeof(t_node));
	node->ctx = ctx;
    node->ctx->stash = malloc(sizeof(char *) * 10);
    node->ctx->stash[0] = "cd";
    node->ctx->stash[1] = ft_strdup("/home/ivan/perm_not_dir/../../");
    node->ctx->stash[2] = NULL;
    run_cd(node);
}
EOF

(cd .. && make && ./minishell)

rm -f ../src/main.c
mv ../src/main.c.orig ../src/main.c

