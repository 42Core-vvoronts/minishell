/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:48:29 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/23 17:49:12 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_dollar(char *lexeme)
{
	if (lexeme && is_eqlchar(*lexeme, '$'))
		return true;
	return false;
}
