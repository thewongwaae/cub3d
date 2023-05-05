#include "cub3d.h"

/*
	Moves player forward taking into consideration
	the current player angle
*/
void	forward( t_game *game )
{
	double new_px;
	double new_py;

	if (game->key.up == true)
	{
		new_px = game->p.pix_x + game->p.pdx;
		new_py = game->p.pix_y + game->p.pdy;
		if (!is_in_wall(game, new_px, new_py))
		{
			game->p.pix_x = new_px;
			game->p.pix_y = new_py;
			game->moved = true;
		}
	}
}

/*
	Moves player backward taking into consideration
	the current player angle
*/
void	backward( t_game *game )
{
	double new_px;
	double new_py;

	if (game->key.down == true)
	{
		new_px = game->p.pix_x - game->p.pdx;
		new_py = game->p.pix_y - game->p.pdy;
		if (!is_in_wall(game, new_px, new_py))
		{
			game->p.pix_x = new_px;
			game->p.pix_y = new_py;
			game->moved = true;
		}
	}
}

/*
	Changes the player angle anti-clockwise
	and recalculates pdx and pdy for
	forwawrd/backward movement
*/
void	left( t_game *game )
{
	if (game->key.left == true)
	{
		game->p.pa -= game->sens;
		if (game->p.pa < 0)
			game->p.pa += 2 * M_PI;
		game->p.pdx = cos(game->p.pa) * 2.5;
		game->p.pdy = -sin(game->p.pa) * 2.5;
		game->moved = true;
	}
}

/*
	Changes the player angle clockwise
	and recalculates pdx and pdy for
	forwawrd/backward movement
*/
void	right( t_game *game )
{
	if (game->key.right == true)
	{
		game->p.pa += game->sens;
		if (game->p.pa > 2 * M_PI)
			game->p.pa -= 2 * M_PI;
		game->p.pdx = cos(game->p.pa) * 2.5;
		game->p.pdy = -sin(game->p.pa) * 2.5;
		game->moved = true;
	}
}
