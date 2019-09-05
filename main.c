/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpalamar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:36:49 by vpalamar          #+#    #+#             */
/*   Updated: 2019/09/05 16:36:50 by vpalamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		parse_map(t_all *all, char *file)
{
	int		fd;
	char	*line;
	int		y;
	int		len;

	fd = open(file, O_RDONLY);
	line = NULL;
	y = 0;
	while (get_next_line(fd, &line))
	{
		len = ft_strlen(line);
		if (len == 0 || get_data(all, line, y, len))
		{
			free(line);
			return (1);
		}
		free(line);
		y++;
	}
	free(line);
	if (all->list)
		all->list->leny = y;
	return (0);
}

int		close_wnd(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	free_list(all);
	exit(0);
}

int		init_start_param(t_all *all)
{
	if (WIN_LENGTH < 0 || WIN_HIGHT < 0)
		return (1);
	all->gnrl.winSize_x = WIN_LENGTH;
	all->gnrl.winSize_y = WIN_HIGHT;
	all->mlx_ptr = mlx_init();
	all->win_ptr =
	mlx_new_window(all->mlx_ptr,
	all->gnrl.winSize_x, all->gnrl.winSize_y, "fdf");
	all->list = NULL;
	all->gnrl.proection = 1;
	all->gnrl.color = CLR_WHITE;
	all->gnrl.height = 1;
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	all;

	if (init_start_param(&all))
	{
		write(1, "ERROR\n", 6);
		return (0);
	}
	if (argc == 2)
	{
		if (parse_map(&all, argv[1]))
		{
			write(1, "ERROR\n", 6);
			free_list(&all);
			return (0);
		}
		init_g_param(&all);
		draw(&all);
		mlx_hook(all.win_ptr, 2, 0, key_hook, (void *)&all);
		mlx_hook(all.win_ptr, 17, 0, close_wnd, (void *)&all);
	}
	mlx_loop(all.mlx_ptr);
	return (0);
}
