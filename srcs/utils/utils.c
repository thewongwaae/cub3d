/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:12:31 by hwong             #+#    #+#             */
/*   Updated: 2023/05/09 14:45:03 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable( char ch )
{
	return (ch == '0' || ch == 'N' || ch == 'S'
		|| ch == 'E' || ch == 'W' || ch == '3');
}

double	get_center( int start, int end )
{
	return ((double)end - (((double)end
		- (double)start) / 2));
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

int	is_in_wall( t_game *game, int x, int y )
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / (double)CELL_SIZE);
	map_y = (int)(y / (double)CELL_SIZE);
	if (map_x < 0 || map_y < 0 || map_x >= game->msize.x
		|| map_y >= game->msize.y)
		return (1);
	return (!is_walkable(game->map[map_y][map_x]));
}

double	deg_to_rad( int angle )
{
	return ((double)angle * M_PI / (double)180);
}
