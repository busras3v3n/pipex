# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: busseven <busseven@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 09:59:40 by busseven          #+#    #+#              #
#    Updated: 2025/02/03 09:35:19 by busseven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC 		= 	./Mandatory/pipex.c ./Mandatory/utils.c ./Mandatory/errors.c
BONUS_SRC	=	./Bonus/pipex_bonus.c ./Bonus/utils_bonus.c ./Bonus/errors_bonus.c ./Bonus/utils2_bonus.c
OBJS 		= $(SRC:.c=.o)
BONUS_OBJS	= $(BONUS_SRC:.c=.o)
NAME 		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFTPRINTF	= ./ft_printf/libftprintf.a
LFLAGS		= -Lft_printf
LIBS		= $(LIBFTPRINTF)

all: $(LIBFTPRINTF) $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS) $(LIBS)

$(LIBFTPRINTF):
	$(MAKE) -C ./ft_printf all 

bonus:  $(BONUS_OBJS) $(LIBFTPRINTF)
	rm -f pipex
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME) $(LFLAGS) $(LIBS)

fclean: clean
	make -C ./ft_printf fclean
	rm -rf $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)
	make -C ./ft_printf clean

re: fclean all

.PHONY: all clean fclean re bonus