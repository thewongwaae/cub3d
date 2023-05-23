/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seele_ult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:25:58 by nnorazma          #+#    #+#             */
/*   Updated: 2023/05/23 15:46:40 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	seele_init( t_game *g )
{
	char	*seele;
	int		i;
	int		x;
	int		y;
	
	i = -1;
	while (++i < 119 && (i % 3 == 0))
	{
		seele = ft_strjoin("frames/seele_", ft_itoa(i));
		seele = ft_strjoin(seele, "-resized.xpm");
		g->seele[i] = mlx_xpm_file_to_image(g->mlx, seele, &x, &y);
		free(seele);
	}
}

void	seele_ult( t_game *g )
{
	int	i;

	i = -1;
	while (++i < 40)
		mlx_put_image_to_window(g->mlx, g->win, g->seele[i], 0, 0);
	g->seele_ani = false;
}