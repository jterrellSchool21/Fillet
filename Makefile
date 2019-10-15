# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterrell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 13:39:13 by jterrell          #+#    #+#              #
#    Updated: 2019/10/14 18:31:19 by jterrell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=fillit

all: $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@gcc -Wall -Wextra -Werror -I libft/ -o read_map.o -c read_map.c
	@gcc -Wall -Wextra -Werror -I libft/ -o main.o -c main.c
	@gcc -Wall -Wextra -Werror -I libft/ -o ft_new_all.o -c ft_new_all.c
	@gcc -Wall -Wextra -Werror -I libft/ -o solver.o -c solver.c
	@gcc -o $(NAME) ft_new_all.o solver.o read_map.o main.o -I libft/ -L libft/ -lft

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
