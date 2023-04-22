/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:14:42 by hwong             #+#    #+#             */
/*   Updated: 2023/04/22 17:46:16 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Draw a solid colour slate onto a specified mlx image
*/
static void	render_bg( t_img img, int h, int w, int color )
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
			my_pp(img, j++, i, color);
		i++;
	}
}

/*
	Render transparent background
	Render minimap based on the 2D map array in
	the game struct
*/
void	render_minimap( t_game *game )
{
	int	h;
	int	w;

	render_bg(game->mmap, game->msize.y * CELL_SIZE,
		game->msize.x * CELL_SIZE, TRANS);
	h = 0;
	while (h < game->msize.y)
	{
		w = 0;
		while (w < ft_slen(game->map[h]))
		{
			if (game->map[h][w] == '1')
				render_cell(game->mmap, WHITE,
					h * CELL_SIZE, w * CELL_SIZE);
			if (game->map[h][w] == '2')
				render_cell(game->mmap, GREEN,
					h * CELL_SIZE, w * CELL_SIZE);
			else if (is_walkable(game->map[h][w]))
				render_cell(game->mmap, BLACK,
					h * CELL_SIZE, w * CELL_SIZE);
			w++;
		}
		h++;
	}
}

/*
	Render transparent background
	Render raycast
	Render a small dot representing the player
*/
static void	render_player( t_game *game )
{
	int		i;
	int		j;
	t_vec	player;

	render_bg(game->p.img, game->msize.y * CELL_SIZE,
		game->msize.x * CELL_SIZE, TRANS);
	player.x = game->p.pix_x + game->p.size / 2;
	player.y = game->p.pix_y + game->p.size / 2;
	raycast(player, game, GREEN);
	i = game->p.pix_y;
	while (i < (game->p.pix_y + game->p.size))
	{
		j = game->p.pix_x;
		while (j < (game->p.pix_x + game->p.size))
			my_pp(game->p.img, j++, i, PLAYER);
		i++;
	}
}

/*
	Modify player position based on input
	Re-draw and put images to the window
*/
int	render( t_game *game )
{
	static int	refresh;

	forward(game);
	backward(game);
	left(game);
	right(game);
	if (refresh == 0 || game->moved != 0)
	{
		render_bg(game->bg, game->winsize.y, game->winsize.x, GREY);
		render_player(game);
		mlx_put_image_to_window(game->mlx, game->win,
			game->bg.mlx_img, 0, 0);
		mlx_put_image_to_window(game->mlx, game->win,
			game->mmap.mlx_img, 0, 0);
		mlx_put_image_to_window(game->mlx, game->win,
			game->p.img.mlx_img, 0, 0);
		game->moved = false;
	}
	refresh++;
	return (0);
}
