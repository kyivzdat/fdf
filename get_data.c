/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpalamar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:34:58 by vpalamar          #+#    #+#             */
/*   Updated: 2019/09/05 16:35:00 by vpalamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		check_hex(char *line)
{
	int	i;

	i = 0;
	if (line[i] != '0' || line[i + 1] != 'x')
		return (1);
	i += 2;
	while (line[i] && line[i] != ' ')
	{
		if (!(line[i] >= '0' && line[i] <= '9') &&
		(!(line[i] >= 'a' && line[i] <= 'f')) &&
		(!(line[i] >= 'A' && line[i] <= 'F')))
			return (1);
		i++;
	}
	if ((i - 2) > 6)
		return (1);
	return (0);
}

static int		list_init(t_all *all, int x, t_point *point)
{
	if (!all->list)
	{
		all->list = (t_lst *)malloc(sizeof(t_lst));
		all->list->next = NULL;
		all->list->prev = NULL;
		all->list->point = point;
		all->list->lenx = x;
	}
	else
	{
		if (add_list(all, point, x))
		{
			point_free(point);
			return (1);
		}
	}
	return (0);
}

static int		check_coma(char *line, int *i, t_point *point, int len)
{
	if (line[*i] == ',')
	{
		if (check_hex(&line[++*i]))
		{
			point_free(point);
			return (-1);
		}
		while (*i < len && line[*i] != ' ')
			(*i)++;
	}
	return (*i);
}

static t_point	*point_start(t_point *point, int y, int z)
{
	if (!point)
		point = point_init(y, z);
	else
		point_add(point, y, z);
	return (point);
}

int				get_data(t_all *all, char *line, int y, int len)
{
	int		i;
	int		x;
	int		z;
	t_point	*point;

	i = 0;
	x = 0;
	point = NULL;
	while (i < len && line[i])
	{
		z = ft_atoi(&line[i]);
		i = (line[i] == '+') ? i + 1 : i;
		i += ft_intlen((ssize_t)z);
		if (check_coma(line, &i, point, len) == -1)
			return (1);
		while (i < len && (line[i] < '0' || line[i] > '9') && line[i] != '-')
			if (line[i++] != ' ' && point_free(point))
				return (1);
		point = point_start(point, y, z);
		x++;
	}
	if (list_init(all, x, point))
		return (1);
	return (0);
}
