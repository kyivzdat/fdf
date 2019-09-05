/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpalamar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:56:29 by vpalamar          #+#    #+#             */
/*   Updated: 2019/09/05 15:56:31 by vpalamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			point_free(t_point *point)
{
	t_point		*free_point;

	while (point)
	{
		free_point = point;
		point = point->next;
		free(free_point);
	}
	return (1);
}

t_point		*point_init(int y, int z)
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

void		point_add(t_point *point, int y, int z)
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

int			add_list(t_all *all, t_point *point, int x)
{
	t_lst	*list;
	t_lst	*new;

	list = all->list;
	while (list->next)
		list = list->next;
	if (list->lenx != x)
		return (1);
	new = (t_lst *)malloc(sizeof(t_lst));
	list->next = new;
	new->lenx = x;
	new->next = NULL;
	new->prev = list;
	new->point = point;
	new->leny = 0;
	return (0);
}

void		free_list(t_all *all)
{
	t_point	*p;
	t_point	*free_p;
	t_lst	*list;
	t_lst	*free_list;

	list = all->list;
	while (list)
	{
		p = list->point;
		while (p)
		{
			free_p = p;
			p = p->next;
			free(free_p);
		}
		free_list = list;
		list = list->next;
		free(free_list);
	}
}
