#include "fdf.h"

int  coord_x(t_all *all, int x, int y)
{
	return ((int)(all->gnrl.midx + (float)(all->gnrl.scale * (x - y) * cos(0.523599))));
}

int  coord_y(t_all *all, int x, int y, int z)
{
	return ((int)(all->gnrl.midy + (float)((-(z) * all->gnrl.scale / 2)) + (float)(all->gnrl.scale * (x + y) * sin(0.523599))));
}


int		noIsoCoord(t_all *all, int n, int x)
{
	if (x)
		return (all->gnrl.midx + all->gnrl.scale * n);
	else
		return (all->gnrl.midy + all->gnrl.scale * n);

}

void	isoDraw(t_all *all, t_point *p1, t_point *p2, t_draw *draw)
{
	draw->x0 = coord_x(all, p1->x, p1->y);
	draw->y0 = coord_y(all, p1->x, p1->y, p1->z);
	draw->x1 = coord_x(all, p2->x, p2->y);
	draw->y1 = coord_y(all, p2->x, p2->y, p2->z);
}

void	noIsoDraw(t_all *all, t_point *p1, t_point *p2, t_draw *draw)
{
	draw->x0 = all->gnrl.midx + p1->x * all->gnrl.scale;
	draw->y0 = all->gnrl.midy + p1->y * all->gnrl.scale;
	draw->x1 = all->gnrl.midx + p2->x * all->gnrl.scale;
	draw->y1 = all->gnrl.midy + p2->y * all->gnrl.scale;
}
