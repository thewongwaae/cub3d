#pragma once
#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
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
char	*gnl( int fd );
// split
char	**ft_split( const char *str, char c );
// strings
int		ft_strlen( char *s );
char	*ft_strjoin( char *s1, char *s2 );
char	*ft_strdup( char *s );
char	*ft_strrchr( const char *s, int c );
int		ft_strcmp( const char *s1, const char *s2 );

#endif