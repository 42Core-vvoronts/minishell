/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wraperror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:07:01 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 16:51:50 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parserror(char *type, char *lexeme, int code, t_ctx *ctx)
{
	char *msg;
	
	if (is_eqlstr(type, "syntax"))
		msg = "syntax error near unexpected token";
	else
		msg = type;
	if (lexeme)
		error(code, ctx, (t_m){msg, lexeme+TOK});
	else
		error(code, ctx, (t_m){msg, NULL});
	return (NULL);
}
