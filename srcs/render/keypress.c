/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:51 by hwong             #+#    #+#             */
/*   Updated: 2023/04/17 10:55:29 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	forward( t_game *game )
{
	printf("up\n");
	game->p.pix_y -= 10;
}

static void	left( t_game *game )
{
	printf("left\n");
	game->p.pix_x -= 10;
}

static void	backward( t_game *game )
{
	game->p.pix_y += 10;
	printf("down\n");
}

static void	right( t_game *game )
{
	game->p.pix_x += 10;
	printf("right\n");
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
