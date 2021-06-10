/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_norm_seven.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:59:38 by buthor            #+#    #+#             */
/*   Updated: 2021/04/13 22:53:18 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && str1[i] != '\0' && n - 1 > i)
		i++;
	if (str1[i] != str2[i])
		return (str1[i] - str2[i]);
	return (0);
}

void	check_cub(char *av, int i)
{
	if (dvs_strchr(av, '.') == 0)
	{
		while (av[i] != '.')
			i++;
		if (ft_strlen(&av[i]) != 4)
		{
			dvs_putstr("Error\nWrong argument!");
			exit(0);
		}
		else
		{
			if (ft_strncmp(".cub", &av[i], 4) == 0)
				return ;
			dvs_putstr("Error\nWrong argument!");
			exit(0);
		}
	}
	else
	{
		dvs_putstr("Error\nWrong argument!");
		exit(0);
	}
}
