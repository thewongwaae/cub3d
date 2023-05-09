/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:56 by hwong             #+#    #+#             */
/*   Updated: 2023/05/09 17:20:39 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Initialise values needed for game start-up
	Initialise all player variables needed in
	map verification
	Intialisie render values and movement keys
	
	Note: 'moved' variable is to lower refreshes by
	only rendering when the player has moved
*/
static void	game_init( t_game *game )
{
	game->winsize.x = 1600;
	game->winsize.y = 900;
	game->foundtex = (int *) malloc (sizeof(int) * 7);
	ft_memset(game->foundtex, 0, 7);
	// game->tex = malloc (sizeof(t_texture));
	game->p.found = false;
	game->p.y = 0;
	game->p.x = 0;
	game->p.dir = 0;
	game->p.size = 4;
	game->leak = false;
	game->msize.y = 0;
	game->msize.x = 0;
	game->fovdeg = 60;
	game->key.up = false;
	game->key.left = false;
	game->key.down = false;
	game->key.right = false;
	game->sens = 0.1;
	game->moved = true;
}

/*
	Initialise mlx variables needed to start-up window
	Initialise main game mlx variables
	Initialise minimap mlx variables
*/
static void	init_mlx( t_game *game )
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->winsize.x,
			game->winsize.y, "cub3D");
	game->bg.mlx_img = mlx_new_image(game->mlx,
			game->winsize.x, game->winsize.y);
	game->bg.addr = mlx_get_data_addr(game->bg.mlx_img,
			&game->bg.bpp, &game->bg.line_len, &game->bg.endian);
	game->mmap.mlx_img = mlx_new_image(game->mlx,
			game->msize.x * CELL_SIZE, game->msize.y * CELL_SIZE);
	game->mmap.addr = mlx_get_data_addr(game->mmap.mlx_img,
			&game->mmap.bpp, &game->mmap.line_len, &game->mmap.endian);
}

/*
	Set initial player direction based on
	the character ( N | S | W | E ) in the map
*/
static double	set_dir( char ch )
{
	if (ch == 'N')
		return (M_PI / 2.0);
	if (ch == 'S')
		return (3 * M_PI / 2.0);
	if (ch == 'W')
		return (M_PI);
	return (0);
}

/*
	Initialise player variables needed for movement
	and render calculations
	Initialise player mlx variables
*/
static void	player_init( t_game *game )
{
	int	cell_x;
	int	cell_y;

	cell_x = game->p.x * CELL_SIZE;
	cell_y = game->p.y * CELL_SIZE;
	game->p.pix_x = get_center(cell_x, cell_x + CELL_SIZE);
	game->p.pix_y = get_center(cell_y, cell_y + CELL_SIZE);
	game->p.img.mlx_img = mlx_new_image(game->mlx,
			game->msize.x * CELL_SIZE, game->msize.y * CELL_SIZE);
	game->p.img.addr = mlx_get_data_addr(game->p.img.mlx_img,
			&game->p.img.bpp, &game->p.img.line_len, &game->p.img.endian);
	game->p.pa = set_dir(game->p.dir);
	game->p.pdx = cos(game->p.pa);
	game->p.pdy = -sin(game->p.pa);
}

/*
	Initialise game variables
	Run map checks
	Initialise game mlx
	Initialise player varaibles
	Setup image for minimap
	Set neccesary game hooks
	Loop the render function
	Loop the game mlx
*/
int	main( int ac, char **av )
{
	t_game	game;

	if (ac != 2)
		return (write(2, "Error: Invalid arguments\n", 25));
	game_init(&game);
	if (checks(av[1], &game))
		return (write(2, ": Invalid file\n", 15));
	init_mlx(&game);
	player_init(&game);
	render_minimap(&game);
	mlx_hook(game.win, 2, (1L << 0), key_down, &game);
	mlx_hook(game.win, 3, (1L << 0), key_up, &game);
	mlx_hook(game.win, 6, (1L << 6), mouse_hook, &game);
	mlx_hook(game.win, 17, (1L << 17), endgame, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (0);
}
