/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 12:27:55 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(t_tok *tok)
{
	if (!tok)
		return (0);
	return (tok->type == REDIR_APPEND
		|| tok->type == REDIR_HEREDOC
		|| tok->type == REDIR_IN
		|| tok->type == REDIR_OUT);
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
	return (node);
}

/**
 * @brief Handle the redirection operators
 * 
 * <redirection> ::= ( '>' | '<' | '>>' | '<<' ) <word>
 * 
 * @param tok The token list
 * @return new node
 */
t_node	*parse_redir(t_tok **tok, t_ctx *ctx)
{
	t_tok	*operator;
	t_tok	*word_tok;
	t_node	*word;

	operator = *tok;
	if (!*tok)
		return (NULL);
	step_forward(tok);
	if (!*tok || !is_word_token(*tok))
		return (rule_error(tok, ctx, NULL));
	word_tok = *tok;
	step_forward(tok);
	if (operator->type == REDIR_HEREDOC)
		word_tok->type = CONTENT;
	else
		word_tok->type = FILENAME;
	word = init_node(word_tok, NULL, NULL, ctx);
	return (init_node(operator, word, NULL, ctx));
}
