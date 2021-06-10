/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:31:10 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 22:31:00 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	fill_and_check_map(t_data *data, char *map_addres, int result)
{
	result = fill_map(map_addres, data, result);
	if (result < 0)
	{
		dvs_free_map(data);
		return (check_error_file(result));
	}
	if (check_map(data) != 0)
	{
		dvs_free_map(data);
		return (check_error_file(-3));
	}
	return (0);
}

int	pars_and_check_file(char *map_addres, t_data *data)
{
	int	result;

	result = pars_and_check_header(map_addres, data, 0, 0);
	if (result < 0)
		return (tern_to_pars(result));
	data->x_map = x_size_map(map_addres, result);
	if (data->x_map < 0)
		return (check_error_file(data->x_map));
	data->y_map = y_size_map(map_addres, result, 0, data);
	if (data->y_map < 0)
		return (check_error_file(data->y_map));
	data->map = allocate_map(data);
	if (data->map == NULL)
		return (check_error_file(-4));
	result = fill_and_check_map(data, map_addres, result);
	if (result < 0)
		return (-1);
	fill_map_count_sp_and_write_pos_pers(data, 0, 0);
	prepare_sprite(data, 0, 0);
	return (0);
}

int	close_win(void)
{
	exit (0);
}

void	check_acav(t_data *data, char **av, int ac)
{
	int		i;
	char	*save;

	i = 0;
	save = "--save";
	if (ac != 2 && ac != 3)
	{
		dvs_putstr("Error\nWrong arguments!");
		exit(0);
	}
	check_cub(av[1], 0);
	if (ac == 2)
		return ;
	while (av[2][i] != '\0')
	{
		if (save[i] != av[2][i])
		{
			dvs_putstr("Error\nWrong arguments!");
			exit (0);
		}
		i++;
	}
	check_acav_norm(i);
	data->av = 1;
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_acav(&data, argv, argc);
	init_data_and_mlx_pixput(&data);
	init_data_raycast(&data);
	data.mlx.mlx = mlx_init();
	mlx_get_screen_size(data.mlx.mlx, &data.mlx.wsx, &data.mlx.wsy);
	if (pars_and_check_file(argv[1], &data) < 0)
		exit (0);
	init_others(&data);
	data.img.img = mlx_new_image(data.mlx.mlx, data.header.rw, data.header.rh);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
			&data.img.line_length, &data.img.endian);
	screenshot(&data);
	data.mlx.win = mlx_new_window(data.mlx.mlx, data.header.rw, data.header.rh,
			"https://github.com/SavchenkoDV");
	mlx_hook(data.mlx.win, 2, 1L << 0, calculation, &data);
	mlx_hook(data.mlx.win, 17, 0L, close_win, NULL);
	mlx_loop_hook(data.mlx.mlx, rendering, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
