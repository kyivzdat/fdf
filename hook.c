/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpalamar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:51:03 by vpalamar          #+#    #+#             */
/*   Updated: 2019/09/05 15:51:06 by vpalamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	key_hook_wasd2(int key, t_all *all)
{
	if (key == 126)
	{
		if ((coord_y(all, all->gnrl.maxPointY->x,
		all->gnrl.maxPointY->y, all->gnrl.maxPointY->z) > 0 &&
		all->gnrl.proection == 1) || (all->gnrl.proection == 0 &&
		(no_iso_coord(all, all->gnrl.maxPointY->y, 0) > 0)))
			all->gnrl.midy -= 10;
	}
	else if (key == 125)
	{
		if ((coord_y(all, all->gnrl.minPointY->x,
		all->gnrl.minPointY->y, all->gnrl.minPointY->z) < all->gnrl.winSize_y
		&& all->gnrl.proection == 1) || (all->gnrl.proection == 0 &&
		(no_iso_coord(all, all->gnrl.minPointY->y, 0) < all->gnrl.winSize_y)))
			all->gnrl.midy += 10;
	}
}

static void	key_hook_wasd(int key, t_all *all)
{
	if (key == 124)
	{
		if ((coord_x(all, all->gnrl.minPointX->x,
		all->gnrl.minPointX->y) < all->gnrl.winSize_x
		&& all->gnrl.proection == 1) || (all->gnrl.proection == 0 &&
		(no_iso_coord(all, all->gnrl.minPointX->x, 1) < all->gnrl.winSize_x)))
			all->gnrl.midx += 10;
	}
	else if (key == 123)
	{
		if ((coord_x(all, all->gnrl.maxPointX->x,
		all->gnrl.maxPointX->y) > 0
		&& all->gnrl.proection == 1) || (all->gnrl.proection == 0 &&
		(no_iso_coord(all, all->gnrl.maxPointX->x, 1) > 0)))
			all->gnrl.midx -= 10;
	}
	else
		key_hook_wasd2(key, all);
}

static void	key_hook_color(int key, t_all *all)
{
	if (key == 82)
		all->gnrl.color = CLR_WHITE;
	else if (key == 83)
		all->gnrl.color = CLR_RED;
	else if (key == 84)
		all->gnrl.color = CLR_BLUE;
	else if (key == 85)
		all->gnrl.color = CLR_GREEN;
	else if (key == 86)
		all->gnrl.color = CLR_CYAN;
	else if (key == 87)
		all->gnrl.color = CLR_PURPLE;
	else if (key == 88)
		all->gnrl.color = CLR_YELLOW;
	else if (key == 89)
		all->gnrl.color = CLR_TIFFANY;
	else if (key == 91)
		all->gnrl.color = CLR_CHOCOLATE;
	else if (key == 92)
		all->gnrl.color = CLR_TEA_GREEN;
}

void		key_hook_proection(int key, t_all *all)
{
	if (key == 18)
	{
		all->gnrl.proection = 0;
		init_g_param(all);
	}
	else if (key == 19)
	{
		all->gnrl.proection = 1;
		init_g_param(all);
	}
}

int			key_hook(int key, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (key == 53)
	{
		free_list(all);
		exit(1);
	}
	else if (key == 18 || key == 19)
		key_hook_proection(key, all);
	else if (key == 69)
		all->gnrl.scale += 2;
	else if (key == 78)
		all->gnrl.scale -= 2;
	else if (key == 24)
		all->gnrl.height += 1;
	else if (key == 27)
		all->gnrl.height -= 1;
	else if (key == 123 || key == 124 || key == 125 || key == 126)
		key_hook_wasd(key, all);
	else if (key == 65 || (key >= 82 && key <= 89) || key == 91 || key == 92)
		key_hook_color(key, all);
	draw(all);
	return (0);
}
