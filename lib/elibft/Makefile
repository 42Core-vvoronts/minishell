# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 16:48:06 by ipetrov           #+#    #+#              #
#    Updated: 2025/01/12 18:39:42 by ipetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -MMD -MF
RM					=	rm -rf

# Name of the output library
NAME 				=	elibft.a

# Include directories
INCLUDE_DIRS		=	./include \

# Source directories
VPATH				=	\
						./src/array:\
						./src/conversion:\
						./src/file:\
						./src/list:\
						./src/memory:\
						./src/output:\
						./src/parr:\
						./src/string:\

# Include flags
INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

# Source files
SRC					= 	arr_add.c \
						arr_clean.c \
						arr_del.c \
						arr_extract.c \
						arr_insert.c \
						arr_iter.c \
						arr_madd.c \
						arr_new.c \
						arr_retrieve.c \
						\
						ft_atoi.c \
						strs_to_arr.c \
						\
						get_next_line.c \
						\
						lst_add_after.c \
						lst_clean.c \
						lst_get.c \
						lst_insert_after.c \
						lst_iter.c \
						lst_new.c \
						\
						ft_alloc.c \
						ft_bzero.c \
						ft_calloc.c \
						ft_free.c \
						ft_memchr.c \
						ft_memcmp.c \
						ft_memcpy.c \
						ft_memmove.c \
						ft_memset.c \
						\
						ft_printf.c \
						ft_putchar_fd.c \
						ft_putendl_fd.c \
						ft_putnbr_fd.c \
						ft_putstr_fd.c \
						\
						ft_parrclean.c \
						ft_parrjoin.c \
						ft_parrlen.c \
						\
						ft_isalnum.c \
						ft_isalpha.c \
						ft_isascii.c \
						ft_isdigit.c \
						ft_isprint.c \
						ft_strchr.c \
						ft_strcmp.c \
						ft_strdup.c \
						ft_strdups.c \
						ft_striteri.c \
						ft_strjoin.c \
						ft_strlcat.c \
						ft_strlcpy.c \
						ft_strlen.c \
						ft_strmapi.c \
						ft_strncmp.c \
						ft_strnstr.c \
						ft_strrchr.c \
						ft_strtrim.c \
						ft_substr.c \
						ft_tolower.c \
						ft_toupper.c \
						is_eqlstr.c \
						ft_split.c \
# arr_to_lst.c
# lst_to_arr.c
# Object files
OBJ					=	$(SRC:%.c=obj/%.o)


# Dependency files
DEP					=	$(SRC:%.c=dep/%.d)

# Make flags
MFLAGS				=	 --no-print-directory -C

# Build all targets
all: $(NAME)

# Link mandatory object files
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(NAME) has been built"

# Compile mandatory object files
obj/%.o: %.c | obj_dir dep_dir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@

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
	@echo "$(NAME) has been cleaned"

# Clean build files and executables
fclean: clean
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re a
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)