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

static void	parse_textures( char **mapfile, int *i, t_game *game )
{
	int		j;
	int		k;
	char	*space;

	j = 0;
	k = 0;
	while (ft_strcmp(mapfile[j], "C "))
	{
		if (mapfile[j][0] == '\n')
			continue ;
		space = ft_strchr(mapfile[j], ' ');
		if (space)
		{
			game->paths[k] = ft_strdup(space + 1);
			(*i)++;
			k++;
		}
		j++;
	}
	game->paths[k] = ft_strdup(mapfile[j][2]);
	(*i)++;
	game->paths[k + 1] = NULL;
	ft_free(space);
	load_textures(game);
}

static void	parse_map( char **mapfile, t_game *game )
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
	game->map = malloc(sizeof(char *) * j + 1);
	j = 0;
	while (mapfile[i + j])
	{
		game->map[j] = ft_strdup(mapfile[i + j]);
		j++;
	}
	game->map[j] = NULL;
}

/*
	Assign file to FD, error check
	Convert file to 2d array
	Convert xpm textures and floor/ceiling rgb to mlx values
	Copy map into seperate 2d array, error check
*/
char	**parse_mapfile( char *file, t_game *game )
{
	int		fd;
	char	**mapfile;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: File not found", 22));
	mapfile = cub_to_array(fd);
	game->paths = malloc(sizeof(char *) * 7);
	parse_textures(mapfile, &i, game);
	parse_map(&mapfile[i], game);
}
