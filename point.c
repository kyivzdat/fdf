#include "fdf.h"

t_point	*point_init(int y, int z)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	point->x = 0;
	point->y = y;
	point->z = z;
	point->next = NULL;
	point->prev = NULL;
	return (point);
}

void	point_add(t_point *point, int y, int z)
{
	t_point	*new;

	new = (t_point *)malloc(sizeof(t_point));
	while (point->next)
		point = point->next;
	new->x = point->x + 1;
	new->y = y;
	new->z = z;
	point->next = new;
	new->prev = point;
	new->next = NULL;
}

void	list_print(t_all *all)
{
	t_lst	*list;
	t_point	*point;

	list = all->list;
	while (list)
	{
		point = list->point;
		printf("_______________________\n");
		while (point)
		{
			printf("x = %d, y = %d, z = %d\n", point->x, point->y, point->z);
			if (point->next && point->y != point->next->y)
				printf("\n");
			point = point->next;
		}
		list = list->next;
	}
}

void	point_cur_print(t_point *point)
{
	printf("x = %d, y = %d, z = %d\n", point->x, point->y, point->z);
}
