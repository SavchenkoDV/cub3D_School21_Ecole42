/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_five.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:34:48 by buthor            #+#    #+#             */
/*   Updated: 2021/04/11 19:35:51 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	tern_z(int nbr, int ret, int elret)
{
	if (nbr < 3)
		return (ret);
	else
		return (elret);
}

int	x_size_map_norm(int fl, int check_read, int fd)
{
	int		size_x;
	int		x;
	char	sym;

	x = 0;
	size_x = 0;
	while (fl == 0 && check_read > 0)
	{
		check_read = read(fd, &sym, 1);
		if (check_read < 1)
			break ;
		size_x++;
		if (size_x > x)
			x = size_x;
		if (sym == '\n')
			size_x = 0;
	}
	return (x);
}

int	x_size_map(char *map_addres, int fl)
{
	int		fd;
	int		x;
	int		check_read;
	char	sym;

	fd = open(map_addres, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (fl > 0)
	{
		check_read = read(fd, &sym, 1);
		if (check_read < 1)
			break ;
		if (sym == '\n')
			fl--;
	}
	x = x_size_map_norm(fl, check_read, fd);
	close(fd);
	if (check_read < 0)
		return (-2);
	return (tern_z(x, -3, x));
}

void	fill_map_with_spaces(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->y_map)
	{
		while (x < data->x_map)
		{
			data->map[y][x] = ' ';
			x++;
		}
		x = 0;
		y++;
	}
}
