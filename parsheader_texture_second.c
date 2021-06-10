/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsheader_texture_second.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:18:25 by buthor            #+#    #+#             */
/*   Updated: 2021/04/10 22:06:32 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill_data_we_to_struct(t_data *data, char *address)
{
	data->header.we = mlx_xpm_file_to_image(data->mlx.mlx, address,
			&data->header.w_texture_we, &data->header.h_texture_we);
	data->header.addr_we = mlx_get_data_addr(data->header.we,
			&data->header.bpp_we, &data->header.line_len_we,
			&data->header.end_we);
}

void	fill_data_ea_to_struct(t_data *data, char *address)
{
	data->header.ea = mlx_xpm_file_to_image(data->mlx.mlx, address,
			&data->header.w_texture_ea, &data->header.h_texture_ea);
	data->header.addr_ea = mlx_get_data_addr(data->header.ea,
			&data->header.bpp_ea, &data->header.line_len_ea,
			&data->header.end_ea);
}

void	fill_data_sp_to_struct(t_data *data, char *address)
{
	data->header.s = mlx_xpm_file_to_image(data->mlx.mlx, address,
			&data->header.w_texture_s, &data->header.h_texture_s);
	data->header.addr_s = mlx_get_data_addr(data->header.s,
			&data->header.bpp_s, &data->header.line_len_s,
			&data->header.end_s);
}

int	check_and_write_texture(t_data *data, char nsweo, char *address)
{
	if (nsweo == 'n')
		fill_data_no_to_struct(data, address);
	if (nsweo == 's')
		fill_data_so_to_struct(data, address);
	if (nsweo == 'w')
		fill_data_we_to_struct(data, address);
	if (nsweo == 'e')
		fill_data_ea_to_struct(data, address);
	if (nsweo == 'o')
		fill_data_sp_to_struct(data, address);
	if (check_and_write_texture_norm25(data, nsweo) < 0)
		return (-9);
	return (0);
}

int	caw_texture(t_data *data, char *line, int len, char nsweo)
{
	data->norm.res = 0;
	data->norm.i = 0;
	data->norm.new_line = malloc(len + 1);
	if (data->norm.new_line == NULL)
		return (-4);
	data->norm.new_line[len] = '\0';
	while (data->norm.i < len)
	{
		data->norm.new_line[data->norm.i] = line[data->norm.i];
		data->norm.i++;
	}
	data->norm.res = check_for_opening_and_reading(data->norm.new_line);
	if (data->norm.res < 0)
	{
		free(data->norm.new_line);
		return (data->norm.res);
	}
	data->norm.res = check_and_write_texture(data, nsweo, data->norm.new_line);
	if (data->norm.res < 0)
	{
		free(data->norm.new_line);
		return (data->norm.res);
	}
	free(data->norm.new_line);
	return (1);
}
