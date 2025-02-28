/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:08:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 18:57:12 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_word_token(t_tok *tok)
{
	if (!tok)
		return (0);
	return (tok->type == ARGUMENT
		|| tok->type == CONTENT
		|| tok->type == FILENAME);
}

t_node	*create_word_node(t_tok **tok, t_ctx *ctx)
{
	t_node	*word;

	word = NULL;
	if ((*tok) && is_word_token(*tok))
	{
		word = init_node((*tok), NULL, NULL, ctx);
		step_forward(tok);
		return (word);
	}
	else
		return (NULL);
}

/**
 * @brief  Grammar rule: <expression>::= <group> <redirection>*
 * Parse group then its trailing redirections
 * 
 * @param tok The token list.
 * @return New left node
 * 
 * Example: (ls | cat) > f1
 * 
 * 		 >
 * 		/ \
 * 	f1     ()       <- group
 * 		   /
 *        |          
 * 		 / \
 * 	   ls  cat
 */
t_node	*expression_with_group(t_tok **tok, t_ctx *ctx)
{
	t_node	*stack[STACK_SIZE];
	t_node	*node;
	t_node	*result;
	int		elem;

	elem = 0;
	node = parse_group(tok, ctx);
	if (node && *tok && !is_operator((*tok)->lexeme))
		return (NULL);
	stack_redirs(tok, stack, &elem, ctx);
	result = unfold_redirs(stack, &elem, node);
	return (result);
}

/**
 * @brief  Grammar rule: <expression>::= { <word> | <redirection>}* 
 * Parse any combination of words and redirections.
 * 
 * @param tok The token list.
 * @return New left node
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
 */
t_node	*expression_no_group(t_tok **tok, t_ctx *ctx)
{
	t_node	*stack[STACK_SIZE];
	t_node	*node;
	t_node	*result;
	t_node	*word;
	int		elem;

	elem = 0;
	stack_redirs(tok, stack, &elem, ctx);
	word = create_word_node(tok, ctx);
	while (*tok && (is_word_token(*tok) || is_redir(*tok)))
	{
		collect_args(tok, word, ctx);
		stack_redirs(tok, stack, &elem, ctx);
	}
	if (is_group_open(*tok))
		return (rule_error(tok, ctx));
	node = word;
	result = unfold_redirs(stack, &elem, node);
	return (result);
}

/**
 * @brief  Grammar rule: <expression>::= { <word> | <redirection>}* 
 * 									   | <group> <redirection>*
 * If the token is a redirection operator, parse first subrule. 
 * If the token is a group, parse second subrule.
 *
 * @param tok The token list.
 * @return t_node*
 */
t_node	*parse_expression(t_tok **tok, t_ctx *ctx)
{
	if (!*tok)
		return (NULL);
	if (is_group_open(*tok))
		return (expression_with_group(tok, ctx));
	else if (!is_redir(*tok) && is_operator((*tok)->lexeme))
		return (rule_error(tok, ctx));
	else
		return (expression_no_group(tok, ctx));
}
