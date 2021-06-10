/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:23:22 by buthor            #+#    #+#             */
/*   Updated: 2021/04/11 19:35:34 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	y_size_map(char *map_addres, int fl, int y, t_data *data)
{
	data->norm.fd = open(map_addres, O_RDONLY);
	if (data->norm.fd < 0)
		return (-1);
	while (fl > 0)
	{
		data->norm.check_read = read(data->norm.fd, &data->norm.sym, 1);
		if (data->norm.check_read < 1)
			break ;
		if (data->norm.sym == '\n')
			fl--;
	}
	while (fl == 0 && data->norm.check_read > 0)
	{
		data->norm.check_read = read(data->norm.fd, &data->norm.sym, 1);
		if (data->norm.check_read < 1)
			break ;
		if (data->norm.sym == '\n')
			y++;
	}
	y++;
	if (data->norm.check_read < 0)
		return (-2);
	close(data->norm.fd);
	return (tern_z(y, -3, y));
}

char	**allocate_map(t_data *data)
{
	char	**map;
	char	*line;
	int		i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (data->y_map + 1));
	if (map == NULL)
		return (NULL);
	map[data->y_map] = NULL;
	while (i < data->y_map)
	{
		line = (char *)malloc (sizeof(char) * (data->x_map + 2));
		if (line == NULL)
		{
			while (i != 0)
				free(map[--i]);
			free(map);
			return (NULL);
		}
		line[data->x_map + 1] = '\0';
		map[i] = line;
		i++;
	}
	data->x_map = data->x_map + 1;
	return (map);
}

int	check_map(t_data *data)
{
	int	x;
	int	y;

	x = 1;
	y = 0;
	while (x < data->x_map)
	{
		if (data->map[y][x] != '1' && data->map[y][x] != ' ')
			return (-3);
		x++;
	}
	x = 1;
	y = data->y_map - 1;
	while (x < data->x_map)
	{
		if (data->map[y][x] != '1' && data->map[y][x] != ' ')
			return (-3);
		x++;
	}
	return (check_map_body(data, 1, 0, 0));
}

void	write_pos_pers(t_data *data, char sym)
{
	if (sym == 'N')
	{
		data->rc.dir_x = 0;
		data->rc.dir_y = -1;
	}
	else if (sym == 'W')
	{
		data->rc.dir_x = -1;
		data->rc.dir_y = 0;
	}
	else if (sym == 'E')
	{
		data->rc.dir_x = 1;
		data->rc.dir_y = 0;
	}
	else if (sym == 'S')
	{
		data->rc.dir_x = 0;
		data->rc.dir_y = 1;
	}
	data->rc.plane_x = data->rc.dir_y * -0.66;
	data->rc.plane_y = data->rc.dir_x * 0.66;
}

void	fill_map_count_sp_and_write_pos_pers(t_data	*data, int i, int j)
{
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = '1';
			else if (data->map[i][j] == 'N' || data->map[i][j] == 'W' ||
			data->map[i][j] == 'S' || data->map[i][j] == 'E')
			{
				write_pos_pers(data, data->map[i][j]);
				data->map[i][j] = '0';
			}
			else if (data->map[i][j] == '2')
				data->count_sp++;
			j++;
		}
		j = 0;
		i++;
	}
}
