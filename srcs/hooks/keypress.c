/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:51 by hwong             #+#    #+#             */
/*   Updated: 2023/04/19 22:10:58 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	forward( t_game *game )
{
	float new_px;
	float new_py;

	new_px = game->p.pix_x + game->p.pdx;
	new_py = game->p.pix_y + game->p.pdy;
	if (!is_in_wall(game, new_px, new_py))
	{
		game->p.pix_x = new_px;
		game->p.pix_y = new_py;
		game->moved = true;
	}
}

static void	backward( t_game *game )
{
	float new_px;
	float new_py;

	new_px = game->p.pix_x - game->p.pdx;
	new_py = game->p.pix_y - game->p.pdy;
	if (!is_in_wall(game, new_px, new_py))
	{
		game->p.pix_x = new_px;
		game->p.pix_y = new_py;
		game->moved = true;
	}
}

static void	left( t_game *game )
{
	game->p.pa += 0.1;
	if (game->p.pa < 0)
		game->p.pa += 2 * M_PI;
	game->p.pdx = cos(game->p.pa) * 3;
	game->p.pdy = -sin(game->p.pa) * 3;
	game->moved = true;
}

static void	right( t_game *game )
{
	game->p.pa -= 0.1;
	if (game->p.pa > 2 * M_PI)
		game->p.pa -= 2 * M_PI;
	game->p.pdx = cos(game->p.pa) * 3;
	game->p.pdy = -sin(game->p.pa) * 3;
	game->moved = true;
}

int	key_hook( int keycode, t_game *game )
{
	if (keycode == 13 || keycode == 126)
		forward(game);
	else if (keycode == 0 || keycode == 123)
		left(game);
	else if (keycode == 1 || keycode == 125)
		backward(game);
	else if (keycode == 2 || keycode == 124)
		right(game);
	if (keycode == 53 || keycode == 65307)
		endgame(game);
	return (0);
}
