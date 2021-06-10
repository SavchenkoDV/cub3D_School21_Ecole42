/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:30:18 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 18:21:23 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rend_sp(t_data *data, int y, int d)
{
	int	pos;
	int	color;

	while (y < data->sp.end_y)
	{
		d = (y) * 256 - data->header.rh * 128 + data->sp.sp_h * 128;
		data->sp.tex_y = ((d * data->header.h_texture_s) / data->sp.sp_h) / 256;
		pos = (data->sp.tex_y * data->header.line_len_s
				+ data->sp.tex_x * (data->header.bpp_s / 8));
		color = *(int *)(data->header.addr_s + pos);
		if (color != 0)
			fast_mlx_pixel_put(&data->img, data->sp.str_x, y, color);
		y++;
	}
}

void	draw_sp(t_data *data, int i)
{
	write_count_sort_sp(data, 0, 0, 0);
	while (i < data->count_sp)
	{
		transp_pos_to_rel_to_cam(data, i);
		data->sp.sp_h = abs((int)(data->header.rh / (data->sp.tform_y)));
		calc_h_and_w_sprite(data);
		while (data->sp.str_x < data->sp.end_x)
		{
			data->sp.tex_x = (int)(256 * (data->sp.str_x
						- (-data->sp.sp_w / 2 + data->sp.spscreenx))
					* data->header.w_texture_s / data->sp.sp_w) / 256;
			if (data->sp.tform_y > 0 && data->sp.str_x > 0
				&& data->sp.str_x < data->header.rw && data->sp.tform_y
				&& data->sp.tform_y < data->rc.zbuf[data->sp.str_x])
				rend_sp(data, data->sp.str_y, 0);
			data->sp.str_x++;
		}
		i++;
	}
}

int	rendering(t_data *data)
{
	draw_background(data, 0, 0);
	draw_wall(data);
	draw_sp(data, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		data->img.img, 0, 0);
	mlx_do_sync(data->mlx.mlx);
	return (0);
}

void	prepare_sprite(t_data *data, int i, int j)
{
	int	counter;

	counter = 0;
	data->dsp = malloc(sizeof(t_dsp) * data->count_sp);
	if (data->dsp == NULL)
	{
		check_error_file(-4);
		exit (0);
	}
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == '2')
			{
				data->dsp[counter].y = i + 0.5;
				data->dsp[counter].x = j + 0.5;
				counter++;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int	tern_to_pars(int res)
{
	if (res == 0)
		return (check_error_file(-3));
	else
		return (check_error_file(res));
}
