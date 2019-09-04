SRC :=	main.c \
			draw_line.c \
			parse.c \
			point.c \
			initGparam.c \
			def_coordinate.c \

all:
	gcc -lmlx -framework OpenGL -framework AppKit $(SRC) libft/libft.a

flags:
	gcc -Wall -Wextra -Werror -lmlx-framework OpenGL -framework AppKit $(SRC)
