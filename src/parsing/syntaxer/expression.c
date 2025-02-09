/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:08:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/09 16:52:18 by vvoronts         ###   ########.fr       */
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
	if (!tok)
		return (0);
    return (tok->type == WORD ||
            tok->type == CONTENT);
}

t_node	**stack_redirs(t_tok **tok, t_node **stack, int *elem)
{
	t_node	*redir;
	
	while ((*tok) && is_redir(*tok))
	{
		redir = parse_redir(tok);
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

void collect_args(t_tok **tok, t_node *word)
{
    t_node	*arg;
    t_node	*head;
	t_node	*tail;

	tail = NULL;
	head = NULL;
	if (!word)
		return ;
    while (*tok && is_word(*tok))
    {
        arg = init_node((*tok)->type, (*tok)->lexeme, NULL, NULL);
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

t_node	*create_word_node(t_tok **tok)
{
	t_node	*word;

	word = NULL;
	if ((*tok) && is_word(*tok))
	{
		word = init_node((*tok)->type, (*tok)->lexeme, NULL, NULL);
		step_forward(tok);
		return word;
	}
	else
	{
		if (*tok && (*tok)->lexeme)
			fprintf(stderr, "Error: expected command\n");
		else
			fprintf(stderr, "Error: expected command\n");
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
 * 		 >       <- redir
 * 		/ \
 * 	f1     ()       <- group
 * 		   /
 *        |        <- pipe
 * 		 / \
 * 	   ls  cat
 */
t_node *expression_with_group(t_tok **tok)
{
	t_node	*stack[STACK_SIZE];
	t_node	*node;
	t_node	*result;
	int		elem;

	elem = 0;
	node = parse_group(tok);
	stack_redirs(tok, stack, &elem);
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
t_node *expression_no_group(t_tok **tok)
{
	t_node	*stack[STACK_SIZE];
	t_node	*node;
	t_node	*result;
	t_node	*word;
	int		elem;
	
	elem = 0;
	stack_redirs(tok, stack, &elem);
	word = create_word_node(tok);
	collect_args(tok, word);
	stack_redirs(tok, stack, &elem);
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
t_node	*parse_expression(t_tok **tok)
{
	if (!*tok)
		return NULL;
	if (is_group_open(*tok))
		return (expression_with_group(tok));
	else
		return (expression_no_group(tok));
}
