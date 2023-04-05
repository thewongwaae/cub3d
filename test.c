#include <stdlib.h>
#include <stdio.h>

#include <mlx.h>

#define WIN_W 1920
#define WIN_H 1080

#define MLX_ERROR 1

#define PINK 0XFFC0CB
#define B_BLUE 0X669AED
#define GREEN 0X1D8F24

typedef struct s_data {
	void *mlx_ptr;
	void *win_ptr;
}	t_data;

typedef struct s_rect {
	int x;
	int y;
	int width;
	int height;
	int colour;
}	t_rect;

int render_rect(t_data *data, t_rect rect)
{
	int i;
	int j;

	if (data->win_ptr == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.colour);
		i++;
	}
	return (0);
}

void render_bg(t_data *data, int colour)
{
	int i;
	int j;

	if (data->win_ptr == NULL)
		return ;
	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, colour);
		i++;
	}
}

int render(t_data *data)
{
	render_bg(data, B_BLUE);
	render_rect(data, (t_rect){600, 400, 300, 500, GREEN});
	render_rect(data, (t_rect){200, 100, 100, 100, PINK});
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

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);

	free(data.mlx_ptr);
}