/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:21:52 by nnorazma          #+#    #+#             */
/*   Updated: 2023/05/24 14:43:54 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	music_player( char *path, char *volume)
{
	execl("/usr/bin/afplay", "afplay", path, "-v", volume, NULL);
}

static void	play_audio( int type )
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (type == MUSIC)
			music_player("audio/space_walk.mp3", "0.5");
		else if (type == OPEN || type == CLOSE)
			music_player("audio/vine_boom.mp3", "1");
		else if (type == COLLIDE)
			music_player("audio/mgrr_alert.mp3", "1");
		exit(0);
	}
	waitpid(pid, &status, 0);
}

static void	*audio( void *arg )
{
	t_audio	*sound;

	sound = (t_audio *)arg;
	while (1)
	{
		if (sound->type == MUSIC)
			play_audio(sound->type);
		if ((sound->type == OPEN || sound->type == CLOSE
				|| sound->type == COLLIDE) && sound->play == true)
		{
			play_audio(sound->type);
			sound->play = false;
		}
	}
	return (NULL);
}

void	audio_init( t_game *g )
{
	int	i;

	i = 0;
	while (i < 4)
	{
		g->audio[i].type = i;
		g->audio[i].play = false;
		pthread_create(&g->audio[i].tid, NULL, audio, &g->audio[i]);
		i++;
	}
}
