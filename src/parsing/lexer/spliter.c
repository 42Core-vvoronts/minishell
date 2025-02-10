/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:09:27 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 14:09:30 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **statement)
{
	while (**statement == ' ' || **statement == '\t' || **statement == '\n')
		(*statement)++;
}

void	handle_quotes(char **statement, t_tok **tokens)
{
	char	*start;
	char	*end;
	t_tok	*new;
	t_tok	*current;

	if (!*statement)
		error_exit("end of statement");
	if (is_double_quote(*statement) || is_single_quote(*statement))
	{
		start = *statement;
		end = *statement + 1;
		while (*end && !is_double_quote(end) && !is_single_quote(end))
			end++;
		if (*end == '\0')
			error_exit("Unclosed quote");
		new = init_token(start, end - start);
		add_token(new, &tokens, &current);
		*statement = end + 1;
	}

}

void	handle_words(char **statement, t_tok **tokens)
{
	char	*start;
	char	*end;
	t_tok	*new;
	t_tok	*current;

	if (!*statement)
		error_exit("end of statement");
	start = *statement;
	end = start;
	while (*end && !is_pipe_symbol(end) && !is_less(end) && !is_greater(end) && !is_and(end) && !is_double_greater(end) && !is_double_less(end))
		end++;
	new = init_token(start, end - start);
	add_token(new, &tokens, &current);
	*statement = end;
	}
	
void	handle_operators(char **statement, t_tok **tokens)
{
	char	*start;
	char	*end;
	t_tok	*new;
	t_tok	*current;
		
	if (!*statement)
		error_exit("end of statement");
	start = *statement;
	end = start + 1;
	if (is_pipe_symbol(start) || is_less(start) || is_greater(start) || is_and(start) || is_double_greater(start) || is_double_less(start))
	{
		if (is_double_greater(start) || is_double_less(start))
			end++;
		if (*end == '\0')
			error_exit("end of statement");
		new = init_token(start, end - start);
		add_token(new, &tokens, &current);
		*statement = end;
	}
}


