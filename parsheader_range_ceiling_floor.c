/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsheader_range_ceiling_floor.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:23:13 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 19:53:09 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_range(t_data *data, char *line)
{
	if (data->header.range != NULL || *line != ' ')
		return (-11);
	data->header.range = " ";
	data->header.rw = dvs_atoi(&line, '1');
	if (data->header.rw < 1)
		return (-5);
	data->header.rh = dvs_atoi(&line, '1');
	if (data->header.rh < 1)
		return (-5);
	while (*line != '\0' && *line != '\n')
	{
		if (*line != ' ')
			return (-5);
		line++;
	}
	if (data->header.rw > data->mlx.wsx)
		data->header.rw = data->mlx.wsx;
	if (data->header.rh > data->mlx.wsy)
		data->header.rh = data->mlx.wsy;
	data->norm.counter = data->norm.counter + 1;
	return (0);
}

int	check_fc_comma(char **line)
{
	while ((**line) == ' ')
		(*line)++;
	if ((**line) == ',')
		(*line)++;
	else
		return (-7);
	return (0);
}

int	check_fc(t_data *data, char *line, char **ceiling_or_floor, char sym)
{
	data->norm.r = 0;
	data->norm.g = 0;
	data->norm.b = 0;
	if (*ceiling_or_floor != NULL || *line != ' ')
		return (-11);
	*ceiling_or_floor = " ";
	data->norm.r = dvs_atoi(&line, '0');
	if (check_fc_comma(&line) < 0)
		return (-7);
	data->norm.g = dvs_atoi(&line, '0');
	if (check_fc_comma(&line) < 0)
		return (-7);
	data->norm.b = dvs_atoi(&line, '0');
	if (*line != '\0' && *line != '\n')
		return (-7);
	if (data->norm.r > 255 || data->norm.r < 0 || data->norm.g > 255
		|| data->norm.g < 0 || data->norm.b > 255 || data->norm.b < 0)
		return (-7);
	check_fc_norm(data, sym);
	return (0);
}
