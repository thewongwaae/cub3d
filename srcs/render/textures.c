/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:17 by hwong             #+#    #+#             */
/*   Updated: 2023/05/06 17:16:03 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Bit-shift an integer to store rgb value
*/
int	rgba_to_int( int r, int g, int b )
{
	int	color;

	color = 0;
	color |= (int)(b % 256);
	color |= (int)(g % 256) << 8;
	color |= (int)(r % 256) << 16;
	return (color);
}

/*
	Convert a string rgb value to an int array of 3
*/
static void	strrgb_to_rgba( const char *strrgb, int *rgba )
{
	char	*tkn;
	int		i;

	i = 0;
	tkn = ft_strtok((char *)strrgb, ",");
	while (tkn)
	{
		rgba[i] = ft_atoi(tkn);
		i++;
		tkn = ft_strtok(NULL, ",");
	}
}

/*
	Convert given xpm files into mlx images
	Convert string rgb values to hexadecimal
*/
void	load_textures( t_game *game )
{
	int	x;
	int	y;
	int	*c;

	game->tex->north = mlx_xpm_file_to_image(game->mlx, game->paths[0], &x, &y);
	game->tex->south = mlx_xpm_file_to_image(game->mlx, game->paths[1], &x, &y);
	game->tex->west = mlx_xpm_file_to_image(game->mlx, game->paths[2], &x, &y);
	game->tex->east = mlx_xpm_file_to_image(game->mlx, game->paths[3], &x, &y);
	c = malloc(sizeof(int) * 3);
	strrgb_to_rgba(game->paths[4], c);
	game->tex->floor = rgba_to_int(c[0], c[1], c[2]);
	strrgb_to_rgba(game->paths[5], c);
	game->tex->ceiling = rgba_to_int(c[0], c[1], c[2]);
	free(c);
	free_tab(game->paths);
}
