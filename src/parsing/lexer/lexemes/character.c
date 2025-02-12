/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/12 17:28:31 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_character(char *lexeme)
{
	if (is_eqlchar(*lexeme, '*') || is_eqlchar(*lexeme, '$') ||
		is_eqlchar(*lexeme, '?') || ft_isprint(*lexeme))
		return true;
	return false;
}
