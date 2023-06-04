# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 19:01:28 by aoubhoum          #+#    #+#              #
#    Updated: 2023/06/04 15:21:47 by aoubhoum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SOURCES = philo.c parssing.c utils.c utils2.c\

OBJECTS = $(SOURCES:.c=.o)
CC = cc
CFLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)


%.o: %.c philo.h
	$(CC) -c $(CFLAGS)  $<

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all