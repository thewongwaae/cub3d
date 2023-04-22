/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:51 by hwong             #+#    #+#             */
/*   Updated: 2023/04/22 16:55:55 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Changes fov value based on key-input
	15 <= fov >= 360
*/
static void	change_fov( int keycode, t_game *game )
{
	int	new_fov;

	if (keycode == 33)
	{
		new_fov = game->fovdeg - 1;
		if (new_fov > 14)
			game->fovdeg = new_fov;
	}
	else if (keycode == 30)
	{
		new_fov = game->fovdeg + 1;
		if (new_fov < 361)
			game->fovdeg = new_fov;
	}
	else if (keycode == 42)
		game->fovdeg = 60;
	game->moved = 1;
}

/*
	Changes turn sensitivity based on key-input
*/
static void	change_sens( int keycode, t_game *game )
{
	float	new_sens;

	if (keycode == 27)
	{
		new_sens = game->sens - 0.05;
		if (new_sens > 0.00001)
			game->sens = new_sens;
		printf("new sens: %f\n", new_sens);
	}
	else if (keycode == 24)
	{
		new_sens = game->sens + 0.05;
		if (new_sens < 1)
			game->sens = new_sens;
		printf("new sens: %f\n", new_sens);
	}
	else if (keycode == 51)
		game->sens = 0.1;
}

/*
	Triggered on keypress
	Sets corresponding key boolean to true
	Handle for end-game and exits
*/
int	key_down( int keycode, t_game *game )
{
	if (keycode == 13 || keycode == 126)
		game->key.up = true;
	else if (keycode == 0 || keycode == 123)
		game->key.left = true;
	else if (keycode == 1 || keycode == 125)
		game->key.down = true;
	else if (keycode == 2 || keycode == 124)
		game->key.right = true;
	if (keycode == 33 || keycode == 30 || keycode == 42)
		change_fov(keycode, game);
	if (keycode == 27 || keycode == 24 || keycode == 51)
		change_sens(keycode, game);
	if (keycode == 53 || keycode == 65307)
		endgame(game);
	return (0);
}

/*
	Triggered on keyrelease
	Sets corresponding key boolean to false
*/
int	key_up( int keycode, t_game *game )
{
	if (keycode == 13 || keycode == 126)
		game->key.up = false;
	else if (keycode == 0 || keycode == 123)
		game->key.left = false;
	else if (keycode == 1 || keycode == 125)
		game->key.down = false;
	else if (keycode == 2 || keycode == 124)
		game->key.right = false;
	return (0);
}
