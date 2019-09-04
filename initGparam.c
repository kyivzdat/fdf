#include "fdf.h"

static void	initMid(t_all *all)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;

	x1 = coord_x(all, all->gnrl.maxPointX->x, all->gnrl.maxPointX->y);
	x2 = coord_x(all, all->gnrl.minPointX->x, all->gnrl.minPointX->y);
	all->gnrl.midx = (all->gnrl.winSize_x - x1 - x2) / 2;
	if (all->gnrl.proection == 0)
		all->gnrl.midx = (all->gnrl.winSize_x - all->list->lenx * all->gnrl.scale) / 2;
	y1 = coord_y(all, all->gnrl.maxPointY->x, all->gnrl.maxPointY->y, all->gnrl.maxPointY->z);
	y2 = coord_y(all, all->gnrl.minPointY->x, all->gnrl.minPointY->y, all->gnrl.minPointY->z);
	all->gnrl.midy = (all->gnrl.winSize_y - y2 - y1) / 2;
	if (all->gnrl.proection == 0)
		all->gnrl.midy = (all->gnrl.winSize_y - all->list->leny * all->gnrl.scale) / 2;
}


static void	initGscale(t_all *all)
{
	int	y1;
	int	y2;

	y1 = coord_y(all, all->gnrl.maxPointY->x, all->gnrl.maxPointY->y, all->gnrl.maxPointY->z);
	y2 = coord_y(all, all->gnrl.minPointY->x, all->gnrl.minPointY->y, all->gnrl.minPointY->z);
	all->gnrl.scale = (all->gnrl.winSize_x / 2) / (y1 - y2);
	if (all->gnrl.proection == 0)
		all->gnrl.scale = all->gnrl.winSize_x / 2 / all->list->lenx;
}

static void	noIsoExtrPoints(t_all *all)
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
			tmp = noIsoCoord(all, p->x, 1);
			point = noIsoCoord(all, all->gnrl.maxPointX->x, 1);
			all->gnrl.maxPointX = (point < tmp) ? p : all->gnrl.maxPointX;
			point = noIsoCoord(all, all->gnrl.minPointX->x, 1);
			all->gnrl.minPointX = (point > tmp) ? p : all->gnrl.minPointX;
			tmp = noIsoCoord(all, p->y, 0);
			point = noIsoCoord(all, all->gnrl.maxPointY->y, 0);
			all->gnrl.maxPointY = (point < tmp) ? p : all->gnrl.maxPointY;
			point = noIsoCoord(all, all->gnrl.minPointY->y, 0);
			all->gnrl.minPointY = (point > tmp) ? p : all->gnrl.minPointY;
			p = p->next;
		}
		list = list->next;
	}
}

static void	getExtremePoints(t_all *all, t_lst *list)
{
	t_point	*p;
	int		tmp;
	int		point;

	if (all->gnrl.proection == 0)
		return (noIsoExtrPoints(all));
	while (list)
	{
		p = list->point;
		while (p)
		{
			tmp = coord_x(all, p->x, p->y);
			point = coord_x(all, all->gnrl.maxPointX->x, all->gnrl.maxPointX->y);
			all->gnrl.maxPointX = (point < tmp) ? p : all->gnrl.maxPointX;
			point = coord_x(all, all->gnrl.minPointX->x, all->gnrl.minPointX->y);
			all->gnrl.minPointX = (point > tmp) ? p : all->gnrl.minPointX;
			tmp = coord_y(all, p->x, p->y, p->z);
			point = coord_y(all, all->gnrl.maxPointY->x, all->gnrl.maxPointY->y, all->gnrl.maxPointY->z);
			all->gnrl.maxPointY = (point < tmp) ? p : all->gnrl.maxPointY;
			point = coord_y(all, all->gnrl.minPointY->x, all->gnrl.minPointY->y, all->gnrl.minPointY->z);
			all->gnrl.minPointY = (point > tmp) ? p : all->gnrl.minPointY;
			p = p->next;
		}
		list = list->next;
	}
}

void	initGparam(t_all *all)
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
	getExtremePoints(all, list);
	initGscale(all);
	initMid(all);
}
