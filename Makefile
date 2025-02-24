# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:48:31 by vvoronts          #+#    #+#              #
#    Updated: 2025/02/24 11:37:31 by ipetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -Wunreachable-code -g -MMD -MF
RM					=	rm -rf

# Name of the output library
NAME				=	minishell

# Include directories
INCLUDE_DIRS		=	\
						./include \
						./lib/elibft \


# Source directories
VPATH				=	\
						./src/:\
						./src/error/:\
						./src/execution/:\
						./src/execution/andor/:\
						./src/execution/stash/:\
						./src/execution/command/:\
						./src/execution/exitcode/:\
						./src/execution/expansion/:\
						./src/execution/group/:\
						./src/execution/pipe/:\
						./src/execution/redirection/:\
						./src/execution/word/:\
						./src/execution/command/builtin:\
						./src/parsing/:\
						./src/parsing/heredoc/:\
						./src/parsing/syntaxer/:\
						./src/parsing/lexer/:\
						./src/parsing/lexer/lexemes:\
						./src/prompt/:\
						./src/signals/:\
						./src/test/:\
						./test/parsing/:\
						./test/parsing/printer/:\


# Include flags
INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

# Libraries
LIB 				=	\
						./lib/elibft/elibft.a \
						-lreadline \

# Source files
SRC 				=	\
						main.c \
						init.c \
						prompt.c \
						\
						executils.c \
						\
						signals.c \
						\
						parser.c \
						heredoc.c \
						\
						lexer.c \
						words.c \
						operators.c \
						\
						ampersand.c \
						angle.c \
						asterisk.c \
						blank.c \
						character.c \
						dollar.c \
						parenthesis.c \
						quote.c \
						verticalbar.c \
						\
						syntaxer.c \
						list.c \
						groups.c \
						pipelines.c \
						redirections.c \
						expression.c \
						\
						evaluation.c \
						argument.c \
						stash.c \
						content.c \
						filename.c \
						\
						redir_append.c \
						redir_heredoc.c \
						redir_in.c \
						redir_out.c \
						\
						pipe.c \
						pipewrapper.c \
						\
						group.c \
						\
						exitcode.c \
						envvar.c \
						wildcard.c \
						expansion.c \
						\
						command.c \
						path.c \
						\
						and.c \
						or.c \
						\
						error.c \
						clean.c \
						\
						cd.c \
						echo.c \
						env.c \
						exit.c \
						export.c \
						pwd.c \
						unset.c \

ifeq ($(shell if [ -d tests ]; then echo yes; fi),yes)

VPATH				+=	\
						./tests/parsing/printer/:

SRC					+= 	\
						printer.c
endif

# Object and Dependency files
OBJ					=	$(SRC:%.c=obj/%.o)
DEP					=	$(SRC:%.c=dep/%.d)

# Make flags
MFLAGS				=	 --no-print-directory -C



# Build all targets
all: $(NAME)
	@echo "$(NAME) has been built"

# Link mandatory object files
$(NAME): $(OBJ) lib
	@echo "Building $(NAME) ..."
	@$(CC) $(OBJ) $(LIB) -o $@

# Build libraries
lib:
	@make $(MFLAGS) ./lib/elibft

# Compile mandatory object files
obj/%.o: %.c | obj_dir dep_dir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@ && printf "Compiling: $(notdir $< \n)"

# Create mandatory object directories
obj_dir:
	@mkdir -p obj

# Create mandatory dependency directories
dep_dir:
	@mkdir -p dep

# Clean build files
clean:
	@$(RM) obj
	@$(RM) dep
	@make clean $(MFLAGS) ./lib/elibft
	@echo "$(NAME) has been cleaned"

# Clean build files and executables
fclean: clean
	@make fclean $(MFLAGS) ./lib/elibft
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re lib
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)
