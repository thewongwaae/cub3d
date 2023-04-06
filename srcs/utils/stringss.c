/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:30 by hwong             #+#    #+#             */
/*   Updated: 2023/04/06 17:12:55 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strchr( const char *s, int c )
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

int	is_space( char c )
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_digit( char c )
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi( const char *s )
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (is_space(*s))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	while (is_digit(*s))
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}

char	*ft_strtok( char *s, char sep )
{
	static char	*stock;
	char		*ptr;

	ptr = NULL;
	if (s)
	{
		free(stock);
		stock = ft_strdup(s);
	}
	while (*stock)
	{
		if (!ptr && *stock != sep)
			ptr = stock;
		else if (ptr && *stock == sep)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	return (ptr);
}
