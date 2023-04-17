/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:51 by hwong             #+#    #+#             */
/*   Updated: 2023/04/17 13:33:01 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	forward( t_game *game )
{
	game->p.pix_x += game->p.pdx;
	game->p.pix_y += game->p.pdy;
}

static void	backward( t_game *game )
{
	game->p.pix_x -= game->p.pdx;
	game->p.pix_y -= game->p.pdy;
}

static void	left( t_game *game )
{
	game->p.pa += 0.3;
	if (game->p.pa < 0)
		game->p.pa += 2 * M_PI;
	game->p.pdx = cos(game->p.pa) * 5;
	game->p.pdy = -sin(game->p.pa) * 5;
}

static void	right( t_game *game )
{
	game->p.pa -= 0.3;
	if (game->p.pa > 2 * M_PI)
		game->p.pa -= 2 * M_PI;
	game->p.pdx = cos(game->p.pa) * 5;
	game->p.pdy = -sin(game->p.pa) * 5;
}

int	move( int keycode, t_game *game )
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
