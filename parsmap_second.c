/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsmap_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:26:49 by buthor            #+#    #+#             */
/*   Updated: 2021/04/10 21:11:37 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	fill_map_with_data(t_data *data, int fd, int fl, int check_read)
{
	int		x;
	int		y;
	char	sym;

	y = 0;
	x = 1;
	while ((fl == 0 && check_read > 0))
	{
		check_read = read(fd, &sym, 1);
		if (check_read <= 0)
			break ;
		if (sym == '\n')
		{
			data->map[y][x] = ' ';
			y++;
			x = 1;
		}
		else
		{
			data->map[y][x] = sym;
			x++;
		}
	}
	return (check_read);
}

int	fill_map(char *map_addres, t_data *data, int fl)
{
	int		check_read;
	char	sym;
	int		fd;

	fill_map_with_spaces(data);
	fd = open(map_addres, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (fl > 0)
	{
		check_read = read(fd, &sym, 1);
		if (check_read <= 0)
			break ;
		if (sym == '\n')
			fl--;
	}
	check_read = fill_map_with_data(data, fd, fl, check_read);
	close(fd);
	if (check_read < 0)
		return (-2);
	return (0);
}

int	map_space_check(t_data *data, int x, int y)
{
	if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' ' ||
		data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	tern_f(int nbr, int ret, int elret)
{
	if (nbr == 1)
		return (ret);
	else
		return (elret);
}

int	check_map_body(t_data *data, int x, int y, int pers)
{
	while (++y < data->y_map)
	{
		while (x < data->x_map)
		{
			if (dvs_strchr(SYM0, data->map[y][x]) == 0)
			{
				if (dvs_strchr(SYM1, data->map[y][x]) == 0)
				{
					pers++;
					if (map_space_check(data, x, y) == 1)
						return (1);
					data->y_pers = y + 0.5;
					data->x_pers = x + 0.5;
				}
				if (dvs_strchr(SYM2, data->map[y][x]) == 0)
					if (map_space_check(data, x, y) != 0)
						return (1);
			}
			else
				return (1);
			x++;
		}
		x = 1;
	}
	return (tern_f(pers, 0, 1));
}
