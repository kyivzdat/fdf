/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpalamar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:47:00 by vpalamar          #+#    #+#             */
/*   Updated: 2019/09/05 16:47:02 by vpalamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_mid(t_all *all)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;

	x1 = coord_x(all, all->gnrl.maxPointX->x, all->gnrl.maxPointX->y);
	x2 = coord_x(all, all->gnrl.minPointX->x, all->gnrl.minPointX->y);
	all->gnrl.midx = (all->gnrl.winSize_x - x1 - x2) / 2;
	if (all->gnrl.proection == 0)
		all->gnrl.midx = (all->gnrl.winSize_x -
		all->list->lenx * all->gnrl.scale) / 2;
	y1 = coord_y(all, all->gnrl.maxPointY->x,
	all->gnrl.maxPointY->y, all->gnrl.maxPointY->z);
	y2 = coord_y(all, all->gnrl.minPointY->x,
	all->gnrl.minPointY->y, all->gnrl.minPointY->z);
	all->gnrl.midy = (all->gnrl.winSize_y - y2 - y1) / 2;
	if (all->gnrl.proection == 0)
		all->gnrl.midy = (all->gnrl.winSize_y -
		all->list->leny * all->gnrl.scale) / 2;
}

static void	init_g_scale(t_all *all)
{
	int	y1;
	int	y2;
	int	min_value;

	min_value = (all->gnrl.winSize_x < all->gnrl.winSize_y) ?
	all->gnrl.winSize_x : all->gnrl.winSize_y;
	y1 = coord_y(all, all->gnrl.maxPointY->x,
	all->gnrl.maxPointY->y, all->gnrl.maxPointY->z);
	y2 = coord_y(all, all->gnrl.minPointY->x,
	all->gnrl.minPointY->y, all->gnrl.minPointY->z);
	all->gnrl.scale = (min_value / 2) / (y1 - y2);
	if (all->gnrl.proection == 0)
		all->gnrl.scale = all->gnrl.winSize_x / 2 / all->list->lenx;
}

static void	no_iso_extr_points(t_all *all)
{
	t_lst	*list;
	t_point	*p;
	int		tmp;
	int		point;

	list = all->list;
	while (list)
	{
		p = list->point;
		while (p)
		{
			tmp = no_iso_coord(all, p->x, 1);
			point = no_iso_coord(all, all->gnrl.maxPointX->x, 1);
			all->gnrl.maxPointX = (point < tmp) ? p : all->gnrl.maxPointX;
			point = no_iso_coord(all, all->gnrl.minPointX->x, 1);
			all->gnrl.minPointX = (point > tmp) ? p : all->gnrl.minPointX;
			tmp = no_iso_coord(all, p->y, 0);
			point = no_iso_coord(all, all->gnrl.maxPointY->y, 0);
			all->gnrl.maxPointY = (point < tmp) ? p : all->gnrl.maxPointY;
			point = no_iso_coord(all, all->gnrl.minPointY->y, 0);
			all->gnrl.minPointY = (point > tmp) ? p : all->gnrl.minPointY;
			p = p->next;
		}
		list = list->next;
	}
}

static void	get_extreme_points(t_all *a, t_lst *list, int maxy, int miny)
{
	t_point	*p;
	int		tmp;
	int		c;

	if (a->gnrl.proection == 0)
		return (no_iso_extr_points(a));
	while (list)
	{
		p = list->point;
		while (p)
		{
			tmp = coord_x(a, p->x, p->y);
			c = coord_x(a, a->gnrl.maxPointX->x, a->gnrl.maxPointX->y);
			a->gnrl.maxPointX = (c < tmp) ? p : a->gnrl.maxPointX;
			c = coord_x(a, a->gnrl.minPointX->x, a->gnrl.minPointX->y);
			a->gnrl.minPointX = (c > tmp) ? p : a->gnrl.minPointX;
			tmp = coord_y(a, p->x, p->y, p->z);
			c = coord_y(a, a->gnrl.maxPointY->x, maxy, a->gnrl.maxPointY->z);
			a->gnrl.maxPointY = (c < tmp) ? p : a->gnrl.maxPointY;
			c = coord_y(a, a->gnrl.minPointY->x, miny, a->gnrl.minPointY->z);
			a->gnrl.minPointY = (c > tmp) ? p : a->gnrl.minPointY;
			p = p->next;
		}
		list = list->next;
	}
}

void		init_g_param(t_all *all)
{
	t_lst	*list;

	list = all->list;
	all->gnrl.midx = 0;
	all->gnrl.midy = 0;
	all->gnrl.scale = 1;
	all->gnrl.maxPointX = list->point;
	all->gnrl.maxPointY = list->point;
	all->gnrl.minPointX = list->point;
	all->gnrl.minPointY = list->point;
	get_extreme_points(all, list,
	all->gnrl.maxPointY->y, all->gnrl.minPointY->y);
	init_g_scale(all);
	init_mid(all);
}
