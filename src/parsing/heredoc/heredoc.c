/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:28:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/23 11:24:34 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_delimeter(char **lexeme, t_ctx *ctx)
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
		error(-1, ctx, (t_m){strerror(errno)});
	*lexeme = end;
	return delim;
}

static char *ft_strjoin_nl(char *content, char *line, t_ctx *ctx)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(line, "\n");
	if (!tmp)
	{
		free(content);
		free(line);
		error(-1, ctx, (t_m){strerror(errno)});
	}
	free(line);
	if (!content)
		return (tmp);
	tmp2 = content;
	content = ft_strjoin(content, tmp);
	if (!content)
	{
		free(tmp);
		free(tmp2);
		error(-1, ctx, (t_m){strerror(errno)});
	}
	free(tmp);
	free(tmp2);
	return (content);
}

static bool	is_valid_delim(char *delim, t_ctx *ctx, t_tok **current)
{
	if (!delim)
	{
		error(2, ctx, (t_m){"syntax error near unexpected token 'newline'"});
		*current = NULL;
		return (false);
	}
	return (true);
}

static	void process_signal(char *content, t_ctx *ctx, t_tok **current)
{
	t_node node;

	node.ctx = ctx;
	restore_stdfd(STDIN_FILENO, &node);
	free(content);
	*current = NULL;
}

static bool	is_eot(char *line, char *delim, t_ctx *ctx)
{
	if (!line || is_eqlstr(line, delim))
	{
		if (!line)
			error(0, ctx, (t_m){"warning: here-document delimited by end-of-file, wanted", delim + TOK});
		free(line);
		return (true);
	}
	return (false);
}

static void	tokenize_content(char *delim, t_ctx *ctx, t_tok **tokens, t_tok **current)
{
	char	*content;
	char	*line;
	t_tok	*new;

	if (!is_valid_delim(delim, ctx, current))
		return ;
	content = ft_strdup("");
	if (!content)
		error(-1, ctx, (t_m){strerror(errno)});
	new = NULL;
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			process_signal(content, ctx, current);
			return ;
		}
		if (is_eot(line, delim, ctx))
			break ;
		content = ft_strjoin_nl(content, line, ctx);
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
	setup_signals(IS_HEREDOC, ctx);
	tokenize_content(get_delimeter(lexeme, ctx), ctx, tokens, current);
	setup_signals(IS_IGNORE, ctx);
}
