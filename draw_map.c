/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:59:58 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 19:45:44 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_background(t_data *data, int w, int h)
{
	int	half_win;

	half_win = data->header.rh / 2;
	while (half_win > h)
	{
		while (data->header.rw > w)
		{
			fast_mlx_pixel_put(&data->img, w, h, data->header.hex_ceiling);
			w++;
		}
		w = 0;
		h++;
	}
	while (data->header.rh > h)
	{
		while (data->header.rw > w)
		{
			fast_mlx_pixel_put(&data->img, w, h, data->header.hex_floor);
			w++;
		}
		w = 0;
		h++;
	}
}

void	screenshot(t_data	*data)
{
	if (data->av == 1)
	{
		draw_background(data, 0, 0);
		draw_wall(data);
		draw_sp(data, 0);
		make_screenshot(data, 0, 0);
		exit(0);
	}
}

void	write_count_sort_sp_norm(t_data *data, int i)
{
	while (i < data->count_sp)
	{
		data->sp.sp_ord[i] = i;
		data->sp.sp_dist[i] = ((data->x_pers - data->dsp[i].x)
				* (data->x_pers - data->dsp[i].x) +(data->y_pers
					- data->dsp[i].y) * (data->y_pers - data->dsp[i].y));
		i++;
	}
}

void	check_fc_norm(t_data *data, int sym)
{
	if (sym == 'F' && data->norm.f == 0)
	{
		data->norm.f = 1;
		data->header.hex_floor = data->norm.r << 16 | data->norm.g << 8
			| data->norm.b;
		data->norm.counter += 1;
	}
	if (sym == 'C' && data->norm.c == 0)
	{
		data->norm.c = 1;
		data->header.hex_ceiling = data->norm.r << 16 | data->norm.g << 8
			| data->norm.b;
		data->norm.counter += 1;
	}
}

void	check_acav_norm(int i)
{
	if (i != 6)
	{
		dvs_putstr("Error\nWrong arguments!");
		exit (0);
	}
}
