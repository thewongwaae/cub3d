/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:56 by hwong             #+#    #+#             */
/*   Updated: 2023/05/24 14:42:02 by nnorazma         ###   ########.fr       */
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
static void	game_init( t_game *g )
{
	g->foundtex = (int *) malloc (sizeof(int) * 7);
	ft_memset(g->foundtex, 0, 7);
	g->tex = malloc (sizeof(t_texture));
	g->p.found = 0;
	g->p.map_pos.y = 0;
	g->p.map_pos.x = 0;
	g->p.dir = 0;
	g->p.size = 4;
	g->leak = false;
	g->msize.y = 0;
	g->msize.x = 0;
	g->fovdeg = 60;
	g->key.up = false;
	g->key.left = false;
	g->key.down = false;
	g->key.right = false;
	g->sens = 0.1;
	g->door.met = false;
	g->moved = true;
	g->boom = false;
}

/*
	Initialise mlx variables needed to start-up window
	Initialise main game mlx variables
	Initialise minimap mlx variables
*/
static void	init_mlx( t_game *g )
{
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WINSIZE_X,
			WINSIZE_Y, "cub3D");
	g->bg.mlx_img = mlx_new_image(g->mlx,
			WINSIZE_X, WINSIZE_Y);
	g->bg.addr = mlx_get_data_addr(g->bg.mlx_img,
			&g->bg.bpp, &g->bg.line_len, &g->bg.endian);
	g->mmap.mlx_img = mlx_new_image(g->mlx,
			g->msize.x * CELL_SIZE, g->msize.y * CELL_SIZE);
	g->mmap.addr = mlx_get_data_addr(g->mmap.mlx_img,
			&g->mmap.bpp, &g->mmap.line_len, &g->mmap.endian);
}

/*
	Set initial player direction based on
	the character ( N | S | W | E ) in the map
*/
static t_vecd	set_dir( char ch )
{
	if (ch == 'N')
		return ((t_vecd){0, -1});
	if (ch == 'S')
		return ((t_vecd){0, 1});
	if (ch == 'W')
		return ((t_vecd){-1, 0});
	else
		return ((t_vecd){1, 0});
}

/*
	Initialise player variables needed for movement
	and render calculations
	Initialise player mlx variables
*/
static void	player_init( t_game *g )
{
	int	cell_x;
	int	cell_y;

	cell_x = g->p.map_pos.x * CELL_SIZE;
	cell_y = g->p.map_pos.y * CELL_SIZE;
	g->p.pix.x = get_center(cell_x, cell_x + CELL_SIZE);
	g->p.pix.y = get_center(cell_y, cell_y + CELL_SIZE);
	g->p.pdir = set_dir(g->p.dir);
	g->p.plane.x = g->p.pdir.y;
	g->p.plane.y = -g->p.pdir.x;
	g->p.img.mlx_img = mlx_new_image(g->mlx,
			g->msize.x * CELL_SIZE, g->msize.y * CELL_SIZE);
	g->p.img.addr = mlx_get_data_addr(g->p.img.mlx_img,
			&g->p.img.bpp, &g->p.img.line_len, &g->p.img.endian);
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
	audio_init(&game);
	if (load_textures(&game))
		return (write(2, ": Invalid texture\n", 18));
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
