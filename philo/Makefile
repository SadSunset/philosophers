# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 17:38:23 by fbinary           #+#    #+#              #
#    Updated: 2022/06/28 17:38:26 by fbinary          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	philo.c\
		inits.c\
		lifecycle.c\
		timefuncs.c\
		print.c\
		validation/validate_inputs.c\
		validation/utils.c\


OBJ = $(SRC:.c=.o)
NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
HEADER = philo.h


all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		rm -f $(OBJ)
fclean: clean
		rm -f $(NAME)


$(OBJ):			$(HEADER)
re: fclean all

.PHONY: all clean fclean re
