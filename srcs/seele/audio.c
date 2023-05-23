#include "cub3d.h"

static void	music_player( char *path, char *volume)
{
	execl("afplay", path, "-v", volume);
}

static void	play_audio( int type )
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (type == MUSIC)
			music_player("audio/space_walk.mp3", "1");
		// else if (type == ULT)
		// 	music_player("audio/seele_ult.mp3", "50");
	}
	wait_pid(pid, &status, 0);
}

static void	*audio( void *arg )
{
	t_audio *sound;
	
	sound = (t_audio *)arg;
	while (1)
	{
		if (sound->type == MUSIC)
			play_audio(sound->type);
		// if (sound->type == ULT && sound->play == true)
		// {
		// 	play_audio(sound->type);
		// 	sound->play = false;
		// }
	}
	return (NULL);
}

void	audio_init( t_game *g )
{
	int i;

	i = 0;
	while (i++ < 2)
	{
		g->audio[i].type = i + 1;
		g->audio[i].play = false;
		pthread_create(&g->audio[i].tid, NULL, audio, &g->audio[i]);
	}
}