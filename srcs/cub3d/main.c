#include "cub3d.h"

int	main( int ac, char **av )
{
	t_game	game;

	if (ac != 2)
		return (write(2, "Error: Invalid arguments\n", 25));
	game.mlx = mlx_init();
	if (!checks(av[1], &game))
		return (write(2, ": Invalid map file\n", 24));
	game.win = mlx_new_window(game.mlx, 1920, 1080, "cub3D");
	// mlx_key_hook(game.win, move, &game);
	// mlx_hook(game.win, 17, (1L << 0), endgame, &game);
	// mlx_loop_hook(game.mlx, refresh, &game);
	mlx_loop(game.mlx);
	return (0);
}
