# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/18 16:52:21 by mpedraza          #+#    #+#              #
#    Updated: 2025/11/28 12:32:19 by mpedraza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I .

FTS := ft_printf ft_chr_utils ft_hex_utils ft_int_utils
SRCS := $(FTS:%=%.c)
OBJS := $(SRCS:%.c=%.o)
#TEST := test_printf
#TESTSRCS := $(TEST:%=%.c)
#TESTOBJS := $(TESTSRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

# test: $(TEST)

# $(TEST): $(NAME) $(TESTOBJS)
#	$(CC) $(CFLAGS) -o $(TEST) -L. $(TESTOBJS) -lftprintf 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

# tclean: fclean
#	$(RM)$(TESTOBJS) $(TEST)

re: fclean all

.PHONY: all clean fclean re test tclean



