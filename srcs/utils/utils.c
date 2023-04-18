/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:12:31 by hwong             #+#    #+#             */
/*   Updated: 2023/04/18 19:34:24 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable( char ch )
{
	return (ch == '0' || ch == 'N' || ch == 'S'
		|| ch == 'E' || ch == 'W');
}

int	get_center( int start, int end )
{
	return (end - ((end - start) / 2));
}

int	all_found( int *found )
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (found[i] != 1)
			return (0);
		i++;
	}
	return (1);
}
