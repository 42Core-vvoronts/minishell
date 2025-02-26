#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
# define FILE_NOT_FOUND "No such file or directory"
# define CMD_NOT_FOUND "command not found"
# define AMBIGUOUS_REDIR "ambiguous redirect"
# define NOT_VALID_IDENTIFIER "not a valid identifier"
# define SYNTAX_ERROR "syntax error near unexpected token " //syntax error near unexpected token `('
# define SYSTEM NULL
# define ERRNO errno
# define M char *[5]
# define PROGRAMM "bash"
# define TOK 0xf000000000000000
#include <errno.h>
#include <stdarg.h>
# define _POSIX_C_SOURCE 200809L
# include <errno.h>
# include <ctype.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/stat.h>

// typedef char *t_m[5];


// void puterr(char *str)
// {
// 	write(STDERR_FILENO, str, strlen(str));
// }

// void error(int exitcode, t_m msg)
// {
// 	(void)exitcode;
// 	puterr(PROGRAMM);
// 	while (*msg)
// 	{
// 		if (*msg > (char *)TOK)
// 		{
// 			puterr(" `");
// 			puterr(*msg - TOK);
// 			puterr("\'");
// 			msg++;
// 			continue ;
// 		}
// 		puterr(": ");
// 		puterr(*msg);
// 		msg++;
// 	}
// 	puterr("\n");
// }

// void get_msg(int n, ...)
// {
// 	write(1, (char *)(&n + 1), strlen((char *)(&n + 1)));
// }

int	main()
{
	int fd = dup(STDIN_FILENO);
	pid_t pid = fork();
	if (pid > 0)
	{
		close(fd);
	}

	// char *str;
	// char **test;
	// int fd[2];
	// dup(STDIN_FILENO);
	// pipe(fd);
	// malloc(1000);
	// str = malloc(7777);
	// test = malloc(sizeof(char *));
	// *test = str;
	// free(test);
	// str = NULL;
	// char *str;

	// str = FILE_NOT_FOUND;
	// str = AMBIGUOUS_REDIR;
	// str = NOT_VALID_IDENTIFIER;
	// str = SYNTAX_ERROR;
	// str = SYSTEM;
	// str = CMD_NOT_FOUND;
	// // void *p2 = (void*)0xffffffffffffffff;

	// size_t p1 = 0x7fffffffe318;
	// size_t p2 = 0xf000000000000000;
	// // size_t p2 = ULLONG_MAX;
	// size_t p4 = p1 | p2;
	// size_t p5 = p4 ^ p2;
	// error(1, (t_m){FILE_NOT_FOUND + TOK, NULL});
}