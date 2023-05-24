/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:16:03 by hwong             #+#    #+#             */
/*   Updated: 2023/05/24 16:16:23 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Bit-shift an integer to store rgb value
*/
int	rgb_to_int( int r, int g, int b )
{
	int	color;

	color = 0;
	color |= (int)(b % 256);
	color |= (int)(g % 256) << 8;
	color |= (int)(r % 256) << 16;
	return (color);
}

static int	valid_rgb_string( const char *strrgb ) {
    int	comma;
	
	comma = 0;
    while (*strrgb)
	{
        if (*strrgb == ',')
            comma++;
		else if (!is_digit(*strrgb))
            return (0);
        strrgb++;
    }
    return (comma == 2);
}

/*
	Convert a string rgb value to an int array of 3
*/
static int	strrgb_to_rgba( const char *strrgb, int *rgba )
{
	char	*tkn;
	int		i;

	i = 0;
	if (!valid_rgb_string(strrgb))
		return (1);
	tkn = ft_strtok((char *)strrgb, ",");
	while (tkn)
	{
		rgba[i] = ft_atoi(tkn);
		if (rgba[i] < 0 || rgba[i] > 255)
			return (1);
		i++;
		tkn = ft_strtok(NULL, ",");
	}
	return (0);
}

int	set_color( t_game *g )
{
	int	*c;

	c = malloc(sizeof(int) * 3);
	if (strrgb_to_rgba(g->paths[4], c))
	{
		free(c);
		return (1);
	}
	g->tex->floor = rgb_to_int(c[0], c[1], c[2]);
	if (strrgb_to_rgba(g->paths[5], c))
	{
		free(c);
		return (1);
	}
	g->tex->ceiling = rgb_to_int(c[0], c[1], c[2]);
	return (0);
}
