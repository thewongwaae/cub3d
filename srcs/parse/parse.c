/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:05:04 by hwong             #+#    #+#             */
/*   Updated: 2023/03/23 19:11:27 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**parse_map( char *file )
{
	char	*line;
	char	*out;
	int		fd;

	line = NULL;
	out = ft_strdup(line);
	fd = open(file, O_RDONLY);
	line = gnl(fd);
	while (line)
	{
		if (line == NULL || line[0] == '\n')
			break ;
		
	}
}
