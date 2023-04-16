/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:51 by hwong             #+#    #+#             */
/*   Updated: 2023/04/16 16:15:05 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move( int keycode, t_game *game )
{
	// if (keycode == 13 || keycode == 126)
	// 	forward();
	// else if (keycode == 0 || keycode == 123)
	// 	left();
	// else if (keycode == 1 || keycode == 125)
	// 	backward();
	// else if (keycode == 2 || keycode == 124)
	// 	right();
	if (keycode == 53)
		endgame(game);
	return (0);
}
