# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 11:24:00 by jpizarro          #+#    #+#              #
#    Updated: 2021/04/10 21:40:48 by jpizarro         ###   ########.fr        #
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
	@$(CC) -c $< -o $(<:.c=.o)

#$(STATICS):
#	cd $(LIBFOLDERS) && $(MAKE)

$(STATICS):
#	cd libs/mathft/ && $(MAKE)
	cd libs/libft/ && $(MAKE)
	cd libs/color/ && $(MAKE)


clean:
	@echo "Cleaing up binary files"
	@$(RM) $(OBJS)
#	cd libs/mathft/ && $(MAKE) $@
	cd libs/libft/ && $(MAKE) $@
	cd libs/color/ && $(MAKE) $@


fclean: clean
	@echo "also $(NAME) and debug files"
	@$(RM) $(NAME) debug
#	cd libs/mathft/ && $(MAKE) $@
	cd libs/libft/ && $(MAKE) $@
	cd libs/color/ && $(MAKE) $@

re: fclean all

run: all
	@./$(NAME)

debug: $(OBJS) $(STATICS)
	@echo "Creating $@ file"
	@$(CC) -g $(CFLAGS) $(MLXFLAGS) $(OBJS) $(STATICS) -o $@
	@echo "$@ is ready!"

show:
	@echo "SRCS $(SRCS)"
	@echo "OBJS $(OBJS)"
	@echo "MAKES $(MAKES)"
	@echo "LIBFOLDERS $(LIBFOLDERS)"
	@echo "LIBS $(LIBS)"
	@echo "statics $(STATICS)"
	