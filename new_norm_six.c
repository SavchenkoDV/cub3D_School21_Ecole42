/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_six.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:37:07 by buthor            #+#    #+#             */
/*   Updated: 2021/04/11 19:37:52 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calc_rp_and_rd(t_data *data, int x)
{
	data->rc.cam_x = 2 * x / (double)(data->header.rw) - 1;
	data->rc.rdx = data->rc.dir_x + data->rc.plane_x * data->rc.cam_x;
	data->rc.rdy = data->rc.dir_y + data->rc.plane_y * data->rc.cam_x;
	data->rc.map_x = (int)(data->x_pers);
	data->rc.map_y = (int)(data->y_pers);
	data->rc.ddx = fabs(1 / data->rc.rdx);
	data->rc.ddy = fabs(1 / data->rc.rdy);
	data->rc.hit = 0;
}

void	init_step_and_calc_side_dist(t_data *data)
{
	if (data->rc.rdx < 0)
	{
		data->rc.stepx = -1;
		data->rc.sdx = (data->x_pers - data->rc.map_x) * data->rc.ddx;
	}
	else
	{
		data->rc.stepx = 1;
		data->rc.sdx = (data->rc.map_x + 1.0 - data->x_pers) * data->rc.ddx;
	}
	if (data->rc.rdy < 0)
	{
		data->rc.stepy = -1;
		data->rc.sdy = (data->y_pers - data->rc.map_y) * data->rc.ddy;
	}
	else
	{
		data->rc.stepy = 1;
		data->rc.sdy = (data->rc.map_y + 1.0 - data->y_pers) * data->rc.ddy;
	}
}

void	dda_algoritm(t_data *data)
{
	while (data->rc.hit == 0)
	{
		if (data->rc.sdx < data->rc.sdy)
		{
			data->rc.sdx += data->rc.ddx;
			data->rc.map_x += data->rc.stepx;
			data->rc.side = 0;
		}
		else
		{
			data->rc.sdy += data->rc.ddy;
			data->rc.map_y += data->rc.stepy;
			data->rc.side = 1;
		}
		if (data->map[data->rc.map_y][data->rc.map_x] == '1')
			data->rc.hit = 1;
	}
}

void	preparation_to_draw(t_data *data)
{
	if (data->rc.side == 0)
		data->rc.pwd = (data->rc.map_x - data->x_pers
				+ (1.0 - data->rc.stepx) / 2) / data->rc.rdx;
	else
		data->rc.pwd = (data->rc.map_y - data->y_pers
				+ (1.0 - data->rc.stepy) / 2) / data->rc.rdy;
	data->rc.h_line = (int)(data->header.rh / data->rc.pwd);
	data->rc.drw_str = -data->rc.h_line / 2 + data->header.rh / 2;
	if (data->rc.drw_str < 0)
		data->rc.drw_str = 0;
	data->rc.drw_end = data->rc.h_line / 2 + data->header.rh / 2;
	if (data->rc.drw_end >= data->header.rh)
		data->rc.drw_end = data->header.rh - 1;
}
