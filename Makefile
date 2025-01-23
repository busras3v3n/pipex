# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: busseven <busseven@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 09:59:40 by busseven          #+#    #+#              #
#    Updated: 2025/01/23 14:21:15 by busseven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC 		= 	./pipex.c ./utils.c ./errors.c
OBJS 		= $(SRC:.c=.o)

NAME 		= pipex.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFTPRINTF	= ft_printf/libftprintf.a

all: $(LIBFTPRINTF) $(NAME)

$(NAME): $(LIBFTPRINTF) $(OBJS)
	cp $(LIBFTPRINTF) $(NAME)
	ar -rcs $(NAME) $(OBJS)

$(LIBFTPRINTF):
	$(MAKE) -C ./ft_printf all 

fclean: clean
	make -C ./ft_printf fclean
	rm -rf $(NAME)

clean:
	rm -f $(OBJS)
	make -C ./ft_printf clean

re: fclean all

.PHONY: all clean fclean re