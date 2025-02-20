/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:28:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/20 04:04:07 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_delimeter(char **lexeme, t_ctx *ctx)
{
	char	*start;
	char	*end;
	char	*delim;

	skip_blanks(lexeme);
	start = *lexeme;
	end = start;
	while (*end && !is_blank(end))
		end++;
	delim = ft_strndup(start, end - start);
	if (!delim)
		error(-1, ctx, (t_m){strerror(errno), NULL});
	*lexeme = end;
	return delim;
}

void	tokenize_content(char *delim, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
	char	*content;
	char	*line;
	char	*tmp;
	t_tok	*new;

	if (!delim)
		error(2, ctx, (t_m){"syntax error near unexpected token `newline'"});
	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || is_eqlstr(line, delim))
		{
			free(line);
			break;
		}
		tmp = content;
		content = ft_strjoin(content, line);
		free(tmp);
		free(line);
	}
	new = init_token(content, ft_strlen(content), ctx);
	add_token(new, tokens, current);
}

void	tokenize_heredoc(char **lexeme, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start + 1;
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tokens, current);
	*lexeme = end + 1;
	tokenize_content(get_delimeter(lexeme, ctx), tokens, current, ctx);
}
