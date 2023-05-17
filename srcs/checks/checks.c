/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:42 by hwong             #+#    #+#             */
/*   Updated: 2023/05/17 18:23:26 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Check whether a file's etension matches
	the given string
*/
static int	has_extension( char *file, char *ext )
{
	const char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot || dot == (file + ft_slen(file) - 1))
		return (0);
	if (!ft_strcmp(dot + 1, ext))
		return (1);
	return (0);
}

/*
	Runs all checks and returns verbose error
	messages

	Check for correct etension (.cub)
	Check whether file is accessible
	Check for map validity
		- Check if map fully enclosed
		- Check for player existance
*/
int	checks( char *file, t_game *game )
{
	if (!has_extension(file, "cub"))
		return (write(2, "Error: Invalid extension", 25));
	if (parse_mapfile(file, game))
		return (1);
	if (check_map(game) > 1)
		return (1);
	if (game->leak)
	{
		free_tab(game->map);
		return (write(2, "Error: Map leaks", 17));
	}
	if (!game->p.found)
		return (write(2, "Error: Player where", 20));
	return (0);
}
