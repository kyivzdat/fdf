#include "fdf.h"


void	get_draw(t_draw *draw)
{
	draw->a = draw->y1 - draw->y0;
	draw->b = draw->x0 - draw->x1;
	draw->sign = (abs(draw->a) > abs(draw->b)) ? 1 : -1;
	draw->signa = (draw->a < 0) ? -1 : 1;
	draw->signb = (draw->b < 0) ? -1 : 1;
}

void	draw_line1(t_all *all, t_draw *draw)
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
		mlx_pixel_put(all->mlx_ptr, all->win_ptr, x, y, 0xe6e6fa);
	} 
}

void	draw_line2(t_all *all, t_draw *draw)
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
		mlx_pixel_put(all->mlx_ptr, all->win_ptr, x, y, 0xe6e6fa);
	}
}

void	draw_line(t_all *all, t_point *p1, t_point *p2)
{
	t_draw	draw;

	// mlx_clear_window(all->mlx_ptr, all->win_ptr);
	if (all->gnrl.proection == 0)
		noIsoDraw(all, p1, p2, &draw);
	else if (all->gnrl.proection == 1)
		isoDraw(all, p1, p2, &draw);
	get_draw(&draw);
	mlx_pixel_put(all->mlx_ptr, all->win_ptr, draw.x0, draw.y0, 0xe6e6fa);
	if (draw.sign == -1) 
		draw_line1(all, &draw);
	else
		draw_line2(all, &draw);
}
