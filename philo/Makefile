# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 18:01:14 by teambersaw        #+#    #+#              #
#    Updated: 2022/04/27 22:14:28 by teambersaw       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc

CFLAGS= -Wall -Wextra -Werror

SRCS= philosophers.c philo_init.c philo_routine.c philo_check_end.c \
		philo_time.c\

OBJS= ${SRCS:.c=.o}

HEADER= philosophers.h

NAME= philo

${NAME}: ${OBJS} ${HEADER}
		${CC} ${CFLAGS} -pthread ${OBJS} -o ${NAME}

all: ${NAME}

clean: 
	rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re