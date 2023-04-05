#include "cub3d.h"

int	main( int ac, char **av )
{
	if (ac != 2)
		return (write(2, "Error: Invalid arguments\n", 25));
	if (!check_file(av[1]))
		return (write(2, ": Invalid map file\n", 24));
	// parse map
	// hook inputs
	// mlx loop
	return (0);
}
