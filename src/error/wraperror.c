/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wraperror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:07:01 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 09:42:23 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parserror(char *type, char *lexeme, int code, t_ctx *ctx)
{
	char	*msg;

	if (is_eqlstr(type, "syntax"))
		msg = "syntax error near unexpected token";
	else
		msg = "??";
	if (lexeme)
		error(code, ctx, (t_m){msg, lexeme + TOK});
	else
		error(code, ctx, (t_m){msg, NULL});
	return (NULL);
}
