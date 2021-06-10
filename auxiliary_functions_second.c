/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions_second.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:24:59 by buthor            #+#    #+#             */
/*   Updated: 2021/03/24 21:03:38 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	dvs_free_map(t_data *data)
{
	int	y;

	y = 0;
	while (data->map[y] != NULL)
	{
		free(data->map[y]);
		y++;
	}
	free(data->map[y]);
	free(data->map);
}

int	dvs_strchr(char *s, int c)
{
	char	*src;

	src = (char *)s;
	while (*src != '\0')
	{
		if (*src == (char)c)
			return (0);
		src++;
	}
	if (*src == (char)c && (char)c == '\0')
		return (0);
	return (1);
}
