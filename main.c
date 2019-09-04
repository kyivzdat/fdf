#include "fdf.h"
#include <stdbool.h> 

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

int			noIsoCoord(t_all *all, int n, int x)
{
	if (x)
		return (all->gnrl.midx + all->gnrl.scale * n);
	else
		return (all->gnrl.midy + all->gnrl.scale * n);

}


void	noIsoExtrPoints(t_all *all)
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

void	getExtremePoints(t_all *all, t_lst *list)
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


int	key_hook(int key, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (key == 53)
		exit(1);
	else if (key == 18)
	{
		all->gnrl.proection = 0;
		initGparam(all);
	}
	else if (key == 19)
	{
		all->gnrl.proection = 1;
		initGparam(all);
	}

	if (key == 124)
	{
		if ((coord_x(all, all->gnrl.maxPointX->x, all->gnrl.maxPointX->y) + 10 < 1000 && all->gnrl.proection == 1) || 
		(noIsoCoord(all, all->gnrl.maxPointX->x, 1) + 10 < 1000 && all->gnrl.proection == 0))
			all->gnrl.midx += 10;
	}
	else if (key == 123)
	{
		if ((coord_x(all, all->gnrl.minPointX->x, all->gnrl.minPointX->y) - 10 > 0 && all->gnrl.proection == 1) || 
		(noIsoCoord(all, all->gnrl.minPointX->x, 1) - 10 > 0 && all->gnrl.proection == 0))
			all->gnrl.midx -= 10;
	}
	else if (key == 126)
	{
		if ((coord_y(all, all->gnrl.minPointY->x, all->gnrl.minPointY->y, all->gnrl.minPointY->z) - 10 > 0
		&& all->gnrl.proection == 1) || (noIsoCoord(all, all->gnrl.minPointY->y, 0) - 10 > 0 && all->gnrl.proection == 0))
			all->gnrl.midy -= 10;
	}
	else if (key == 125)
	{
		if ((coord_y(all, all->gnrl.maxPointY->x, all->gnrl.maxPointY->y, all->gnrl.maxPointY->z) + 10 < 1000
		&& all->gnrl.proection == 1) || (noIsoCoord(all, all->gnrl.maxPointY->y, 0) + 10 < 1000 && all->gnrl.proection == 0))
			all->gnrl.midy += 10;
	}
	else if (key == 69 || key == 24)
	{
		if ((coord_x(all, all->gnrl.maxPointX->x, all->gnrl.maxPointX->y) + 25 < 1000 &&
		coord_x(all, all->gnrl.minPointX->x, all->gnrl.minPointX->y) - 25 > 0 &&
		coord_y(all, all->gnrl.minPointY->x, all->gnrl.minPointY->y, all->gnrl.minPointY->z) - 25 > 0 &&
		coord_y(all, all->gnrl.maxPointY->x, all->gnrl.maxPointY->y, all->gnrl.maxPointY->z) + 25 < 1000 &&
		all->gnrl.proection == 1) ||
		(noIsoCoord(all, all->gnrl.maxPointX->x, 1) + 40 < 1000 &&
		noIsoCoord(all, all->gnrl.maxPointY->y, 0) + 40 < 1000 && all->gnrl.proection == 0))
			all->gnrl.scale += 2;
	}
	else if (key == 78 || key == 27)
	{
		if (all->gnrl.scale - 2 > 0 && ((coord_x(all, all->gnrl.maxPointX->x, all->gnrl.maxPointX->y) - 25 > 0 &&
		coord_x(all, all->gnrl.minPointX->x, all->gnrl.minPointX->y) + 25 < 1000 &&
		coord_y(all, all->gnrl.minPointY->x, all->gnrl.minPointY->y, all->gnrl.minPointY->z) + 25 < 1000 &&
		coord_y(all, all->gnrl.maxPointY->x, all->gnrl.maxPointY->y, all->gnrl.maxPointY->z) - 25 > 0 &&
		all->gnrl.proection == 1) || all->gnrl.proection == 0)) 
			all->gnrl.scale -= 2;
	}

	draw(all);
	return (0);
}

int closeWnd(void *param)
{
    (void)param;
    exit(0);
}

int		main(int argc, char **argv)
{
	t_all	all;
	t_general gnrl;

	all.gnrl = gnrl;
	all.gnrl.winSize_x = 1000;
	all.gnrl.winSize_y = 1000;
	all.mlx_ptr = mlx_init();
	all.win_ptr = mlx_new_window(all.mlx_ptr, all.gnrl.winSize_x, all.gnrl.winSize_y, "qwe");
	all.list = NULL;
	all.gnrl.midx = 300;
	all.gnrl.midy = 150;
	all.gnrl.proection = 1;

	int	test = 0xFE;
	printf("test = %d\n", test);
	if (argc == 2)
	{
		if (parse_map(&all, argv[1]))
		{
			write(1, "ERROR\n", 6);
			return (0);
		}
		initGparam(&all);
		// list_print(&all);
		draw(&all);
		mlx_hook(all.win_ptr, 2, 0, key_hook, (void *)&all);
		mlx_hook(all.win_ptr, 17, 0, closeWnd, (void *)&all);
	}

	mlx_loop(all.mlx_ptr);
	return (0);
}
