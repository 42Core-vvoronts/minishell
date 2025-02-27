/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/26 06:26:05 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit(1): bash: cd: HOME not set
static	void	handle_no_args(t_node *node)
{
	char	**var;
	char	*path;

	var = get_var(node->ctx, "HOME");
	if (!var)
		error(1, node->ctx, (t_m){CD, CD_HOME});
	else
	{
		path = ft_strchr(*var, '=') + 1;
		path = ft_strdup(path);
		if (!path)
			error(-1, node->ctx, (t_m){strerror(errno)});
		add_stash(path, node);
	}
}

//exit(1) bash: cd: OLDPWD not set
static	void	handle_dash_arg(t_node *node)
{
	char	**var;
	char	*path;

	var = get_var(node->ctx, "OLDPWD");
	if (!var)
	{
		error(1, node->ctx, (t_m){CD, CD_OLDPWD});
		node->ctx->stash[1][0] = '\0';
	}
	else
	{
		path = ft_strchr(*var, '=') + 1;
		printf("%s\n", path);
		free(node->ctx->stash[1]);
		node->ctx->stash[1] = ft_strdup(path);
		if (!node->ctx->stash[1] || !*var || !*path)
			error(-1, node->ctx, (t_m){strerror(errno)});
	}
}

static	void	update_pwds(t_node *node, char *pwd)
{
	char *envvar;

	envvar = ft_strjoin("OLDPWD=", pwd);
	if (!envvar)
		error(-1, node->ctx, (t_m){strerror(errno)});
	add_var(node, envvar);
	free(envvar);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		error(-1, node->ctx, (t_m){strerror(errno)});
	envvar = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!envvar)
		error(-1, node->ctx, (t_m){strerror(errno)});
	add_var(node, envvar);
	free(envvar);

}
//exit(1); bash: cd: too many arguments
//exit(1); bash: cd: /GitHub/ls: Not a directory
//exit(1); bash: cd: /GitHdfdfub/: No such file or directory
void	run_cd(t_node *node)
{
	size_t	len;
	char	*pwd;

	node->ctx->exitcode = EXIT_SUCCESS;
	len = ft_parrlen(node->ctx->stash);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		error(-1, node->ctx, (t_m){strerror(errno)});
	if (len == 2 && is_eqlstr(node->ctx->stash[1], "-"))
		handle_dash_arg(node);
	else if (len == 1)
		handle_no_args(node);
	else if (len > 2)
	{
		error(1, node->ctx, (t_m){CD, TOO_MANY_ARG});
		free(pwd);
		return;
	}
	if (!node->ctx->stash[1][0])
		;
	else if (chdir(node->ctx->stash[1]) == ERROR)
		error(1, node->ctx, (t_m){CD, node->ctx->stash[1], strerror(errno)});
	else
		update_pwds(node, pwd);
	free(pwd);
}
//update PWD and OLDPWD
// //-----------------delete later
// 	printf("\ngetcwd: %s\n", getcwd(NULL, 0));
// 	char **path = get_var(node->ctx, "PWD");
// 	if (path)
// 		printf("PWD: %s\n", *path);
// 	path = get_var(node->ctx, "OLDPWD");
// 	if (path)
// 		printf("OLDPWD: %s\n", *path);