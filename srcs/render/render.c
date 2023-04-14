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
			my_pp(game->img, j++, i, colour);
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
				render_cell(game->img, WHITE,
						h*CELL_SIZE, w*CELL_SIZE);
			else if (game->map[h][w] == '0')
				render_cell(game->img, BLACK,
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
	// int	center_x;
	// int	center_y;

	// center_x = get_center(game->p.x*CELL_SIZE,(game->p.x+1)*CELL_SIZE)-2;
	// center_y = get_center(game->p.y*CELL_SIZE,(game->p.y+1)*CELL_SIZE)-2;
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
	render_map_grid(game);
	mlx_put_image_to_window(game->mlx, game->win,
			game->img.mlx_img, 0, 0);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win,
			game->p.img.mlx_img, 0, 0);
	return (0);
}
