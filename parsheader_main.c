/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsheader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:36:55 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 19:14:38 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_all_and_fist_line_map(t_data *data, char first_sym)
{
	if (data->header.range != NULL && data->header.no != NULL
		&& data->header.so != NULL && data->header.we != NULL
		&& data->header.ea != NULL && data->header.s != NULL
		&& data->header.floor != NULL && data->header.ceiling != NULL
		&& data->norm.counter != 7)
	{
		if (first_sym == '1')
			return (1);
		else
			return (-3);
	}
	return (-11);
}

int	check_line(t_data *data, char *line, int i)
{
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == 'R')
			return (check_range(data, ++line));
		else if (line[i] == 'N' && line[i + 1] == 'O')
			return (check_no(data, ++line, 1, 0));
		else if (line[i] == 'S' && line[i + 1] == 'O')
			return (check_so(data, ++line, 1, 0));
		else if (line[i] == 'W' && line[i + 1] == 'E')
			return (check_we(data, ++line, 1, 0));
		else if (line[i] == 'E' && line[i + 1] == 'A')
			return (check_ea(data, ++line, 1, 0));
		else if (line[i] == 'S')
			return (check_s(data, ++line, 0, 0));
		else if (line[i] == 'F')
			return (check_fc(data, ++line, &data->header.floor, 'F'));
		else if (line[i] == 'C')
			return (check_fc(data, ++line, &data->header.ceiling, 'C'));
		else
			return (check_all_and_fist_line_map(data, line[i]));
	}
	return (0);
}

int	pars_and_check_header_norm25(t_data *data, int fd, int cntr)
{
	data->norm.resgnl = get_next_line(&data->norm.line, fd);
	while (data->norm.resgnl > 0)
	{
		data->norm.res = check_line(data, data->norm.line, 0);
		if (data->norm.res < 0)
		{
			free(data->norm.line);
			return (data->norm.res);
		}
		free(data->norm.line);
		data->norm.line = NULL;
		if (data->norm.res == 1)
			break ;
		cntr++;
		data->norm.resgnl = get_next_line(&data->norm.line, fd);
	}
	if (data->norm.resgnl <= 0 && data->norm.line != NULL)
	{
		free(data->norm.line);
		return (data->norm.resgnl);
	}
	if (data->norm.resgnl < 0)
		return (data->norm.resgnl);
	return (cntr);
}

int	pars_and_check_header(char *map_addres, t_data *data, int cntr, int fd)
{
	init_header(data);
	fd = open(map_addres, O_RDONLY);
	if (fd < 0)
		return (-1);
	cntr = pars_and_check_header_norm25(data, fd, cntr);
	close(fd);
	return (cntr);
}
