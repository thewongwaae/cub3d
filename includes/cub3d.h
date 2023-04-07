#pragma once
#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
// # include <mlx.h>

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
	t_vec		winsize;
	t_vec		mapsize;
	int			leak;
	char		**paths;
	t_texture	*tex;
	t_vec		player;
}				t_game;

/* CHECKS AND PARSE */
int		checks( char *file, t_game *game );
int		parse_mapfile( char *file, t_game *game );
void	check_map( t_game *game );

/* RENDER */
// void	load_textures( t_game *game );

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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	is_space( char c );
int		is_digit( char c );
int		ft_atoi( const char *s );
char	*ft_strtok( char *s, char sep );
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t nitems, size_t size);


#endif