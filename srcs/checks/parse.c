/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:14 by hwong             #+#    #+#             */
/*   Updated: 2023/04/13 13:36:28 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**cub_to_array( int fd )
{
	char	*read;
	char	*buff;
	char	*tmp;
	char	**res;

	read = gnl(fd);
	buff = ft_strdup("");
	while (read)
	{
		tmp = ft_strjoin(buff, read);
		free(buff);
		buff = tmp;
		free(read);
		read = gnl(fd);
	}
	ft_free(read);
	res = ft_split(buff, '\n');
	ft_free(buff);
	return (res);
}

static int	all_found( int *found )
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

static int	parse_textures( char **mapfile, char **texs, t_game *game )
{
	int		i;
	int		j;
	char	*space;

	i = 0;
	j = 0;
	while (i < 6)
	{
		j = 0;
		while (mapfile[j])
		{
			if (!ft_strncmp(mapfile[j], texs[i], ft_slen(texs[i])))
			{
				space = ft_strchr(mapfile[j], ' ');
				if (space)
				{
					game->paths[i] = ft_strdup(space + 1);
					game->foundtex[i] += 1;
					if (j > game->foundtex[6])
						game->foundtex[6] = j;
				}
			}
			j++;
		}
		i++;
	}
	game->paths[i] = NULL;
	if (!all_found(game->foundtex))
		return (0);
	return (game->foundtex[6]);
}

static int	parse_map( char **mapfile, t_game *game )
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mapfile[i] && !ismapchar(mapfile[i][0]))
		i++;
	while (mapfile[i + j])
	{
		if (mapfile[i + j][0] == '\n')
			return (write(2, "Error: Newline in map", 22));
		j++;
	}
	game->map = malloc(sizeof(char *) * (j + 1));
	while (mapfile[i + game->msize.y])
	{
		game->map[game->msize.y] = ft_strdup(mapfile[i + game->msize.y]);
		if (game->msize.x < ft_slen(mapfile[game->msize.y]))
			game->msize.x = ft_slen(mapfile[game->msize.y]);
		game->msize.y++;
	}
	game->map[game->msize.y] = NULL;
	return (0);
}

/*
	Assign file to FD, error check
	Convert file to 2d array
	Convert xpm textures and floor/ceiling rgb to mlx values
	Copy map into seperate 2d array, error check

	Note: since using int i to keep track of where we've
	read until in the array, if a texture path is placed
	below the mapfile, 
*/
int	parse_mapfile( char *file, t_game *game )
{
	int		fd;
	char	**mapfile;
	char	**texs;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: File not found", 22));
	mapfile = cub_to_array(fd);
	if (!mapfile)
		return (write(2, "Error: Failed to open", 22));
	close(fd);
	game->paths = malloc(sizeof(char *) * 7);
	texs = ft_split("NO ,SO ,WE ,EA ,F ,C ", ',');
	i = parse_textures(mapfile, texs, game);
	free(game->foundtex);
	free_tab(texs);
	if (i == 0)
		return (write(2, "Error: Incorrect path format", 28));
	if (parse_map(mapfile + i, game))
		return (1);
	free_tab(mapfile);
	return (0);
}
