#include "cub3d.h"

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

static void	render_map_grid( t_game *game )
{
	int	h;
	int	w;

	render_bg(game->mmap,game->msize.y*CELL_SIZE,
			game->msize.x*CELL_SIZE,TRANS);
	h = 0;
	while (h < game->msize.y)
	{
		w = 0;
		while (w < ft_slen(game->map[h]))
		{
			if (game->map[h][w] == '1')
				render_cell(game->mmap, WHITE,
						h*CELL_SIZE, w*CELL_SIZE);
			else if (is_walkable(game->map[h][w]))
				render_cell(game->mmap, BLACK,
						h*CELL_SIZE, w*CELL_SIZE);
			w++;
		}
		h++;
	}
}

static void	player_line( t_vec p1, t_game *game, int len, int color )
{
	t_vec	p2;

	p2.x = p1.x + len * cos(game->p.pa);
	p2.y = p1.y - len * sin(game->p.pa);
	draw_line(p1, p2, game->p.img, color);
}

static void	render_player( t_game *game )
{
	int		i;
	int		j;
	t_vec	player_pos;
	
	render_bg(game->p.img,game->msize.y*CELL_SIZE,
			game->msize.x*CELL_SIZE,TRANS);
	i = game->p.pix_y;
	while (i < (game->p.pix_y + game->p.size))
	{
		j = game->p.pix_x;
		while (j < (game->p.pix_x + game->p.size))
			my_pp(game->p.img, j++, i, PLAYER);
		i++;
	}
	player_pos.x = game->p.pix_x + game->p.size/2;
	player_pos.y = game->p.pix_y + game->p.size/2;
	player_line(player_pos, game, 15, PLAYER);
}

int	render( t_game *game )
{
	render_bg(game->bg,game->winsize.y,game->winsize.x,GREY);
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
