/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpalamar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:22:19 by vpalamar          #+#    #+#             */
/*   Updated: 2019/09/05 15:22:21 by vpalamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		draw_line(t_all *all, t_point *p1, t_point *p2)
{
	t_draw	drw;

	if (all->gnrl.proection == 0)
		no_iso_draw(all, p1, p2, &drw);
	else if (all->gnrl.proection == 1)
		iso_draw(all, p1, p2, &drw);
	drw.a = drw.y1 - drw.y0;
	drw.b = drw.x0 - drw.x1;
	drw.sign = (abs(drw.a) > abs(drw.b)) ? 1 : -1;
	drw.signa = (drw.a < 0) ? -1 : 1;
	drw.signb = (drw.b < 0) ? -1 : 1;
	mlx_pixel_put(all->mlx_ptr, all->win_ptr, drw.x0, drw.y0, all->gnrl.color);
	if (drw.sign == -1)
		draw_line1(all, &drw);
	else
		draw_line2(all, &drw);
}

t_point		*find_upper_point(t_lst *list, int x)
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

void		draw(t_all *all)
{
	t_lst	*list;
	t_point	*point;
	t_point	*f;

	list = all->list;
	mlx_clear_window(all->mlx_ptr, all->win_ptr);
	while (list)
	{
		point = list->point;
		while (point)
		{
			if (point->next)
				draw_line(all, point, point->next);
			if (list->prev)
				(f = find_upper_point(list, point->x)) ?
				draw_line(all, f, point) : 1;
			point = point->next;
		}
		list = list->next;
	}
}
