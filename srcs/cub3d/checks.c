#include "cub3d.h"

static int	has_extension( const char *file, const char *ext )
{
	const char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot || dot == (file + ft_strlen(file) - 1))
		return (0);
	if (!ft_strcmp(dot + 1, ext))
		return (1);
	return (0);
}

int	checks( char *file, t_game *game )
{
	if (!has_extension(file, "cub"))
		return (write(2, "Error: Invalid extension", 25));
	if (!parse_mapfile(file, game))
		return (write(2, "Error: Invalid file", 22));
	check_map(game);
	if (!game->leak)
		return (write(2, "Error: Map invalid", 19));
	return (0);
}
