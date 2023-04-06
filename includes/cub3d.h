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

typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;

typedef struct s_texture
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int 	floor;
	int 	ceiling;
}	t_texture;

typedef struct s_game
{
	char		**map;
	void		*mlx;
	void		*win;
	t_vec		size;
	char		**paths;
	t_texture	*tex;
}				t_game;

/* CUB3D */

/* PARSE */
int		checks( char *file, t_game *game );
char	**parse_mapfile( char *file, t_game *game );
void	load_textures( t_game *game );
int		check_map( t_game *game );

/* UTILS */
// free
void	ft_free( char *var );
void	free_tab( char **tab );
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
int 	is_space( char c );
int		is_digit( char c );
int		ft_atoi( const char *s );
char	*ft_strtok( char *s, char sep );

#endif