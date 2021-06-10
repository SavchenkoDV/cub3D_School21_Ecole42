/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:10:11 by buthor            #+#    #+#             */
/*   Updated: 2021/04/10 16:41:33 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_data_buff(t_data *data)
{
	if (data->rc.rdx > 0)
	{
		data->header.buf = data->header.no;
		data->header.addr_buf = data->header.addr_no;
		data->header.w_texture_buf = data->header.w_texture_no;
		data->header.h_texture_buf = data->header.h_texture_no;
		data->header.line_len_buf = data->header.line_len_no;
		data->header.bpp_buf = data->header.bpp_no;
		data->header.end_buf = data->header.end_no;
	}
	else
	{
		data->header.buf = data->header.so;
		data->header.addr_buf = data->header.addr_so;
		data->header.w_texture_buf = data->header.w_texture_so;
		data->header.h_texture_buf = data->header.h_texture_so;
		data->header.line_len_buf = data->header.line_len_so;
		data->header.bpp_buf = data->header.bpp_so;
		data->header.end_buf = data->header.end_so;
	}
	data->txd.tex_x = data->header.w_texture_buf - data->txd.tex_x - 1;
}

void	init_data_bufs(t_data *data)
{
	if (data->rc.rdy > 0)
	{
		data->header.buf = data->header.we;
		data->header.addr_buf = data->header.addr_we;
		data->header.w_texture_buf = data->header.w_texture_we;
		data->header.h_texture_buf = data->header.h_texture_we;
		data->header.line_len_buf = data->header.line_len_we;
		data->header.bpp_buf = data->header.bpp_we;
		data->header.end_buf = data->header.end_we;
	}
	else
	{
		data->header.buf = data->header.ea;
		data->header.addr_buf = data->header.addr_ea;
		data->header.w_texture_buf = data->header.w_texture_ea;
		data->header.h_texture_buf = data->header.h_texture_ea;
		data->header.line_len_buf = data->header.line_len_ea;
		data->header.bpp_buf = data->header.bpp_ea;
		data->header.end_buf = data->header.end_ea;
	}
	data->txd.tex_x = data->header.w_texture_buf - data->txd.tex_x - 1;
}

void	find_pix_tex_and_wall(t_data *data)
{
	if (data->rc.side == 0)
		data->txd.wall_x = data->y_pers + data->rc.pwd * data->rc.rdy;
	else
		data->txd.wall_x = data->x_pers + data->rc.pwd * data->rc.rdx;
	data->txd.wall_x = data->txd.wall_x - floor(data->txd.wall_x);
	data->txd.tex_x = (int)(data->txd.wall_x
			* (double)data->header.w_texture_buf);
}

void	rend(t_data *data, double step_increase, double start_tex_pos, int x)
{
	int	color;
	int	tex_y;
	int	pos;

	while (data->rc.drw_str < data->rc.drw_end)
	{
		tex_y = (int)start_tex_pos & (data->header.h_texture_buf - 1);
		pos = (tex_y * data->header.line_len_buf
				+ data->txd.tex_x * (data->header.bpp_buf / 8));
		start_tex_pos = start_tex_pos + step_increase;
		color = *(int *)(data->header.addr_buf + pos);
		fast_mlx_pixel_put(&data->img, x, data->rc.drw_str, color);
		data->rc.drw_str++;
	}
}

void	draw_wall(t_data *data)
{
	int		x;
	double	step_increase;
	double	start_tex_pos;

	x = 0;
	while (x < data->header.rw)
	{
		calc_rp_and_rd(data, x);
		init_step_and_calc_side_dist(data);
		dda_algoritm(data);
		preparation_to_draw(data);
		find_pix_tex_and_wall(data);
		if (data->rc.side == 0)
			init_data_buff(data);
		else
			init_data_bufs(data);
		step_increase = 1.0 * data->header.h_texture_buf / data->rc.h_line;
		start_tex_pos = (data->rc.drw_str - data->header.rh
				/ 2.0 + data->rc.h_line / 2.0) * step_increase;
		rend(data, step_increase, start_tex_pos, x);
		data->rc.zbuf[x] = data->rc.pwd;
		x++;
	}
}
