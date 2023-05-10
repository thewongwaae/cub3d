#include <mlx.h>
#include <stdio.h>

int main( int ac, char **av )
{
	void *mlx;
	void *win;
	void *image;
	int x, y;

	(void)ac;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 600, 600, "pain");
	image = mlx_xpm_file_to_image(mlx, av[1], &x, &y);
	mlx_put_image_to_window(mlx, win, image, 0, 0);
	mlx_loop(mlx);
	return 0;
}