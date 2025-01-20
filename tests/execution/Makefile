# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:48:31 by vvoronts          #+#    #+#              #
#    Updated: 2025/01/20 17:05:55 by ipetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC					=	cc
CFLAGS				=	-g -MMD -MF
RM					=	rm -rf

# Name of the output library
NAME				=	minishell

# Include directories
INCLUDE_DIRS		=	\
						../../include \
						../../lib/elibft \

# Source directories
VPATH				=	\
						../../src \
						. \

# Include flags
INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

# Libraries
LIB 				=	\
						../../lib/elibft/elibft.a \
						-lreadline \

# Source files
SRC 				=	\
						main.c \
						parser.c \
						lexer.c \
						validator.c \
						syntaxer.c \
						printer.c \
						execution.c \



# Object and Dependency files
OBJ					=	$(SRC:%.c=obj/%.o)
DEP					=	$(SRC:%.c=dep/%.d)

# Make flags
MFLAGS				=	 --no-print-directory -C


# Build all targets
all: lib $(NAME)
	@echo "Building $(NAME) ..."
	@./minishell

# Link mandatory object files
$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $@
	@echo "$(NAME) has been built"

# Build libraries
lib:
	@make $(MFLAGS) ../../lib/elibft

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
	@make clean $(MFLAGS) ../../lib/elibft
	@echo "$(NAME) has been cleaned"
	@echo "$(NAME) has been cleaned"

# Clean build files and executables
fclean: clean
	@make fclean $(MFLAGS) ../../lib/elibft
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re lib
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)
