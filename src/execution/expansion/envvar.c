/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:53:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/06 01:17:41 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char **get_var(t_ctx *ctx, char *varname)
{
	char	**envp;
	char	*var;
	size_t	len;

	envp = ctx->envp;
	len = ft_strlen(varname);
	while (*envp)
	{
		var = ft_strnstr(*envp, varname, len);
		if (var)
			return (envp);
		envp++;
	}
	return (NULL);
}

char *get_val(t_ctx *ctx, char *varname)
{
	size_t	len;
	char	**var;

	len = ft_strlen(varname);
	var = get_var(ctx, varname);
	if (var)
		return (*var + len + 1);
	return (NULL);
}
