/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:11:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 14:23:54 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_blank(char *lexeme)
{
	if (*lexeme
		&& (is_eqlchar(*lexeme, ' ') || is_eqlchar(*lexeme, '\t')))
		return (true);
	return (false);
}

void	skip_blanks(char **lexeme)
{
	while (is_blank(*lexeme))
		(*lexeme)++;
}
