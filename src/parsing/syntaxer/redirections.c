/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/26 09:32:50 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle the redirection operators
 * 
 * <redirection> ::= ( '>' | '<' | '>>' | '<<' ) <word>
 * 
 * @param tok The token list
 * @return new node
 */
t_node *parse_redir(t_tok **tok, t_ctx *ctx)
{
	t_tok	*operator;
	t_tok	*word_tok;
	t_node	*word;
	t_type	op;
	
	operator = *tok;
	op = operator->type;
	if (!*tok)
		return NULL;
	step_forward(tok);
    if (!*tok || !is_word_token(*tok))
    {
		if (*tok)
			error(2, ctx, (t_m){"syntax error near unexpected token", (*tok)->lexeme});
		else	
			error(2, ctx, (t_m){"syntax error near unexpected token", "newline"});
		return NULL;
    }
	word_tok = *tok;
	step_forward(tok);
	if (op == REDIR_HEREDOC)
		word = init_node(CONTENT, word_tok->lexeme, NULL, NULL, ctx);
	else
		word = init_node(FILENAME, word_tok->lexeme, NULL, NULL, ctx);
    return init_node(op, operator->lexeme, word, NULL, ctx);
}

t_node	**stack_redirs(t_tok **tok, t_node **stack, int *elem, t_ctx *ctx)
{
	t_node	*redir;
	
	while ((*tok) && is_redir(*tok))
	{
		redir = parse_redir(tok, ctx);
		if (redir)
			stack[(*elem)++] = redir;
	}
	return (stack);
}

t_node	*unfold_redirs(t_node **stack, int *elem, t_node *node)
{
	t_node	*redir;
	
	while ((*elem) > 0)
	{
		redir = stack[--(*elem)];
		redir->right = node;
		node = redir;
	}
	return node;
}

bool	is_redir(t_tok *tok)
{
	if (!tok)
		return (0);
	return (tok->type == REDIR_APPEND ||
			tok->type == REDIR_HEREDOC ||
			tok->type == REDIR_IN ||
			tok->type == REDIR_OUT);
}
