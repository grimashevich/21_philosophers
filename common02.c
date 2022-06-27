/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:01:32 by EClown            #+#    #+#             */
/*   Updated: 2022/06/27 19:03:10 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

unsigned int	ft_strlen(const char *s)
{
	unsigned int	result;

	result = 0;
	while (*(s++) != 0)
		result++;
	return (result);
}

static int	ncmp_result(int n)
{
	if (n > 0)
		return (1);
	if (n < 0)
		return (-1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return (ncmp_result((unsigned char) s1[i] - (unsigned char) s2[i]));
		i++;
	}
	return (ncmp_result((unsigned char) s1[i - 1] - (unsigned char) s2[i - 1]));
}