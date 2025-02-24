/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:28:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 03:35:25 by ipetrov          ###   ########.fr       */
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
	return (delim);
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

static	bool	get_quotes_ctx(char *delim)
{
	return (ft_strchr(delim, '\'') || ft_strchr(delim, '"'));
}

static size_t	get_len_bare_delim(char *delim)
{
	size_t len;

	len = 0;
	while (*delim)
	{
		if (*delim != '\'' || *delim != '"')
			len++;
		delim++;
	}
	return (len);
}
//returns false if delim invalid
//puts delimed cleaned of quotes into char **delim
//if there were quotes puts true into bool *quotes
static bool	get_valid_delim(char **delim, t_ctx *ctx, t_tok **current, bool *quotes)
{
	char *new_delim;
	size_t i;
	size_t j;

	if (!*delim)
	{
		error(2, ctx, (t_m){"syntax error near unexpected token 'newline'"});
		*current = NULL;
		return (false);
	}
	*quotes = get_quotes_ctx(*delim);
	new_delim = ft_calloc(get_len_bare_delim(*delim) + 1, sizeof(char)); //check for fail
	i = 0;
	j = 0;
	while ((*delim)[i])
	{
		if ((*delim)[i] != '\'' && (*delim)[i] != '"')
			new_delim[j++] = (*delim)[i];
		i++;
	}
	free(*delim);
	*delim = new_delim;
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

static void	attach_token(char	*content, t_ctx *ctx, t_tok **tokens, t_tok **current)
{
	t_tok	*new;

	new = NULL;
	new = init_token(content, ft_strlen(content), ctx);
	ctx->exitcode = 0;
	add_token(new, tokens, current);
}

//flag that quotes here
static	char	*add_quotes_flag(char *content, t_ctx *ctx)
{
	char	*q_content;
	size_t	i;
	size_t	j;

	i = ft_strlen(content);
	q_content = ft_calloc(i + 2, sizeof(char));
	if (!q_content)
		error(-1, ctx, (t_m){strerror(errno)});
	i = 0;
	j = 0;
	q_content[i++] = 1;
	while(content[j])
		q_content[i++] = content[j++];
	free(content);
	return (q_content);
}

static void	tokenize_content(char *delim, t_ctx *ctx, t_tok **tokens, t_tok **current)
{
	char	*content;
	char	*line;
	bool	quotes;

	if (!get_valid_delim(&delim, ctx, current, &quotes))
		return ;
	content = ft_strdup("");
	if (!content)
		error(-1, ctx, (t_m){strerror(errno)});
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
	if (quotes == true)
		content = add_quotes_flag(content, ctx);
	attach_token(content, ctx, tokens, current);
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
