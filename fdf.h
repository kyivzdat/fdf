#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include "libft/libft.h"
# include "mlx.h"
# include "math.h"

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

# define WIN_LENGTH 1000
# define WIN_HIGHT 1000

# define CLR_WHITE		0xffffff
# define CLR_RED		0xff0000
# define CLR_BLUE		0x0000ff
# define CLR_GREEN		0x00ff00
# define CLR_CYAN		0x00ffff
# define CLR_PURPLE		0xb300b3
# define CLR_YELLOW		0xffff33
# define CLR_TIFFANY	0x00b3b3
# define CLR_CHOCOLATE	0x805500
# define CLR_TEA_GREEN	0xccffcc




typedef struct  s_point
{
	int				x;
	int				y;
	int				z;
	struct s_point  *next;
	struct s_point  *prev;
}				t_point;

typedef struct	s_lst
{
	int				lenx;
	int				leny;
	struct s_point	*point;
	struct s_lst	*next;
	struct s_lst	*prev;
}				t_lst;

typedef struct	s_draw
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		a;
	int		b;
	int		sign;
	int		signa;
	int		signb;
}				t_draw;

typedef	struct	s_general
{
	int			midx;
	int			midy;
	int			scale;
	int			proection;
	int			color;
	int			winSize_x;
	int			winSize_y;
	t_point		*maxPointX;
	t_point		*maxPointY;
	t_point		*minPointX;
	t_point		*minPointY;
}				t_general;


typedef struct	s_all
{
	t_general	gnrl;
	t_draw		draw;
	t_lst		*list;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_all;

t_point	*point_init(int y, int z);
void	point_add(t_point *point, int y, int z);
void	list_print(t_all *all);
void	point_cur_print(t_point *point);

int		get_data(t_all *all, char *line, int y, int len);
int		parse_map(t_all *all, char *file);

void	init_g_param(t_all *all);

void	draw(t_all *all);
void	draw_line(t_all *all, t_point *p1, t_point *p2);

int		coord_x(t_all *all, int x, int y);
int		coord_y(t_all *all, int x, int y, int z);
int		no_iso_coord(t_all *all, int n, int x);
void	iso_draw(t_all *all, t_point *p1, t_point *p2, t_draw *draw);
void	no_iso_draw(t_all *all, t_point *p1, t_point *p2, t_draw *draw);

#endif
