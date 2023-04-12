/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringsss.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:41:23 by hwong             #+#    #+#             */
/*   Updated: 2023/04/12 14:26:05 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*temp;

	if (!str || !n)
		return ;
	temp = (unsigned char *)str;
	while (n-- > 0)
		*(temp++) = '\0';
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*array;

	array = (void *) malloc (size * nitems);
	if (!array)
		return (NULL);
	ft_bzero(array, size * nitems);
	return (array);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memset(void *s, int c, size_t n)
{
	int	*temp;

	if (!s)
		return (NULL);
	temp = (int *)s;
	while (n-- > 0)
		*(temp++) = c;
	return (s);
}

int	ismapchar( int ch )
{
	return (ch == ' ' || ch == '1');
}
