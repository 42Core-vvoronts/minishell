/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:28:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/28 10:40:15 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	attach_token(char *content, t_ctx *ctx, t_tok **tokens, t_tok **cur)
{
	t_tok	*new;

	new = NULL;
	new = init_token(content, ft_strlen(content), ctx);
	ctx->exitcode = 0;
	free(content);
	add_token(new, tokens, cur);
}

void	tokenize_heredoc(char **lexeme, t_tok **tokens, t_tok **cur, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;
	char	*delim;

	start = *lexeme;
	end = start + 1;
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tokens, cur);
	*lexeme = end + 1;
	setup_signals(IS_HEREDOC, ctx);
	delim = get_delimeter(lexeme, ctx);
	tokenize_content(delim, ctx, tokens, cur);
	setup_signals(IS_RUNNING, ctx);
}
