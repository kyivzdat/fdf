#include "fdf.h"

static void	add_list(t_all *all, t_point *point, int x)
{
	t_lst	*list;
	t_lst	*new;

	list = all->list;
	while (list->next)
		list = list->next;
	new = (t_lst *)malloc(sizeof(t_lst));
	list->next = new;
	new->lenx = x;
	new->next = NULL;
	new->prev = list;
	new->point = point;
	new->leny = 0;
}

int	get_data(t_all *all, char *line, int y, int len)
{
	int	i;
	int	x;
	int	z;
	int color;
	t_point	*point;

	i = 0;
	x = 0;
	point = NULL;
	while (i < len && line[i])
	{
		z = ft_atoi(&line[i]);
		i += ft_intlen((ssize_t)z);
		// printf("line[i] = !%c!\n", line[i]);
		if (line[i] == ',')
		{
			i++;
			if (line[i] != '0' || line[i + 1] != 'x')
				return (1);
			while (line[i] != ' ')
				i++;
		}
		if (!point)
			point = point_init(y, z);
		else
			point_add(point, y, z);
		x++;
		while (line[i] == ' ')
			i++;
	}
	if (!all->list)
	{
		all->list = (t_lst *)malloc(sizeof(t_lst));
		all->list->next = NULL;
		all->list->prev = NULL;
		all->list->point = point;
		all->list->lenx = x;
	}
	else
		add_list(all, point, x);
	return (0);
}

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
		// printf("%s\n", line);
		len = ft_strlen(line);
		if (len == 0)
		{
			free(line);
			return (1);
		}
		get_data(all, line, y, len);
		free(line);
		y++;
	}
	if (all->list)
		all->list->leny = y;
	return (0);
}
