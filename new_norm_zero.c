/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_zero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:24:33 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 15:47:11 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void 	init_others_norm(t_data *data)
{
	data->sp.sp_ord = malloc((sizeof (int) * data->count_sp) + 1);
	if (data->sp.sp_ord == NULL)
	{
		check_error_file(-4);
		exit (0);
	}
	data->sp.sp_ord[data->count_sp] = '\0';
	data->sp.sp_dist = malloc((sizeof (double) * data->count_sp) + 1);
	if (data->sp.sp_dist == NULL)
	{
		check_error_file(-4);
		exit (0);
	}
	data->sp.sp_dist[data->count_sp] = '\0';
	data->sp.spx = 0;
	data->sp.spy = 0;
	data->sp.tform_x = 0;
	data->sp.tform_y = 0;
	data->sp.spscreenx = 0;
	data->sp.sp_h = 0;
	data->sp.sp_w = 0;
	data->sp.str_y = 0;
	data->sp.end_y = 0;
	data->sp.str_x = 0;
	data->sp.end_x = 0;
}

void	init_others(t_data *data)
{
	data->rc.zbuf = malloc((sizeof (double) * data->header.rw) + 1);
	if (data->rc.zbuf == NULL)
	{
		check_error_file(-4);
		exit (0);
	}
	data->rc.zbuf[data->header.rw] = '\0';
	data->rc.drw_str = 0;
	data->rc.drw_end = 0;
	data->rc.cam_x = 0;
	data->rc.h_line = 0;
	data->rc.sdx = 0;
	data->rc.sdy = 0;
	data->rc.rdy = 0;
	data->rc.rdx = 0;
	data->rc.map_x = 0;
	data->rc.map_y = 0;
	data->rc.ddx = 0;
	data->rc.ddy = 0;
	data->rc.stepx = 0;
	data->rc.stepy = 0;
	data->rc.hit = 0;
	data->rc.side = 0;
	data->sp.id = 0;
	init_others_norm(data);
}

void	init_data_raycast(t_data *data)
{
	data->rc.dir_x = 0;
	data->rc.dir_y = 0;
	data->rc.plane_x = 0;
	data->rc.plane_y = 0;
	data->rc.oldir_x = 0;
	data->rc.oldplane_x = 0;
}

int	get_color_bmp(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	init_head_bmp(unsigned char *buff, int size, t_data *data, int tmp)
{
	buff[0] = (unsigned char) 'B';
	buff[1] = (unsigned char) 'M';
	buff[2] = (unsigned char)size;
	buff[3] = (unsigned char)(size >> 8);
	buff[4] = (unsigned char)(size >> 16);
	buff[5] = (unsigned char)(size >> 24);
	buff[10] = (unsigned char)54;
	buff[14] = (unsigned char)40;
	buff[18] = (unsigned char)tmp;
	buff[19] = (unsigned char)(tmp >> 8);
	buff[20] = (unsigned char)(tmp >> 16);
	buff[21] = (unsigned char)(tmp >> 24);
	buff[22] = (unsigned char)data->header.rh;
	buff[23] = (unsigned char)(data->header.rh >> 8);
	buff[24] = (unsigned char)(data->header.rh >> 16);
	buff[25] = (unsigned char)(data->header.rh >> 24);
	buff[26] = (unsigned char)1;
	buff[28] = (unsigned char)24;
}
