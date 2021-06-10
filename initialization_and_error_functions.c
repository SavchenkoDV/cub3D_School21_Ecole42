/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:10:21 by buthor            #+#    #+#             */
/*   Updated: 2021/04/10 23:27:04 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_data_and_mlx_pixput(t_data *data)
{
	data->dsp = NULL;
	data->count_sp = 0;
	data->x_map = 0;
	data->y_map = 0;
	data->x_pers = 0;
	data->y_pers = 0;
	data->map = NULL;
	data->mlx.wsx = 0;
	data->mlx.wsy = 0;
	data->img.bits_per_pixel = 0;
	data->img.line_length = 0;
	data->img.endian = 0;
	data->norm.counter = 0;
	data->norm.f = 0;
	data->norm.c = 0;
	data->norm.r = 0;
	data->norm.g = 0;
	data->norm.b = 0;
}

void	init_header_first(t_data *data)
{
	data->header.no = NULL;
	data->header.addr_no = NULL;
	data->header.w_texture_no = 0;
	data->header.h_texture_no = 0;
	data->header.line_len_no = 0;
	data->header.bpp_no = 0;
	data->header.end_no = 0;
	data->header.so = NULL;
	data->header.addr_so = NULL;
	data->header.w_texture_so = 0;
	data->header.h_texture_so = 0;
	data->header.line_len_so = 0;
	data->header.bpp_so = 0;
	data->header.end_so = 0;
}

void	init_header_second(t_data *data)
{
	data->header.we = NULL;
	data->header.addr_we = NULL;
	data->header.w_texture_we = 0;
	data->header.h_texture_we = 0;
	data->header.line_len_we = 0;
	data->header.bpp_we = 0;
	data->header.end_we = 0;
	data->header.ea = NULL;
	data->header.addr_ea = NULL;
	data->header.w_texture_ea = 0;
	data->header.h_texture_ea = 0;
	data->header.line_len_ea = 0;
	data->header.bpp_ea = 0;
	data->header.end_ea = 0;
	data->header.s = NULL;
	data->header.addr_s = NULL;
	data->header.w_texture_s = 0;
	data->header.h_texture_s = 0;
	data->header.line_len_s = 0;
	data->header.bpp_s = 0;
	data->header.end_s = 0;
}

void	init_header(t_data *data)
{
	data->header.range = NULL;
	data->header.rw = 0;
	data->header.rh = 0;
	data->header.buf = NULL;
	data->header.addr_buf = NULL;
	data->header.w_texture_buf = 0;
	data->header.h_texture_buf = 0;
	data->header.line_len_buf = 0;
	data->header.bpp_buf = 0;
	data->header.end_buf = 0;
	init_header_first(data);
	init_header_second(data);
	data->header.floor = NULL;
	data->header.hex_floor = 0;
	data->header.ceiling = NULL;
	data->header.hex_ceiling = 0;
}

int	check_error_file(int nbroferror)
{
	if (nbroferror == -1)
		dvs_putstr("Error\nDon't open file *.cub!\n");
	else if (nbroferror == -2)
		dvs_putstr("Error\nDon't read file *.cub!\n");
	else if (nbroferror == -3)
		dvs_putstr("Error\nThe map isn't liquid!\n");
	else if (nbroferror == -4)
		dvs_putstr("Error\nMemory hasn't been allocated!\n");
	else if (nbroferror == -5)
		dvs_putstr("Error\nInvalid window range!\n");
	else if (nbroferror == -6)
		dvs_putstr("Error\nInvalid texture address!\n");
	else if (nbroferror == -7)
		dvs_putstr("Error\nThe meaning of the color is wrong!\n");
	else if (nbroferror == -8)
		dvs_putstr("Error\nDon't open file texture!\n");
	else if (nbroferror == -9)
		dvs_putstr("Error\nDon't read file texture!\n");
	else if (nbroferror == -10)
		dvs_putstr("Error\nThere aren't enough data in the header of the *"
			 ".cub!\n");
	else if (nbroferror == -11)
		dvs_putstr("Error\nThe data in the header of the *cub is "
			 "incorrect!\n");
	return (-1);
}
