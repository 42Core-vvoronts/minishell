/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herecontent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:33 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 12:44:26 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	process_signal(char *content, t_ctx *ctx, t_tok **cur)
{
	t_node	node;

	node.ctx = ctx;
	restore_stdfd(STDIN_FILENO, &node);
	free(content);
	*cur = NULL;
}

static bool	is_eot(char *line, char *delim, t_ctx *ctx)
{
	char	*msg;

	msg = "warning: here-document delimited by end-of-file, wanted";
	if (!line || is_eqlstr(line, delim))
	{
		if (!line)
			error(0, ctx, (t_m){msg, delim + TOK});
		free(line);
		return (true);
	}
	return (false);
}

//add char = 1 as the first character if we need to expand content
static	char	*add_expand_flag(char *content, t_ctx *ctx, bool quotes)
{
	char	*q_content;
	size_t	i;
	size_t	j;

	if (quotes == true)
		return (content);
	i = ft_strlen(content);
	q_content = ft_calloc(i + 2, sizeof(char));
	if (!q_content)
		error(-1, ctx, (t_m){strerror(errno)});
	i = 0;
	j = 0;
	q_content[i++] = 1;
	while (content[j])
		q_content[i++] = content[j++];
	free(content);
	return (q_content);
}

static char	*ft_strjoin_nl(char *content, char *line, t_ctx *ctx)
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

void	tokenize_content(char **delim, t_ctx *ctx, t_tok **tokens, t_tok **cur)
{
	char	*content;
	char	*line;
	bool	quotes;

	if (!get_valid_delim(delim, ctx, cur, &quotes))
		return ;
	content = ft_strdup("");
	if (!content)
		error(-1, ctx, (t_m){strerror(errno)});
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			process_signal(content, ctx, cur);
			ctx->errlex = true;
			return ;
		}
		if (is_eot(line, *delim, ctx))
			break ;
		content = ft_strjoin_nl(content, line, ctx);
	}
	content = add_expand_flag(content, ctx, quotes);
	attach_token(content, ctx, tokens, cur);
}
