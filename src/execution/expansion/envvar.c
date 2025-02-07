/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:53:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/07 01:44:39 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static	bool	is_eqlvar(char *envvar, char *varname)
{
	while ((*envvar || *varname) && (*envvar != '=' || *varname != '='))
	{
		if (*envvar != *varname)
			return (false);
		envvar++;
		varname++;
	}
	return (true);
}

char **get_var(t_ctx *ctx, char *varname)
{
	char	**envp;

	envp = ctx->envp;
	while (*envp)
	{
		if (is_eqlvar(*envp, varname))
			return (envp);
		envp++;
	}
	return (NULL);
}

char *get_val(t_ctx *ctx, char *varname)
{
	char	**var;

	var = get_var(ctx, varname);
	if (var)
		return (*var + (ft_strchr(*var, '=') - *var));
	return (NULL);
}
