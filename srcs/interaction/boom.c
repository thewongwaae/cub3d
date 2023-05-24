/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:21:37 by nnorazma          #+#    #+#             */
/*   Updated: 2023/05/24 14:41:37 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	boom( t_game *g )
{
	int	i;

	i = 0;
	while (i++ < 5)
		mlx_put_image_to_window(g->mlx, g->win, g->tex->rock.mlx_img, 0, 0);
	g->boom = false;
}
