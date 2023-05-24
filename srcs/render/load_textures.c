/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:17 by hwong             #+#    #+#             */
/*   Updated: 2023/05/24 14:18:29 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Bit-shift an integer to store rgb value
*/
static int	rgb_to_int( int r, int g, int b )
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
	Allocate memory and set texture values for the
	specified image
*/
static int	set_textures( t_img *img, void *mlx, char *path )
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error: ", 8);
		return (write(2, path, ft_slen(path)));
	}
	img->mlx_img = mlx_xpm_file_to_image(mlx, path, &img->x, &img->y);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	return (0);
}

/*
	Convert given xpm files into mlx images
	Convert string rgb values to hexadecimal
*/
int	load_textures( t_game *g )
{
	int	*c;

	if (set_textures(&g->tex->north, g->mlx, g->paths[0])
		|| set_textures(&g->tex->south, g->mlx, g->paths[1])
		|| set_textures(&g->tex->west, g->mlx, g->paths[2])
		|| set_textures(&g->tex->east, g->mlx, g->paths[3])
		|| set_textures(&g->tex->door, g->mlx, "./textures/amogus.xpm")
		|| set_textures(&g->tex->rock, g->mlx, "./textures/rock.xpm"))
	{
		free_tab(g->paths);
		return (1);
	}
	c = malloc(sizeof(int) * 3);
	strrgb_to_rgba(g->paths[4], c);
	g->tex->floor = rgb_to_int(c[0], c[1], c[2]);
	strrgb_to_rgba(g->paths[5], c);
	g->tex->ceiling = rgb_to_int(c[0], c[1], c[2]);
	free(c);
	free_tab(g->paths);
	return (0);
}