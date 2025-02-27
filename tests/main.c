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
#include <sys/wait.h>

int	main()
{
	write(STDOUT_FILENO, "ABCDEF", 6);
	write(STDOUT_FILENO, "\b\b", 2);
	'\b';
}