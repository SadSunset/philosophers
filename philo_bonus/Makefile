# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 17:40:36 by fbinary           #+#    #+#              #
#    Updated: 2022/06/28 17:41:51 by fbinary          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	philo_bonus.c\
		inits.c\
		lifecycle.c\
		philo_utils.c\
		utils.c\


OBJ = $(SRC:.c=.o)
NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
HEADER = philo_bonus.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		rm -f $(OBJ)
fclean: clean
		rm -f $(NAME)
re: fclean all

$(OBJ):			$(HEADER)

.PHONY: all clean fclean re
