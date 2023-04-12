#include <stdlib.h>
#include <stdio.h>

#include <mlx.h>

#define WIN_W 1920
#define WIN_H 1080
#define CELL_SIZE 150
#define PLAYER_SIZE 5

#define MLX_ERROR 1

#define WHITE 0XFFFFFF
#define GREY 0XA6A6A6
#define BLACK 0X000000
#define PLAYER 0XF9A3FF

int map[5][5] =
{
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 1, 1, 1, 1}
};

typedef struct s_img {
	void *mlx_img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
}	t_img;

typedef struct s_player {
	int pos_x; //in map
	int pos_y; //in map
}	t_player;

typedef struct s_data {
	void *mlx_ptr;
	void *win_ptr;
	t_img img;
	t_player player;
}	t_data;

typedef struct s_rect {
	int x;
	int y;
	int width;
	int height;
	int colour;
}	t_rect;

void my_pp(t_img *img, int x, int y, int colour)
{
	char *pixel;
	int i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = colour;

	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (colour >> i) & 0xFF;
		else
			*pixel++ = (colour >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void render_bg(t_img *img, int colour)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
			my_pp(img, j++, i, colour);
		i++;
	}
}

//for every cell in the map, render 100x100
void render_cell(t_img *img, int colour, int h_pix, int w_pix)
{
	int i, j;

	i = h_pix;
	while (i < (h_pix + CELL_SIZE - 1))
	{
		j = w_pix;
		while (j < (w_pix + CELL_SIZE - 1))
			my_pp(img, j++, i, colour);
		i++;
	}
}

//replace h and w comparisons to map sizes
void render_map_grid(t_img *img)
{
	for (int h = 0; h < 5; h++)
	{
		for (int w = 0; w < 5; w++)
		{
			if (map[h][w] == 1)
				render_cell(img, WHITE, h * CELL_SIZE, w * CELL_SIZE);
			else if (map[h][w] == 0)
				render_cell(img, BLACK, h * CELL_SIZE, w * CELL_SIZE);
		}
	}
}

int calculate_center(int start, int end)
{
	int center;

	center = end - ((end - start) / 2);
	return (center);
}

//we initialise inside here for now
void render_player(t_data *data)
{
	int i, j;
	data->player.pos_x = 1; //coords in map (index x)
	data->player.pos_y = 3; //index y

	int center_x, center_y;
	center_x = calculate_center(data->player.pos_x * CELL_SIZE, (data->player.pos_x + 1) * CELL_SIZE) - 2;
	center_y = calculate_center(data->player.pos_y * CELL_SIZE, (data->player.pos_y + 1) * CELL_SIZE) - 2;

	i = center_y;
	while (i < (center_y + PLAYER_SIZE))
	{
		j = center_x;
		while (j < (center_x + PLAYER_SIZE))
			my_pp(&data->img, j++, i, PLAYER);
		i++;
	}
}

int render(t_data *data)
{
	render_bg(&data->img, GREY);
	render_map_grid(&data->img);
	render_player(data);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "TEST CUB3D");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);

	free(data.mlx_ptr);
}