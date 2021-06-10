/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:27:02 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 15:44:35 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_screen(t_data *ap, int fd, int res)
{
	int		color;
	int		x;
	int		y;
	int		size_x;

	color = 0;
	x = 0;
	y = ap->header.rh - 1;
	size_x = res;
	while (y >= 0)
	{
		while (x < size_x)
		{
			color = get_color_bmp(ap, x, y);
			write(fd, &color, 3);
			x++;
		}
		y--;
		x = 0;
	}
}

void	make_screenshot(t_data *data, int count, int size)
{
	int				fd;
	unsigned char	buff[54];
	int				tmp;

	tmp = data->header.rw;
	if (data->header.rw % 4)
		tmp = data->header.rw - (data->header.rw % 4);
	size = tmp * data->header.rh + 54;
	fd = open("./screenshot.bmp", O_RDWR | O_CREAT, 0666);
	if (fd < 0)
	{
		dvs_putstr("Error\nDon't create file to screenshot!");
		exit(0);
	}
	while (count < 54)
	{
		buff[count] = (unsigned char)0;
		count++;
	}
	init_head_bmp(buff, size, data, tmp);
	write(fd, buff, 54);
	get_screen(data, fd, tmp);
	close(fd);
	exit(0);
}

void	fast_mlx_pixel_put(t_pixput *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	rotate_pers(int keycode, t_data *data)
{
	if (keycode == 123)
	{
		data->rc.oldir_x = data->rc.dir_x;
		data->rc.dir_x = data->rc.dir_x * cos(-SUD)
			- data->rc.dir_y * sin(-SUD);
		data->rc.dir_y = data->rc.oldir_x * sin(-SUD)
			+ data->rc.dir_y * cos(-SUD);
		data->rc.oldplane_x = data->rc.plane_x;
		data->rc.plane_x = data->rc.plane_x * cos(-SUD)
			- data->rc.plane_y * sin(-SUD);
		data->rc.plane_y = data->rc.oldplane_x * sin(-SUD)
			+ data->rc.plane_y * cos(-SUD);
	}
	if (keycode == 124)
	{
		data->rc.oldir_x = data->rc.dir_x;
		data->rc.dir_x = data->rc.dir_x * cos(SUD) - data->rc.dir_y * sin(SUD);
		data->rc.dir_y = data->rc.oldir_x * sin(SUD)
			+ data->rc.dir_y * cos(SUD);
		data->rc.oldplane_x = data->rc.plane_x;
		data->rc.plane_x = data->rc.plane_x * cos(SUD)
			- data->rc.plane_y * sin(SUD);
		data->rc.plane_y = data->rc.oldplane_x * sin(SUD)
			+ data->rc.plane_y * cos(SUD);
	}
}

void	move_pers_ver(int keycode, t_data *data)
{
	if (keycode == 126 || keycode == 13)
	{
		if (data->map[(int)data->y_pers][(int)(data->x_pers
			+ data->rc.dir_x * TMS)] != '1')
			data->x_pers += data->rc.dir_x * TMS;
		if (data->map[(int)(data->y_pers + data->rc.dir_y
				* TMS)][(int)(data->x_pers)] != '1')
			data->y_pers += data->rc.dir_y * TMS;
	}
	if (keycode == 125 || keycode == 1)
	{
		if (data->map[(int)(data->y_pers)][(int)(data->x_pers
			- data->rc.dir_x * TMS)] != '1')
			data->x_pers -= data->rc.dir_x * TMS;
		if (data->map[(int)(data->y_pers - data->rc.dir_y
				* TMS)][(int)(data->x_pers)] != '1')
			data->y_pers -= data->rc.dir_y * TMS;
	}
}
