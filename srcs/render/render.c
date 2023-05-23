/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:14:42 by hwong             #+#    #+#             */
/*   Updated: 2023/05/23 13:13:36 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Draw a solid colour slate onto a specified mlx image
*/
static void	render_bg( t_img img, t_vec p1, t_vec p2, int color )
{
	int	i;
	int	j;

	i = p1.x;
	while (i < p2.x)
	{
		j = p1.y;
		while (j < p2.y)
			my_pp(img, j++, i, color);
		i++;
	}
}

/*
	Draw a square cell with colour based on
	it's char on the mapfile 
*/
static void	draw_cell( char ch, int h, int w, t_game *g )
{
	if (ch == '1')
		render_cell(g->mmap, PINK,
			h * CELL_SIZE, w * CELL_SIZE);
	else if (ch == '2')
		render_cell(g->mmap, GREEN,
			h * CELL_SIZE, w * CELL_SIZE);
	else if (ch == '3')
		render_cell(g->mmap, BLUE,
			h * CELL_SIZE, w * CELL_SIZE);
	else if (is_walkable(ch))
		render_cell(g->mmap, DARK_PURPLE,
			h * CELL_SIZE, w * CELL_SIZE);
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

	render_bg(game->mmap, (t_vec){0, 0}, (t_vec){game->msize.y * CELL_SIZE,
		game->msize.x * CELL_SIZE}, TRANS);
	h = 0;
	while (h < game->msize.y)
	{
		w = 0;
		while (w < ft_slen(game->map[h]))
		{
			draw_cell(game->map[h][w], h, w, game);
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
	double	i;
	double	j;

	render_bg(game->p.img, (t_vec){0, 0}, (t_vec){game->msize.y * CELL_SIZE,
		game->msize.x * CELL_SIZE}, TRANS);
	raycast(game);
	i = game->p.pix.y;
	while (i < (game->p.pix.y + game->p.size))
	{
		j = game->p.pix.x;
		while (j < (game->p.pix.x + game->p.size))
		{
			my_pp(game->p.img, (int)(j), (int)(i), YELLOW);
			j += 1.0;
		}
		i += 1.0;
	}
}

/*
	Modify player position based on input
	Re-draw and put images to the window
*/
int	render( t_game *g )
{
	forward(g);
	backward(g);
	left(g);
	right(g);
	if (g->moved == true)
	{
		render_bg(g->bg, (t_vec){0, 0}, (t_vec){WINSIZE_Y / 2, WINSIZE_X},
			g->tex->ceiling);
		render_bg(g->bg, (t_vec){WINSIZE_Y / 2, 0},
			(t_vec){WINSIZE_Y, WINSIZE_X}, g->tex->floor);
		render_player(g);
		mlx_put_image_to_window(g->mlx, g->win,
			g->bg.mlx_img, 0, 0);
		mlx_put_image_to_window(g->mlx, g->win,
			g->mmap.mlx_img, 0, 0);
		mlx_put_image_to_window(g->mlx, g->win,
			g->p.img.mlx_img, 0, 0);
		if (g->seele_ani == true)
			seele_ult(g);
		g->moved = false;
	}
	return (0);
}
