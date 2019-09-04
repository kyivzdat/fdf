#include "fdf.h"
#include <stdbool.h> 

int	key_hook(int key, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (key == 53)
		exit(1);
	else if (key == 18)
	{
		all->gnrl.proection = 0;
		init_g_param(all);
	}
	else if (key == 19)
	{
		all->gnrl.proection = 1;
		init_g_param(all);
	}

	if (key == 124)
	{
		if ((coord_x(all, all->gnrl.maxPointX->x, all->gnrl.maxPointX->y) + 10 < 1000 && all->gnrl.proection == 1) || 
		(no_iso_coord(all, all->gnrl.maxPointX->x, 1) + 10 < 1000 && all->gnrl.proection == 0))
			all->gnrl.midx += 10;
	}
	else if (key == 123)
	{
		if ((coord_x(all, all->gnrl.minPointX->x, all->gnrl.minPointX->y) - 10 > 0 && all->gnrl.proection == 1) || 
		(no_iso_coord(all, all->gnrl.minPointX->x, 1) - 10 > 0 && all->gnrl.proection == 0))
			all->gnrl.midx -= 10;
	}
	else if (key == 126)
	{
		if ((coord_y(all, all->gnrl.minPointY->x, all->gnrl.minPointY->y, all->gnrl.minPointY->z) - 10 > 0
		&& all->gnrl.proection == 1) || (no_iso_coord(all, all->gnrl.minPointY->y, 0) - 10 > 0 && all->gnrl.proection == 0))
			all->gnrl.midy -= 10;
	}
	else if (key == 125)
	{
		if ((coord_y(all, all->gnrl.maxPointY->x, all->gnrl.maxPointY->y, all->gnrl.maxPointY->z) + 10 < 1000
		&& all->gnrl.proection == 1) || (no_iso_coord(all, all->gnrl.maxPointY->y, 0) + 10 < 1000 && all->gnrl.proection == 0))
			all->gnrl.midy += 10;
	}
	else if (key == 69 || key == 24)
	{
		if ((coord_x(all, all->gnrl.maxPointX->x, all->gnrl.maxPointX->y) + 25 < 1000 &&
		coord_x(all, all->gnrl.minPointX->x, all->gnrl.minPointX->y) - 25 > 0 &&
		coord_y(all, all->gnrl.minPointY->x, all->gnrl.minPointY->y, all->gnrl.minPointY->z) - 25 > 0 &&
		coord_y(all, all->gnrl.maxPointY->x, all->gnrl.maxPointY->y, all->gnrl.maxPointY->z) + 25 < 1000 &&
		all->gnrl.proection == 1) ||
		(no_iso_coord(all, all->gnrl.maxPointX->x, 1) + 40 < 1000 &&
		no_iso_coord(all, all->gnrl.maxPointY->y, 0) + 40 < 1000 && all->gnrl.proection == 0))
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
		init_g_param(&all);
		// list_print(&all);
		draw(&all);
		mlx_hook(all.win_ptr, 2, 0, key_hook, (void *)&all);
		mlx_hook(all.win_ptr, 17, 0, closeWnd, (void *)&all);
	}

	mlx_loop(all.mlx_ptr);
	return (0);
}
