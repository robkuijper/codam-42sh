# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: omulder <omulder@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/04/11 14:45:11 by omulder       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I./ -I./libft/ -I./includes
LIBFT= ./libft/libft.a
LIB = -L./libft/ -lft -ltermcap
VPATH = ./srcs
SRCS = main init_term
SRCS := $(SRCS:%=%.c)
OBJECTS = $(SRCS:.c=.o)

all: $(OBJECTS) $(LIBFT) $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(INCLUDES) $(LIB) -o $(NAME) $^

$(OBJECTS): $(SRCS)
	$(CC) $(FLAGS) $(INCLUDES) -c $^

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C libft clean
	
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
