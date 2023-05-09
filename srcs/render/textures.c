/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:17 by hwong             #+#    #+#             */
/*   Updated: 2023/05/09 20:18:17 by hwong            ###   ########.fr       */
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
static void	set_textures( t_img *img, t_game *g, char *path )
{
	int	x;
	int	y;

	printf("Loading texture: %s\n", path);
	img = malloc (sizeof(t_img));
	img->mlx_img = mlx_xpm_file_to_image(g->mlx, path, &x, &y);
	if (img->mlx_img == NULL)
        printf("Failed to load texture: %s\n", path);
    else
        img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
}

/*
	Convert given xpm files into mlx images
	Convert string rgb values to hexadecimal
*/
void	load_textures( t_game *g )
{
	int	*c;

	set_textures(&g->tex.north, g, g->paths[0]);
	set_textures(&g->tex.south, g, g->paths[1]);
	set_textures(&g->tex.west, g, g->paths[2]);
	set_textures(&g->tex.east, g, g->paths[3]);
	c = malloc(sizeof(int) * 3);
	strrgb_to_rgba(g->paths[4], c);
	g->tex.floor = rgb_to_int(c[0], c[1], c[2]);
	strrgb_to_rgba(g->paths[5], c);
	g->tex.ceiling = rgb_to_int(c[0], c[1], c[2]);
	free(c);
	free_tab(g->paths);
}
