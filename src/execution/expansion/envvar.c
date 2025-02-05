/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:53:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 05:57:11 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *get_varvalue(t_ctx *ctx, char *varname)
{
	char	**envp;
	char	*value;
	size_t	len;

	envp = ctx->envp;
	len = ft_strlen(varname);
	while (*envp)
	{
		value = ft_strnstr(*envp, varname, len);
		if (value)
		{
			return (value + len + 1);
		}
		envp++;
	}
	return (NULL);
}
