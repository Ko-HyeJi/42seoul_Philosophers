# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/09 15:40:30 by hyko              #+#    #+#              #
#    Updated: 2022/08/12 22:38:17 by hyko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAG = -Wall -Wextra -Werror #-g3 -fsanitize=thread
DEBUG = -g -fsanitize=address
RM = rm -rf
INCLUDE = include

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

SRC = $(addprefix ./src/, main.c\
philo_utils.c\
initialize.c\
thread.c\
routine.c)

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAG) -o $@ $^

all : $(NAME)

debug :
	$(MAKE) DEBUG_FLAG=1 all

clean :
	$(RM) $(OBJ) $(OBJ_BN)

fclean : clean
	$(RM) $(NAME) $(BONUS)

re : fclean all

.PHONY : all clean fclean re debug
