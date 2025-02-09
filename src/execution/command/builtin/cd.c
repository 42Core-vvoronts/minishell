/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/07 10:06:49 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static	void	handle_no_args(t_node *node)
{
	char	**var;
	char	*path;

	var = get_var(node->ctx, "HOME");
	if (!var)
		error(node, STRUCT_NODE, HOME_NOT_SET_CD, false);
	else
	{
		path = ft_strchr(*var, '=') + 1;
		free(node->ctx->stash[1]);
		node->ctx->stash[1] = ft_strdup(path);
		if (!node->ctx->stash[1])
			error(node, STRUCT_NODE, MALLOC_FAIL, true);
	}
}

static	void	handle_dash_arg(t_node *node)
{
	char	**var;
	char	*path;

	var = get_var(node->ctx, "OLDPWD");
	if (!var)
	{
		error(node, STRUCT_NODE, OLDPWD_NOT_SET_CD, false);
		node->ctx->stash[1][0] = '\0';
	}
	else
	{
		path = ft_strchr(*var, '=') + 1;
		printf("%s\n", path);
		free(node->ctx->stash[1]);
		node->ctx->stash[1] = ft_strdup(path);
		if (!node->ctx->stash[1] || !*var || !*path)
			error(node, STRUCT_NODE, MALLOC_FAIL, true);
	}
}

static	void	update_pwds(t_node *node, char *pwd)
{
	char *envvar;

	envvar = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	if (!envvar)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	add_var(node, envvar);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	envvar = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!envvar)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	add_var(node, envvar);

}

void	run_cd(t_node *node)
{
	size_t	len;
	char	*pwd;

	node->ctx->exitcode = EXIT_SUCCESS;
	len = ft_parrlen(node->ctx->stash);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	if (len == 2 && is_eqlstr(node->ctx->stash[1], "-"))
		handle_dash_arg(node);
	else if (len == 1)
		handle_no_args(node);
	else if (len > 2)
	{
		error(node, STRUCT_NODE, TOO_MANY_ARG_CD, false);
		return;
	}
	if (!node->ctx->stash[1][0])
		;
	else if (chdir(node->ctx->stash[1]) == ERROR)
		error(node, STRUCT_NODE, ERRNO_CD, false);
	else
		update_pwds(node, pwd);//update PWD and OLDPWD
//-----------------delete later
	printf("\ngetcwd: %s\n", getcwd(NULL, 0));
	char **path = get_var(node->ctx, "PWD");
	if (path)
		printf("PWD: %s\n", *path);
	path = get_var(node->ctx, "OLDPWD");
	if (path)
		printf("OLDPWD: %s\n", *path);
}
