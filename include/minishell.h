/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/05 01:48:53 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/elibft/include/elibft.h"

# include <ctype.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <string.h>    // strlen
# include <stdlib.h>    // exit
# include <unistd.h>    // syscalls
# include <readline/readline.h>
# include <readline/history.h>

# define REDIR_FAIL 1

typedef enum t_type
{
	AND,
	OR,
	GROUP,
	PIPE,
	WORD_ZERO_QUOTES,
	WORD_SINGLE_QUOTES,
	WORD_DOUBLE_QUOTES,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC_QUOTES,
	REDIR_HEREDOC_NOQUOTES
}	t_type;

typedef struct s_ctx
{
	char **envp;
	char *ttyname;
	char **stash;
	int	*opened_fd;
	pid_t exitcode;
} t_ctx;

typedef struct s_node
{
	t_ctx			*ctx;
	t_type			type;
	char			*token;
	struct s_node	*left;
	struct s_node	*right;
} t_node;

typedef struct s_pipe
{
	int read;
	int write;
} t_pipe;

typedef struct s_tok
{
	t_type			type;
	char			*lexeme;
	struct s_tok	*next;
} t_tok;

void	process_and(t_node	*node);
void	process_or(t_node	*node);

void	add_arg(char *arg, char * **stash);
char	*pop_arg(char * **stash);
char 	**get_argv(char * **args);

void 	run_cmd(t_node *node);

int		get_exitcode(pid_t pid);


void	process_group(t_node *node);


void	process_pipe(t_node *node);
int		open_pipe(t_pipe *p);
int		close_pipe(t_pipe *p);

void	process_redir_append(t_node *node);
void	process_redir_heredoc(t_node *node);
void	process_redir_in(t_node *node);
void	process_redir_out(t_node *node);

void	process_word_zero_quotes(t_node *node);
void	process_word_single_quotes(t_node *node);
void	process_word_double_quotes(t_node *node);

void	evaluate_node(t_node *node);

#endif
