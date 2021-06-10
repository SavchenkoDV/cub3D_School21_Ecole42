/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions_first.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:02:25 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 21:48:11 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	dvs_putstr(char *s)
{
	int	i;

	i = 0;
	while (s && (s[i] != '\0'))
	{
		write(2, &s[i], 1);
		i++;
	}
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	dvs_atoi(char **str, char sym)
{
	int	nb;

	while (*(*str) == ' ')
		(*str)++;
	if (*(*str) >= sym && *(*str) <= '9')
	{
		nb = *(*str) - '0';
		while (*(*str) >= '0' && *(*str) <= '9')
		{
			if ((*str)[1] >= '0' && (*str)[1] <= '9')
				nb = nb * 10 + ((*str)[1] - '0');
			else
			{
				(*str)++;
				return (nb);
			}
			(*str)++;
		}
	}
	return (-5);
}

char	*dvs_join(char *before_line, char sym)
{
	int		i;
	char	*new_line;
	int		size_line;

	i = 0;
	size_line = ft_strlen(before_line);
	new_line = malloc(size_line + 2);
	if (new_line == NULL)
		return (NULL);
	while (before_line[i] != '\0')
	{
		new_line[i] = before_line[i];
		i++;
	}
	new_line[size_line] = sym;
	new_line[size_line + 1] = '\0';
	free(before_line);
	return (new_line);
}

int	get_next_line(char **line, int fd)
{
	char	sym;
	int		res;

	res = 1;
	*line = malloc(1);
	if (*line == NULL)
		return (-4);
	*(line[0]) = '\0';
	while (res > 0)
	{
		res = read(fd, &sym, 1);
		if (res <= 0)
			break ;
		if (sym == '\n')
			return (1);
		*line = dvs_join(*line, sym);
		if (*line == NULL)
			return (-4);
	}
	if (res < 0)
		return (-1);
	return (0);
}
