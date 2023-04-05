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
	// path to wall files
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	// solid color fill in hex
	int 	floor;
	int 	ceiling;
}	t_texture;

typedef struct s_game
{
	char		**map;
	void		*mlx;
	void		*win;
	char		**texpaths;
	t_texture	*texture;
}				t_game;

/* CUB3D */

/* PARSE */
char	**parse_mapfile( char *file, t_game *game );

/* UTILS */
// GNL
char	*gnl( int fd );
// split
char	**ft_split( const char *str, char c );
// strings
int		ft_strlen( char *s );
char	*ft_strjoin( char *s1, char *s2 );
char	*ft_strdup( char *s );
char	*ft_strchr( const char *s, int c );
char	*ft_strrchr( const char *s, int c );
int		ft_strcmp( const char *s1, const char *s2 );
int		is_space( char c );
char	*ft_strcpy( char *dst, const char *src );

#endif