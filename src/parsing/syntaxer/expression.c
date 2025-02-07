/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:08:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/07 10:41:42 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the token is a word
 *
 * @param tok Current token
 * @return true if the token is a word
 */
int is_word(t_tok *tok)
{
    return (tok->type == WORD_ZERO_QUOTES ||
            tok->type == WORD_SINGLE_QUOTES ||
            tok->type == WORD_DOUBLE_QUOTES);
}

/**
 * @brief  Grammar rule: <expression>::= { <word> | <redirection>}* 
 * 									   | <group> <redirection>*
 * 
 * If the token is a redirection operator, parse first subrule. 
 * If the token is a group, parse second subrule.
 * 
 * Example: echo "arg" > f1 > f2
 * 
 *	       	 >       <- redir #1
 *		    / \
 *		   f1  >      <- redir #2
 *			   / \
 *		     f2   echo
 *					|
 *				  "arg"
 *
 * Example: (ls | cat) > f1
 * 
 * 		 >       <- redir
 * 		/ \
 * 	f1     ()       <- group
 * 		   /
 *        |        <- pipe
 * 		 / \
 * 	   ls  cat
 *
 * 
 * @param tok The token list.
 * @return New left node
 * 
 */
t_node *parse_expression(t_tok **tok)
{
    if (!*tok)
        return NULL;

    /* Case 1: Group – parse group then its trailing redirections */
	if (is_group_open(*tok))
    // if ((*tok)->lexeme && ft_strcmp((*tok)->lexeme, "(") == 0)
    {
        t_node *node = parse_group(tok);
        t_node *redir_stack[256];
        int count = 0;
        while (*tok && get_precedence((*tok)->type) == 2)
            redir_stack[count++] = parse_redir(tok);
        while (count > 0)
        {
            t_node *redir = redir_stack[--count];
            redir->right = node;
            node = redir;
        }
        return node;
    }

    /* Case 2: Non-group – allow redirections before and after the command */
    t_node *redir_stack[256];
    int count = 0;

    /* Parse any leading redirections (e.g., "< f2") */
    while (*tok && get_precedence((*tok)->type) == 2)
        redir_stack[count++] = parse_redir(tok);

    /* Now expect a command word */
    if (!*tok || !is_word(*tok))
    {
        fprintf(stderr, "Error: expected command, got '%s'\n",
                (*tok)->lexeme ? (*tok)->lexeme : "NULL");
        return NULL;
    }
    t_node *cmd = new_node((*tok)->type, (*tok)->lexeme, NULL, NULL);
    *tok = (*tok)->next;

    /* Collect additional command arguments */
    t_node *args = NULL, *args_tail = NULL;
    while (*tok && is_word(*tok))
    {
        t_node *arg = new_node((*tok)->type, (*tok)->lexeme, NULL, NULL);
        *tok = (*tok)->next;
        if (!args)
        {
            args = arg;
            args_tail = arg;
        }
        else
        {
            args_tail->right = arg;
            args_tail = arg;
        }
    }
    cmd->left = args;

    /* Parse any redirections following the command */
    while (*tok && get_precedence((*tok)->type) == 2)
        redir_stack[count++] = parse_redir(tok);

    /* Fold all redirections from right to left.
       This makes the first redirection the top node with its right child
       being the next redirection (or the command if none remain). */
    t_node *node = cmd;
    while (count > 0)
    {
        t_node *redir = redir_stack[--count];
        redir->right = node;
        node = redir;
    }
    return node;
}

