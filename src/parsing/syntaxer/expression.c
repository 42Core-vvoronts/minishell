/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:08:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 11:41:33 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the token is a word
 *
 * @param tok Current token
 * @return true if the token is a word
 */
bool	is_word_token(t_tok *tok)
{
	if (!tok)
		return (0);
    return (tok->type == ARGUMENT ||
            tok->type == CONTENT ||
			tok->type == FILENAME);
}

void collect_args(t_tok **tok, t_node *word, t_ctx *ctx)
{
	t_node	*head;
	t_node	*tail;
    t_node	*arg;
	t_node	*tmp;

	tail = NULL;
	head = NULL;
	if (!word || !*tok)
		return ;
	tmp = word;
	if (tmp && tmp->left)
		head = tmp->left;
	tail = head;
	while (tmp && tmp->left)
	{
		tail = tmp->left;
		tmp = tmp->left;
	}
    while (*tok && is_word_token(*tok))
    {
        arg = init_node((*tok)->type, (*tok)->lexeme, NULL, NULL, ctx);
		step_forward(tok);
        if (!head)
        {
            head = arg;
            tail = arg;
        }
        else
        {
            tail->left = arg;
            tail = arg;
        }
    }
    word->left = head;
}

t_node	*create_word_node(t_tok **tok, t_ctx *ctx)
{
	t_node	*word;

	word = NULL;
	if ((*tok) && is_word_token(*tok))
	{
		word = init_node((*tok)->type, (*tok)->lexeme, NULL, NULL, ctx);
		step_forward(tok);
		return word;
	}
	else
	{
		return NULL;
	}
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
t_node *expression_with_group(t_tok **tok, t_ctx *ctx)
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
t_node *expression_no_group(t_tok **tok, t_ctx *ctx)
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
    node = word;
	result = unfold_redirs(stack, &elem, node);
    return result;
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
		return NULL;
	if (is_group_open(*tok))
		return (expression_with_group(tok, ctx));
	else if (!is_redir(*tok) && is_operator((*tok)->lexeme))
		return ((t_node *)parserror("syntax", (*tok)->lexeme, 2, ctx));
	else
		return (expression_no_group(tok, ctx));
}
