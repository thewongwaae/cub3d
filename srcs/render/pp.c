#include "cub3d.h"

/*
	Rewrite of mlx_pixel_put such that it draws to
	an image instead of directly onto the windoww
*/
void	my_pp( t_img img, int x, int y, int colour )
{
	char	*pixel;
	int		i;

	i = img.bpp - 8;
	pixel = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(int *)pixel = colour;
	while (i >= 0)
	{
		if (img.endian != 0)
			*pixel++ = (colour >> i) & 0xFF;
		else
			*pixel++ = (colour >> (img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

/*
	Render a square from specified start pixel
*/
void	render_cell( t_img img, int color, int h_pixel, int w_pixel )
{
	int	i;
	int	j;

	i = h_pixel;
	while (i < (h_pixel + CELL_SIZE - 1))
	{
		j = w_pixel;
		while (j < (w_pixel + CELL_SIZE - 1))
			my_pp(img, j++, i, color);
		i++;
	}
}
