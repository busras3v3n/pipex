# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: busseven <busras3v3n@proton.me>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 10:55:22 by busseven          #+#    #+#              #
#    Updated: 2024/11/09 17:14:07 by busseven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC 		= ft_printf.c ft_print_char.c ft_print_str.c ft_print_nbr.c ft_print_hex.c ft_print_ptr.c ft_print_unbr.c ft_print_percent.c
OBJS 		= $(SRC:.c=.o)

NAME 		= libftprintf.a
LIBFT 		= ./libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	cp libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

$(LIBFT):
	make -C ./libft all 

%.o: %.c
	cc -c -Wall -Wextra -Werror $< -o $@ 

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)	

clean:
	rm -f $(OBJS)
	make -C ./libft clean

re: fclean all

.PHONY: all clean fclean re