# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 11:24:00 by jpizarro          #+#    #+#              #
#    Updated: 2021/03/20 11:50:28 by jpizarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re run

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
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
#	@cd libs/color && $(MAKE)

$(STATICS):
	@cd $(LIBFOLDERS) && $(MAKE)

clean:
	@echo "Cleaing up binary files"
	@$(RM) $(OBJS)
	@cd $(LIBFOLDERS) && $(MAKE) $@


fclean: clean
	@echo "and $(NAME)"
	@$(RM) $(NAME)
	@cd $(LIBFOLDERS) && $(MAKE) $@

re: fclean all

run: all
	@./$(NAME)

show:
	@echo "SRCS $(SRCS)"
	@echo "OBJS $(OBJS)"
	@echo "MAKES $(MAKES)"
	@echo "LIBFOLDERS $(LIBFOLDERS)"
	@echo "LIBS $(LIBS)"
	@echo "statics $(STATICS)"
	