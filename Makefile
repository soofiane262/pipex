# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 19:01:47 by sel-mars          #+#    #+#              #
#    Updated: 2021/12/28 21:49:03 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libpipex.a

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror

AR		=	ar rc

RM		=	rm -f

SRCS	=	pipex_ext.c ft_split.c ft_strlen.c ft_strncmp.c ft_substr.c ft_strjoin.c

OBJS	=	$(SRCS:.c=.o)

PGM		=	pipex.c

HDFL	=	pipex.h

all: $(NAME)

$(NAME): $(SRCS) $(HDFL) $(PGM)
	@$(CC) $(FLAGS) -c $(SRCS) -I $(HDFL)
	@$(AR) $(NAME) $(OBJS)
	@$(CC) $(FLAGS) $(PGM) -L. -lpipex -o pipex

norm:
	@norminette $(PGM) $(SRCS) $(HDFL)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
