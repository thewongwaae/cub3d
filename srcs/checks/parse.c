/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:14 by hwong             #+#    #+#             */
/*   Updated: 2023/04/08 01:17:27 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**cub_to_array( int fd )
{
	char	*read;
	char	*buff;
	char	**res;

	read = gnl(fd);
	buff = ft_strdup("");
	while (read)
	{
		buff = ft_strjoin(buff, read);
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
	printf("In parse_textures\n");
	while (ft_strncmp(mapfile[j], "C ", 2))
	{
		printf("%s\n", mapfile[j]);
		// if (mapfile[j][0] == '\n')
		// 	continue ;
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
	//ft_free(space);
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
	while (mapfile[i + game->mapsize.y])
	{
		game->map[game->mapsize.y] = ft_strdup(mapfile[i + game->mapsize.y]);
		game->mapsize.y++;
	}
	game->map[game->mapsize.y] = NULL;
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
	int		j;

	i = 0;
	j = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: File not found", 22));
	mapfile = cub_to_array(fd);
	while (mapfile[j])
	{
		printf("%s\n", mapfile[j]);
		j++;
	}
	close(fd);
	game->paths = malloc(sizeof(char *) * 7);
	parse_textures(mapfile, &i, game);
	j = 0;
	printf("Showing saved paths and colors:\n");
	while (game->paths[j])
	{
		printf("%s\n", game->paths[j]);
		j++;
	}
	free_tab(game->paths);
	if (parse_map(&mapfile[i], game))
		return (1);
	free_tab(mapfile);
	j = 0;
	printf("Showing saved map:\n");
	while (game->map[j])
	{
		printf("%s\n", game->map[j]);
		j++;
	}
	return (0);
}
