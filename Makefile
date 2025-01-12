# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:48:31 by vvoronts          #+#    #+#              #
#    Updated: 2025/01/12 14:58:14 by vvoronts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -MMD -MF
RM					=	rm -rf
NAME				=	minishell


INCLUDE_DIRS		=	./include \
						./lib/libft \
						./lib/ft_printf \

VPATH				=	./src \

INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))


SRCS 				=	minishell.c \
						parsing.c \
						scanner.c \
						lexer.c \
						syntaxer.c \
						printer.c \
						

LIBS 				=	./lib/libft/libft.a \
						./lib/ft_printf/ft_printf.a \
						-lreadline


OBJ				=	$(SRCS:%.c=obj/$(NAME)/%.o)

DEP				=	$(SRCS:%.c=dep/$(NAME)/%.d)

MFLAGS				= --no-print-directory -C


all: $(NAME)
	@echo "Building $(NAME) ..."

$(NAME): $(OBJ) libs
	@$(CC) $(OBJ) $(LIBS) -o $@

libs:
	@make $(MFLAGS) ./lib/libft
	@make $(MFLAGS) ./lib/ft_printf

obj/$(NAME)/%.o: %.c | obj_dir dep_dir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@

obj_dir:
	@mkdir -p obj/$(NAME)

dep_dir:
	@mkdir -p dep/$(NAME)

dep:
	@mkdir -p dep/$(NAME)

clean:
	@echo "Cleaning ..."
	@$(RM) obj
	@$(RM) dep
	@make clean $(MFLAGS) ./lib/libft
	@make clean $(MFLAGS) ./lib/ft_printf

fclean: clean
	@$(RM) $(NAME)
	@make fclean $(MFLAGS) ./lib/libft
	@make fclean $(MFLAGS) ./lib/ft_printf

re: fclean all

.PHONY: all clean fclean re libs
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)