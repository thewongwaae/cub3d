#include "cub3d.h"

static void	render_bg( t_game *game, int colour )
{
	int i;
	int j;

	i = 0;
	while (i < game->winsize.y)
	{
		j = 0;
		while (j < game->winsize.x)
			my_pp(game->bg, j++, i, colour);
		i++;
	}
}

static void	render_map_grid( t_game *game )
{
	int	h;
	int	w;

	h = 0;
	w = 0;
	while (h < game->msize.y)
	{
		w = 0;
		while (w < ft_slen(game->map[h]))
		{
			if (game->map[h][w] == '1')
				render_cell(game->mmap, WHITE,
						h*CELL_SIZE, w*CELL_SIZE);
			else if (game->map[h][w] == '0')
				render_cell(game->mmap, BLACK,
						h*CELL_SIZE, w*CELL_SIZE);
			w++;
		}
		h++;
	}
}

static void	render_player( t_game *game )
{
	int	i;
	int	j;
	
	i = 0;
	while (i < game->msize.y*CELL_SIZE)
	{
		j = 0;
		while (j < game->msize.x*CELL_SIZE)
			my_pp(game->p.img, j++, i, TRANS);
		i++;
	}
	i = game->p.pix_y;
	while (i < (game->p.pix_y + game->p.size))
	{
		j = game->p.pix_x;
		while (j < (game->p.pix_x + game->p.size))
			my_pp(game->p.img, j++, i, PLAYER);
		i++;
	}
}

int	render( t_game *game )
{
	render_bg(game, GREY);
	mlx_put_image_to_window(game->mlx, game->win,
			game->bg.mlx_img, 0, 0);
	render_map_grid(game);
	mlx_put_image_to_window(game->mlx, game->win,
			game->mmap.mlx_img, 0, 0);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win,
			game->p.img.mlx_img, 0, 0);
	return (0);
}
