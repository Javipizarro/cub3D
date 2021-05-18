# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 11:24:00 by jpizarro          #+#    #+#              #
#    Updated: 2021/05/18 20:30:20 by jpizarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean debug fclean re run show

NAME = cub3D

SRCS =	srcs/bmp_maker.c srcs/cub3d.c srcs/dot_cub_parser.c srcs/dot_cub_parser_utils_1.c srcs/dot_cub_parser_utils_2.c srcs/eventer.c srcs/game_setup.c srcs/game_start_and_end.c srcs/mapper.c srcs/mapper_utils.c srcs/painter.c srcs/raycaster.c srcs/spriter.c srcs/utils.c

OBJS = $(SRCS:.c=.o)

LIBS = libs/libft/libft.h libs/get_next_line/get_next_line.h

STATICS = $(LIBS:.h=.a)

CC = gcc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(STATICS)
	echo "Creating $@"
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(STATICS) -o $@
	echo "$@ is ready!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(STATICS):
	cd libs/libft/ && $(MAKE)
	cd libs/get_next_line/ && $(MAKE)


clean:
	echo "Cleaing up binary files"
	$(RM) $(OBJS)
	cd libs/libft/ && $(MAKE) $@
	cd libs/get_next_line/ && $(MAKE) $@


fclean: clean
	echo "also $(NAME), debug and .bmp files"
	$(RM) $(NAME) debug
	$(RM) $(wildcard *.bmp)
	cd libs/libft/ && $(MAKE) $@
	cd libs/get_next_line/ && $(MAKE) $@

re: fclean all

run: all
	./$(NAME) map.cub

bmp: all
	./$(NAME) map.cub --save

debug: fclean $(OBJS) $(STATICS)
	echo "Creating $@ file"
	$(CC) -g $(MLXFLAGS) $(OBJS) $(STATICS) -o $@
	echo "$@ is ready!"

show:
	@echo "SRCS $(SRCS)"
	@echo "OBJS $(OBJS)"
	@echo "MAKES $(MAKES)"
	@echo "LIBFOLDERS $(LIBFOLDERS)"
	@echo "LIBS $(LIBS)"
	@echo "statics $(STATICS)"
	