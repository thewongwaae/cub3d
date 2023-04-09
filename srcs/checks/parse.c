/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:14 by hwong             #+#    #+#             */
/*   Updated: 2023/04/09 11:58:12 by hwong            ###   ########.fr       */
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

static void	parse_textures( char **mapfile, int *i, t_game *game )
{
	int		j;
	int		k;
	char	*space;

	j = 0;
	k = 0;
	while (ft_strncmp(mapfile[j], "C ", 2))
	{
		space = ft_strchr(mapfile[j], ' ');
		if (space)
		{
			game->paths[k] = ft_strdup(space + 1);
			(*i)++;
			k++;
		}
		j++;
	}
	game->paths[k] = ft_strdup(&mapfile[j][2]);
	(*i)++;
	game->paths[k + 1] = NULL;
	//load_textures(game);
}

static int	parse_map( char **mapfile, t_game *game )
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mapfile[i][0] == '\n')
		i++;
	while (mapfile[i + j])
	{
		if (mapfile[i + j][0] == '\n')
		{
			free_tab(mapfile);
			return (write(2, "Error: Newline in map", 22));
		}
		j++;
	}
	game->map = malloc(sizeof(char *) * (j + 1));
	while (mapfile[i + game->msize.y])
	{
		game->map[game->msize.y] = ft_strdup(mapfile[i + game->msize.y]);
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
*/
int	parse_mapfile( char *file, t_game *game )
{
	int		fd;
	char	**mapfile;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: File not found", 22));
	mapfile = cub_to_array(fd);
	close(fd);
	game->paths = malloc(sizeof(char *) * 7);
	parse_textures(mapfile, &i, game);
	free_tab(game->paths);
	if (parse_map(&mapfile[i], game))
		return (1);
	free_tab(mapfile);
	return (0);
}
