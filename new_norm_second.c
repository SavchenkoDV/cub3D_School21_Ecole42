/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_second.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:28:25 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 18:30:28 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_pers_hor(int keycode, t_data *data)
{
	if (keycode == 0)
	{
		if (data->map[(int)data->y_pers][(int)(data->x_pers
			+ data->rc.dir_y * SUD)] != '1')
			data->x_pers += data->rc.dir_y * SUD;
		if (data->map[(int)(data->y_pers - data->rc.dir_x
				* SUD)][(int)(data->x_pers)] != '1')
			data->y_pers -= data->rc.dir_x * SUD;
	}
	if (keycode == 2)
	{
		if (data->map[(int)data->y_pers][(int)(data->x_pers
			- data->rc.dir_y * SUD)] != '1')
			data->x_pers -= data->rc.dir_y * SUD;
		if (data->map[(int)(data->y_pers + data->rc.dir_x
				* SUD)][(int)(data->x_pers)] != '1')
			data->y_pers += data->rc.dir_x * SUD;
	}
}

int	calculation(int keycode, t_data *data)
{
	if (keycode == 126 || keycode == 13)
		move_pers_ver(keycode, data);
	if (keycode == 125 || keycode == 1)
		move_pers_ver(keycode, data);
	if (keycode == 123)
		rotate_pers(123, data);
	if (keycode == 124)
		rotate_pers(124, data);
	if (keycode == 0)
		move_pers_hor(keycode, data);
	if (keycode == 2)
		move_pers_hor(keycode, data);
	if (keycode == 53)
		exit (0);
	return (0);
}

void	write_count_sort_sp(t_data *data, int dtmp, int i, int j)
{
	write_count_sort_sp_norm(data, i);
	i = 0;
	while (i < data->count_sp - 1)
	{
		j = 0;
		while (j < data->count_sp - i - 1)
		{
			if (data->sp.sp_dist[j] < data->sp.sp_dist[j + 1])
			{
				dtmp = (int) data->sp.sp_dist[j];
				data->sp.sp_dist[j] = data->sp.sp_dist[j + 1];
				data->sp.sp_dist[j + 1] = dtmp;
				data->norm.tmp = data->sp.sp_ord[j];
				data->sp.sp_ord[j] = data->sp.sp_ord[j + 1];
				data->sp.sp_ord[j + 1] = data->norm.tmp;
			}
			j++;
		}
		i++;
	}
}

void	transp_pos_to_rel_to_cam(t_data *data, int i)
{
	data->sp.spx = data->dsp[data->sp.sp_ord[i]].x - data->x_pers;
	data->sp.spy = data->dsp[data->sp.sp_ord[i]].y - data->y_pers;
	data->sp.id = 1.0 / (data->rc.plane_x * data->rc.dir_y
			- data->rc.dir_x * data->rc.plane_y);
	data->sp.tform_x = data->sp.id * (data->rc.dir_y
			* data->sp.spx - data->rc.dir_x * data->sp.spy);
	data->sp.tform_y = data->sp.id * (-data->rc.plane_y
			* data->sp.spx + data->rc.plane_x * data->sp.spy);
	data->sp.spscreenx = (int)((data->header.rw / 2.0)
			* (1 + data->sp.tform_x / data->sp.tform_y));
}

void	calc_h_and_w_sprite(t_data *data)
{
	data->sp.str_y = -data->sp.sp_h / 2 + data->header.rh / 2;
	if (data->sp.str_y < 0)
		data->sp.str_y = 0;
	data->sp.end_y = data->sp.sp_h / 2 + data->header.rh / 2;
	if (data->sp.end_y >= data->header.rh)
		data->sp.end_y = data->header.rh - 1;
	data->sp.sp_w = abs((int)(data->header.rw / (data->sp.tform_y)));
	data->sp.str_x = -data->sp.sp_w / 2 + data->sp.spscreenx;
	if (data->sp.str_x < 0)
		data->sp.str_x = 0;
	data->sp.end_x = data->sp.sp_w / 2 + data->sp.spscreenx;
	if (data->sp.end_x >= data->header.rw)
		data->sp.end_x = data->header.rw - 1;
}
