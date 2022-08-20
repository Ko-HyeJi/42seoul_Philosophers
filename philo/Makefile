# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/09 15:40:30 by hyko              #+#    #+#              #
#    Updated: 2022/08/20 16:35:52 by hyko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread
RM = rm -rf
INCLUDE = include

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

SRC = $(addprefix ./src/, main.c\
initialize.c\
monitoring_thread.c\
philo_thread.c\
print.c\
routine.c\
time.c\
utils.c)

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
