/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_four.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:31:43 by buthor            #+#    #+#             */
/*   Updated: 2021/04/11 19:46:59 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	tern_s(int nbr, int ret, int elret)
{
	if (nbr < 0)
		return (ret);
	else
		return (elret);
}

int	check_for_opening_and_reading(char *addres)
{
	int		fd;
	char	sym;

	fd = open(addres, O_RDONLY);
	if (fd < 0)
		return (-8);
	if (read(fd, &sym, 1) < 0)
	{
		close(fd);
		return (-9);
	}
	close(fd);
	return (0);
}

int	check_and_write_texture_norm25(t_data *data, char nsweo)
{
	if (nsweo == 'n' && data->header.no == NULL)
		return (-9);
	if (nsweo == 's' && data->header.so == NULL)
		return (-9);
	if (nsweo == 'w' && data->header.we == NULL)
		return (-9);
	if (nsweo == 'e' && data->header.ea == NULL)
		return (-9);
	if (nsweo == 'o' && data->header.s == NULL)
		return (-9);
	return (0);
}

void	fill_data_no_to_struct(t_data *data, char *address)
{
	data->header.no = mlx_xpm_file_to_image(data->mlx.mlx, address,
			&data->header.w_texture_no, &data->header.h_texture_no);
	data->header.addr_no = mlx_get_data_addr(data->header.no,
			&data->header.bpp_no, &data->header.line_len_no,
			&data->header.end_no);
}

void	fill_data_so_to_struct(t_data *data, char *address)
{
	data->header.so = mlx_xpm_file_to_image(data->mlx.mlx, address,
			&data->header.w_texture_so, &data->header.h_texture_so);
	data->header.addr_so = mlx_get_data_addr(data->header.so,
			&data->header.bpp_so, &data->header.line_len_so,
			&data->header.end_so);
}
