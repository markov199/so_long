/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:06:12 by mkovoor           #+#    #+#             */
/*   Updated: 2022/11/17 09:48:31 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"solong.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (dest == NULL)
		return (0);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}

static int	ft_getdigits(int x)
{
	int	i;

	i = 0;
	if (x < 0)
	{
		i++;
		x = x * -1;
	}
	while (x >= 10)
	{
		i++;
		x = x / 10;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		j;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	j = ft_getdigits(n);
	i = j;
	s = malloc (sizeof(char) * j + 1);
	if (!s)
		return (0);
	if (n < 0)
	{
		n *= -1;
		s[0] = '-';
	}
	while (n > 0)
	{
		s[--j] = ((n % 10) + '0');
		n = n / 10;
	}
	s[i] = '\0';
	return (s);
}
