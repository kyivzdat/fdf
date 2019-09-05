#include "fdf.h"

static void	draw_line1(t_all *all, t_draw *draw)
{
	int x;
	int	y;
	int f;

	x = draw->x0;
	y = draw->y0;
	f = 0;
	while (x != draw->x1 || y != draw->y1)
	{
		f += draw->a * draw->signa;
		if (f > 0)
		{
			f -= draw->b * draw->signb;
			y += draw->signa;
		}
		x -= draw->signb;
		mlx_pixel_put(all->mlx_ptr, all->win_ptr, x, y, all->gnrl.color);
	} 
}

static void	draw_line2(t_all *all, t_draw *draw)
{
	int x;
	int	y;
	int f;

	x = draw->x0;
	y = draw->y0;
	f = 0;
	while (x != draw->x1 || y != draw->y1)
	{
		f += draw->b * draw->signb;
		if (f > 0)
		{
			f -= draw->a * draw->signa;
			x -= draw->signb;
		}
		y += draw->signa;
		mlx_pixel_put(all->mlx_ptr, all->win_ptr, x, y, all->gnrl.color);
	}
}

void	draw_line(t_all *all, t_point *p1, t_point *p2)
{
	t_draw	draw;

	// mlx_clear_window(all->mlx_ptr, all->win_ptr);
	if (all->gnrl.proection == 0)
		no_iso_draw(all, p1, p2, &draw);
	else if (all->gnrl.proection == 1)
		iso_draw(all, p1, p2, &draw);
	draw.a = draw.y1 - draw.y0;
	draw.b = draw.x0 - draw.x1;
	draw.sign = (abs(draw.a) > abs(draw.b)) ? 1 : -1;
	draw.signa = (draw.a < 0) ? -1 : 1;
	draw.signb = (draw.b < 0) ? -1 : 1;
	mlx_pixel_put(all->mlx_ptr, all->win_ptr, draw.x0, draw.y0, all->gnrl.color);
	if (draw.sign == -1) 
		draw_line1(all, &draw);
	else
		draw_line2(all, &draw);
}

t_point	*find_upper_point(t_lst *list, int x)
{
	t_point	*find;
	int		i;

	find = list->prev->point;
	i = 0;
	while (find->next && i < x)
	{
		i++;
		find = find->next;
	}
	if (i != x)
		return (NULL);
	return (find);
}

void	draw(t_all *all)
{
	t_lst	*list;
	t_point	*point;
	t_point	*find;	

	list = all->list;
	mlx_clear_window(all->mlx_ptr, all->win_ptr);
	while (list)
	{
		point = list->point;
		while (point)
		{
			if (point->next)
			{
				draw_line(all, point, point->next);
			}
			if (list->prev)
			{
				(find = find_upper_point(list, point->x)) ? draw_line(all, find, point) : 1;
			}
			point = point->next;
		}
		list = list->next;
	}
}
