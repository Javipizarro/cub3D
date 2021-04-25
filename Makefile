# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 11:24:00 by jpizarro          #+#    #+#              #
#    Updated: 2021/04/25 21:04:30 by jpizarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re run debug

NAME = cub3D

SRCS = $(wildcard srcs/*.c)

OBJS = $(SRCS:.c=.o)

LIBFOLDERS = $(wildcard libs/*)

LIBS = $(wildcard libs/*/*.h)

STATICS = $(LIBS:.h=.a)

MAKES = $(wildcard libs/*/Makefile)

#STEM = $(LIBS:*/*.h=*)


CC = gcc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(STATICS)
	@echo "Creating $@"
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(STATICS) -o $@
	@echo "$@ is ready!"

%.o: %.c
#	@echo "files that need to be compiled: $?"
#	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@$(CC) -g -c $< -o $(<:.c=.o)

#$(STATICS):
#	cd $(LIBFOLDERS) && $(MAKE)

$(STATICS):
#	cd libs/mathft/ && $(MAKE)
	cd libs/libft/ && $(MAKE)
#	cd libs/color/ && $(MAKE)
	cd libs/get_next_line/ && $(MAKE)


clean:
	@echo "Cleaing up binary files"
	@$(RM) $(OBJS)
#	cd libs/mathft/ && $(MAKE) $@
	cd libs/libft/ && $(MAKE) $@
#	cd libs/color/ && $(MAKE) $@
	cd libs/get_next_line/ && $(MAKE) $@


fclean: clean
	@echo "also $(NAME) and debug files"
	@$(RM) $(NAME) debug
#	cd libs/mathft/ && $(MAKE) $@
	cd libs/libft/ && $(MAKE) $@
#	cd libs/color/ && $(MAKE) $@
	cd libs/get_next_line/ && $(MAKE) $@

re: fclean all

run: all
	@./$(NAME) map.cub

debug: fclean $(OBJS) $(STATICS)
	@echo "Creating $@ file"
	@$(CC) -g $(MLXFLAGS) $(OBJS) $(STATICS) -o $@
#	@$(CC) -g $(CFLAGS) $(MLXFLAGS) $(OBJS) $(STATICS) -o $@
	@echo "$@ is ready!"

debrun: debug
	gdb $(NAME)

show:
	@echo "SRCS $(SRCS)"
	@echo "OBJS $(OBJS)"
	@echo "MAKES $(MAKES)"
	@echo "LIBFOLDERS $(LIBFOLDERS)"
	@echo "LIBS $(LIBS)"
	@echo "statics $(STATICS)"
	