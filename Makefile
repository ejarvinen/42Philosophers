# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 14:50:50 by emansoor          #+#    #+#              #
#    Updated: 2024/06/27 08:46:20 by emansoor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = error.c \
		main.c \
		philo_utils.c \
		initialize.c \
		create_philos.c \
		philo_routine.c \
		print_status.c \
		monitor.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	@gcc -Wall -Wextra -Werror -c -pthread $< -o $(<:.c=.o)

$(NAME): $(OBJECTS)
	@gcc -Wall -Wextra -Werror -pthread $(OBJECTS) -o $(NAME)
	@echo philo compiled

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug:
	@gcc -Wall -Wextra -Werror -g -fsanitize=thread $(OBJECT) -o $(NAME)

.PHONY: clean fclean all re