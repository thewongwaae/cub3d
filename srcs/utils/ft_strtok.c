/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:00:17 by hwong             #+#    #+#             */
/*   Updated: 2023/05/06 17:04:01 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		*skip_delim(char *str, const char *delim)
{
	while (*str != '\0' && ft_strchr(delim, *str) != NULL)
		str++;
	return (str);
}

static char		*next_token(char *str, const char *delim)
{
	bool	is_delimiter;

	while (*str != '\0')
	{
		if (ft_strchr(delim, *str) != NULL)
    		is_delimiter = true;
		else
    		is_delimiter = false;
		if (is_delimiter)
		{
			*str = '\0';
			return (str + 1);
		}
		str++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token;
	char		*token;

	if (str == NULL)
	{
		str = last_token;
		if (str == NULL)
			return (NULL);
	}
	str = skip_delim(str, delim);
	if (*str == '\0')
	{
		last_token = NULL;
		return (NULL);
	}
	token = str;
	last_token = next_token(str, delim);
	return (token);
}
