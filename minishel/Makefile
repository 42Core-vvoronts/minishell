# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:48:31 by vvoronts          #+#    #+#              #
#    Updated: 2025/01/05 17:48:44 by vvoronts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 14:07:44 by vvoronts          #+#    #+#              #
#    Updated: 2025/01/05 14:21:07 by vvoronts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -MMD -MF
RM					=	rm -rf
NAME				=	minishel
# BONUS_NAME			=	


INCLUDE_DIRS		=	./include \
						./lib/libft \
						./lib/ft_printf \

VPATH				=	./src

INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

SHARED_SRC			= 	\

MANDATORY_SRC 		=	$(SHARED_SRC) \
						main.c \

BONUS_SRC 			=	$(SHARED_SRC) \

LIBS 				=	./lib/libft/libft.a \


MANDATORY_OBJ		=	$(MANDATORY_SRC:%.c=obj/$(NAME)/%.o)
BONUS_OBJ			= 	$(BONUS_SRC:%.c=obj/$(BONUS_NAME)/%.o)

DEP					=	$(MANDATORY_SRC:%.c=dep/%.d) $(BONUS_SRC:%.c=dep/%.d)

MFLAGS				= --no-print-directory -C

a: all bonus

all: $(NAME)
	@echo "Building $(NAME) ..."

bonus: $(BONUS_NAME)
	@echo "Building $(BONUS_NAME) ..."

$(NAME): $(MANDATORY_OBJ) libs
	@$(CC) $(MANDATORY_OBJ) $(LIBS) -o $@

$(BONUS_NAME): $(BONUS_OBJ) libs
	@$(CC) $(BONUS_OBJ) $(LIBS) -o $@

libs:
	@make $(MFLAGS) ./lib/libft
	@make $(MFLAGS) ./lib/ft_printf

obj/$(NAME)/%.o: %.c | mandatory_dep mandatory_obj_dir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@

obj/$(BONUS_NAME)/%.o: %.c | bonus_dep bonus_obj_dir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@

mandatory_obj_dir:
	@mkdir -p obj
	@mkdir -p obj/$(NAME)

bonus_obj_dir:
	@mkdir -p obj
	@mkdir -p obj/$(BONUS_NAME)

mandatory_dep:
	@mkdir -p dep
	@mkdir -p dep/$(NAME)

bonus_dep:
	@mkdir -p dep
	@mkdir -p dep/$(BONUS_NAME)

clean:
	@echo "Cleaning ..."
	@$(RM) obj
	@$(RM) dep
	@make clean $(MFLAGS) ./lib/libft
	@make clean $(MFLAGS) ./lib/ft_printf

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@make fclean $(MFLAGS) ./lib/libft
	@make fclean $(MFLAGS) ./lib/ft_printf

re: fclean a

.PHONY: all clean fclean re bonus libs a
.DEFAULT_GOAL := a

# Include the dependency files
-include $(DEP)