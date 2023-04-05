#include "cub3d.h"

static char	**cub_to_array( int fd )
{
	char	*read;
	char	*buff;

	read = gnl(fd);
	while (read)
	{
		buff = ft_strjoin(buff, read);
		read = gnl(fd);
	}
	return (ft_split(buff, '\n'));
}

static void	parse_textures( char **mapfile, t_game *game )
{
	int		i;
	int		j;
	char	*space;
	
	i = 0;
	j = 0;
	while (ft_strcmp(mapfile[i], "C "))
	{
		if (mapfile[i][0] == '\n')
			continue ;
		space = ft_strchr(mapfile[i], ' ');
		if (space)
		{
			ft_strcpy(game->texpaths[j], space + 1);
			j++;
		}
		i++;
	}
	if (space)
		free(space);
	load_textures(game);
}

char	**parse_mapfile( char *file, t_game *game )
{
	int		fd;
	char	**mapfile;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: File not found", 22));
	mapfile = cub_to_array(fd);
	parse_textures(mapfile, game);
}

// check map validity