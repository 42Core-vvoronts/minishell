/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:08:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/06 17:01:54 by vvoronts         ###   ########.fr       */
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
 * @brief 
 * 
 * <exec> ::= <group>
 *          | <word> { <word> }* { <redirection> }*
 * 
 * If the token is a left parenthesis (represented by lexeme "("), then
 * we parse a grouped command. Otherwise we expect one or more WORD tokens.
 * 
 * @param tok The token list.
 * @return New left node
 * 
 */
t_node *parse_expression(t_tok **tok)
{
    if (!*tok)
        return NULL;

    t_node *node = NULL;

    /* Check for group: if the lexeme is "(" then parse a group */
    if ((*tok)->lexeme && strcmp((*tok)->lexeme, "(") == 0) //is_eqlstr()
    {
        node = parse_group(tok);
    }
    else
    {
        if (!is_word(*tok))
        {
            fprintf(stderr, "Error: expected command word, got '%s'\n",
                    (*tok)->lexeme ? (*tok)->lexeme : "NULL");
            return NULL;
        }

        /* Create an execution node with the first command word */
        node = new_node((*tok)->type, (*tok)->lexeme, NULL, NULL);
        *tok = (*tok)->next;

        /* Collect additional WORD tokens as arguments (attached to right) */
        while (*tok && is_word(*tok))
        {
            t_node *arg = new_node((*tok)->type, (*tok)->lexeme, NULL, NULL);
            if (!node->left)
                node->left = arg;
            else
            {
                t_node *temp = node->left;
                while (temp->right)
                    temp = temp->right;
                temp->right = arg;
            }
            *tok = (*tok)->next;
        }
    }

    /* Process any redirections following the command or group */
    while (*tok && ((*tok)->type == REDIR_IN || (*tok)->type == REDIR_OUT ||
                    (*tok)->type == REDIR_APPEND || (*tok)->type == REDIR_HEREDOC))
    {
        t_node *redir = parse_redir(tok);
        if (!node->right)
            node->right = redir;
        else
        {
            t_node *temp = node->right;
            while (temp->right)
                temp = temp->right;
            temp->right = redir;
        }
    }
    return node;
}