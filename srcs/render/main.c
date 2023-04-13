/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:56 by hwong             #+#    #+#             */
/*   Updated: 2023/04/13 16:04:39 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_init( t_game *game )
{
	game->p.cell_x = game->p.x * CELL_SIZE;
	game->p.cell_y = game->p.y * CELL_SIZE;
	game->p.pix_x = get_center(game->p.cell_x, game->p.cell_x + CELL_SIZE);
	game->p.pix_y = get_center(game->p.cell_y, game->p.cell_y + CELL_SIZE);
	game->p.img.mlx_img = mlx_new_image(game->mlx, game->p.size, game->p.size);
	game->p.img.addr = mlx_get_data_addr(game->p.img.mlx_img,
			&game->p.img.bpp, &game->p.img.line_len, &game->p.img.endian);
}

static void	game_init( t_game *game )
{
	game->winsize.x = 1920;
	game->winsize.y = 1080;
	game->foundtex = (int *) malloc (sizeof(int) * 7);
	ft_memset(game->foundtex, 0, 7);
	game->p.found = 0;
	game->p.y = 0;
	game->p.x = 0;
	game->p.dir = 0;	
	game->p.size = 5;
	game->leak = 0;
	game->msize.y = 0;
	game->msize.x = 0;
}

static void	init_mlx( t_game *game )
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->winsize.x,
			game->winsize.y, "cub3D");
	game->img.mlx_img = mlx_new_image(game->mlx,
			game->winsize.x, game->winsize.y);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
}

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
	// mlx_key_hook(game.win, move, &game);
	// mlx_hook(game.win, 17, (1L << 0), endgame, &game);
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop(game.mlx);
	//system("leaks cub3D");
	free_tab(game.map);
	free(game.mlx);
	return (0);
}
