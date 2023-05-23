/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringssss.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:25:54 by nnorazma          #+#    #+#             */
/*   Updated: 2023/05/23 12:25:56 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_char(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*output;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = count_char(n);
	output = (char *) malloc (sizeof(char) * (i + 1));
	if (!output)
		return (NULL);
	output[i--] = '\0';
	if (n < 0)
	{
		output[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		output[i--] = 48 + (n % 10);
		n /= 10;
	}
	return (output);
}
