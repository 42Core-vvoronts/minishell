/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:29:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/20 18:50:56 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int apply_redirs()
{
	// redir_in("./infile");
	// redir_out("./outfile");
	// redir_append("./outfile");
	// here_doc("EOF\n")
	return (SUCCESS);
}

int	redir_in(char *pathname)
{
	int fd;

	fd = open(pathname, O_RDONLY);
	if (fd == ERROR)
	{
		error(NULL, FILE_NOT_FOUND); //bash: infile: No such file or directory / print this msg
		return (FAIL);
	}
	if (dup2(fd, STDIN_FILENO) == ERROR)
	{
		error(NULL, DUP2);
	}
	return (SUCCESS);
}

int	redir_out(char *pathname)
{
	int fd;

	fd = open(pathname, O_WRONLY | O_CREAT, 0777);
	if (fd == ERROR)
	{
		error(NULL, OPEN);
	}
	if (dup2(fd, STDOUT_FILENO) == ERROR)
	{
		error(NULL, DUP2);
	}
	return (SUCCESS);
}

int	redir_append(char *pathname)
{
	int fd;

	fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == ERROR)
	{
		error(NULL, OPEN);
	}
	if (dup2(fd, STDOUT_FILENO) == ERROR)
	{
		error(NULL, DUP2);
	}
	return (SUCCESS);
}


//use pipe always cyrcle input inside for each stage
int	redir_heredoc(char *delim)
{
	char *line;
	int fd[4];
	char *pathname;
	int status;

	fd[0] = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777); //create and write collected from stdin
	fd[1] = open("here_doc", O_RDONLY); //read for expantion
	fd[2] = open("here_doc", O_WRONLY); //result of expanstion
	fd[3] = open("here_doc", O_RDONLY); //final read
	unlink("here_doc");
	if (fd[0] == -1) //check all of fd
	{
		error(NULL, OPEN);
	}
	while (1)
	{
		ft_printf("> ");
		status = get_next_line(STDIN_FILENO, &line);
		//add that all /n changed to /0 and then manually add /n after EOF echeck
		if (status == ERROR)
		{
			error(NULL, GNL); //close all fd here
		}
		if (is_eqlstr(line, delim))
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, fd[0]); //it should return status of write if error there?
		if (line[ft_strlen(line) - 1] != '\n')
		{
			free(line);
			break ;
		}
		free(line);
	}
	close(fd[0]);
	if (dup2(fd[3], STDIN_FILENO) == ERROR)
	{
		error(NULL, DUP2);
	}
	return (SUCCESS);
}
