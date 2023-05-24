/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:17 by hwong             #+#    #+#             */
/*   Updated: 2023/05/24 16:15:54 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (set_color(g))
		return (write(2, "Error: Bad color", 17));
	free_tab(g->paths);
	return (0);
}
