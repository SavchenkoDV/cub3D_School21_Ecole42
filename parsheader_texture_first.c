/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsheader_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:12:57 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 19:14:38 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_no(t_data *data, char *line, int i, int flag)
{
	int	len;

	len = 0;
	if (data->header.no != NULL || line[1] != ' ')
		return (-11);
	data->header.no = " ";
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] >= '!' && line[i] <= '~')
		{
			if (flag == 1)
				return (-6);
			while (line[i] >= '!' && line[i++] <= '~')
				len++;
			flag = caw_texture(data, &line[i - len], len, 'n');
			if (flag < 0)
				return (flag);
		}
		else
			i++;
	}
	data->norm.counter += 1;
	return (tern_s(flag, flag, 0));
}

int	check_so(t_data *data, char *line, int i, int flag)
{
	int	len;

	len = 0;
	if (data->header.so != NULL || line[1] != ' ')
		return (-11);
	data->header.so = " ";
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] >= '!' && line[i] <= '~')
		{
			if (flag == 1)
				return (-6);
			while (line[i] >= '!' && line[i++] <= '~')
				len++;
			flag = caw_texture(data, &line[i - len], len, 's');
			if (flag < 0)
				return (flag);
		}
		else
			i++;
	}
	data->norm.counter += 1;
	return (tern_s(flag, flag, 0));
}

int	check_we(t_data *data, char *line, int i, int flag)
{
	int	len;

	len = 0;
	if (data->header.we != NULL || line[1] != ' ')
		return (-11);
	data->header.we = " ";
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] >= '!' && line[i] <= '~')
		{
			if (flag == 1)
				return (-6);
			while (line[i] >= '!' && line[i++] <= '~')
				len++;
			flag = caw_texture(data, &line[i - len], len, 'w');
			if (flag < 0)
				return (flag);
		}
		else
			i++;
	}
	data->norm.counter += 1;
	return (tern_s(flag, flag, 0));
}

int	check_ea(t_data *data, char *line, int i, int flag)
{
	int	len;

	len = 0;
	if (data->header.ea != NULL || line[1] != ' ')
		return (-11);
	data->header.ea = " ";
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] >= '!' && line[i] <= '~')
		{
			if (flag == 1)
				return (-6);
			while (line[i] >= '!' && line[i++] <= '~')
				len++;
			flag = caw_texture(data, &line[i - len], len, 'e');
			if (flag < 0)
				return (flag);
		}
		else
			i++;
	}
	data->norm.counter += 1;
	return (tern_s(flag, flag, 0));
}

int	check_s(t_data *data, char *line, int i, int flag)
{
	int	len;

	len = 0;
	if (data->header.s != NULL || *line != ' ')
		return (-11);
	data->header.s = " ";
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] >= '!' && line[i] <= '~')
		{
			if (flag == 1)
				return (-6);
			while (line[i] >= '!' && line[i++] <= '~')
				len++;
			flag = caw_texture(data, &line[i - len], len, 'o');
			if (flag < 0)
				return (flag);
		}
		else
			i++;
	}
	data->norm.counter += 1;
	return (tern_s(flag, flag, 0));
}
