#pragma once
#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

# define BUFFER_SIZE 1024

typedef struct s_texture
{
	// solid color fill in hex
	int 	floor_color;
	int 	ceil_color;
	// path to wall files
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_texture;

typedef struct s_game
{
	char		**map;
	void		*mlx;
}				t_game;

/* CUB3D */

/* PARSE */
char	**parse_map( char *file );

/* UTILS */
// GNL
char	*gnl(int fd);


#endif