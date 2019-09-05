# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpalamar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 17:35:54 by vpalamar          #+#    #+#              #
#    Updated: 2019/09/05 17:35:58 by vpalamar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBDIR = ./libft

LIB = $(LIBDIR)/libft.a

SRC :=	main.c \
			draw_line.c \
			get_data.c \
			point_list.c \
			init_g_param.c \
			def_coordinate.c \
			hook.c \

O_FILES := $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(O_FILES)
	$(MAKE) -C $(LIBDIR)
	gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit $(SRC) $(LIB) -o $(NAME)

%.o: %.c filler.h
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(O_FILES)
	$(MAKE) clean -C $(LIBDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBDIR)
