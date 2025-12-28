# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/28 18:48:07 by mpedraza          #+#    #+#              #
#    Updated: 2025/12/28 22:32:02 by mpedraza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minitalk

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Iftprintf -D _DEFAULT_SOURCE

SRCS	= client.c server.c
OBJS	= $(SRCS:%.c=%.o)

all: ${NAME}

${NAME}: client server

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

server: server.o ftprintf
	${CC} ${CFLAGS} server.o -Lftprintf -lftprintf -o server
client: client.o ftprintf
	${CC} ${CFLAGS} client.o -Lftprintf -lftprintf -o client

ftprintf:
	$(MAKE) -C ftprintf

clean:
	$(MAKE) -C ftprintf clean
	${RM} ${OBJS}

fclean: clean
	$(MAKE) -C ftprintf fclean
	${RM} server client

re: fclean all

.PHONY: all clean fclean re ftprintf server client