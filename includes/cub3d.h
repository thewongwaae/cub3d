/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:37:23 by hwong             #+#    #+#             */
/*   Updated: 2023/05/11 13:12:59 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "../mlx/mlx.h"

# define BUFFER_SIZE 1024
# define TRANS 0XFF000000
# define WHITE 0XFFFFFF
# define GREY 0XA6A6A6
# define GREEN 0X90EE90
# define PURPLE 0X48185C
# define BLUE 0XADD8E6
# define BLACK 0X000000
# define PLAYER 0XF9A3FF
# define CELL_SIZE 30

typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;

typedef struct s_vecd
{
	double	x;
	double	y;
}	t_vecd;

/* Iterative flood */
typedef struct s_queue_node
{
	t_vec				val;
	struct s_queue_node	*next;
}	t_queue_node;

typedef struct s_queue
{
	t_queue_node	*head;
	t_queue_node	*tail;
}	t_queue;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
}	t_img;

typedef struct s_texture
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_player
{
	bool	found;
	int		x;
	int		y;
	char	dir;
	int		size;

	double	pix_x;
	double	pix_y;
	double	pa;
	double	pdx;
	double	pdy;
	double	dist;
	t_vec	its;

	t_img	img;
}	t_player;

typedef struct s_keys
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_game
{
	char		**map;
	void		*mlx;
	void		*win;
	t_vec		winsize;
	t_img		bg;
	t_img		mmap;
	t_vec		msize;
	bool		leak;
	char		**paths;
	int			*foundtex;
	t_texture	*tex;
	t_player	p;
	int			fovdeg;
	t_keys		key;
	double		sens;
	bool		moved;
}				t_game;

/* CHECKS AND PARSE */
int		checks( char *file, t_game *game );
int		parse_mapfile( char *file, t_game *game );
void	check_map( t_game *g );
int		all_found( int *found );
/* ITERATIVE FLOOD */
t_queue	*init_queue( void );
int		is_q_empty( t_queue *q );
void	enqueue( t_queue *q, t_vec val );
t_vec	dequeue( t_queue *q );
void	free_queue( t_queue *q );

/* HOOKS */
void	forward( t_game *game );
void	backward( t_game *game );
void	left( t_game *game );
void	right( t_game *game );
void	open_door( t_game *g );
int		key_down( int keycode, t_game *game );
int		key_up( int keycode, t_game *game );
int		mouse_hook( int x, int y, t_game *game );

/* RENDER */
void	load_textures( t_game *game );
void	my_pp( t_img img, int x, int y, int colour );
void	render_cell( t_img img, int color, int h_pixel, int w_pixel );
t_vecd	get_intersect( t_game *g, double angle );
void	raycast( t_vecd player, t_game *game, int color );
double	get_dist( t_vecd p1, t_vecd p2 );
void	render_minimap( t_game *game );
int		render( t_game *game );
void	cast_3d(t_game *g, double dist, int r, double angle);

/* UTILS */
// free
void	ft_free( char *var );
void	free_tab( char **tab );
int		endgame( t_game *game );
// GNL
char	*gnl( int fd );
// split
char	**ft_split( const char *str, char c );
// strings
int		ft_slen( char *s );
char	*ft_strjoin( char *s1, char *s2 );
char	*ft_strdup( char *s );
char	*ft_strchr( const char *s, int c );
char	*ft_strrchr( const char *s, int c );
int		ft_strcmp( const char *s1, const char *s2 );
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		is_space( char c );
int		is_digit( char c );
int		ft_atoi( const char *s );
char	*ft_strtok(char *str, const char *delim);
void	ft_bzero( void *str, size_t n );
void	*ft_calloc( size_t nitems, size_t size );
void	*ft_memset( void *s, int c, size_t n );
void	*ft_memcpy(void *str1, const void *str2, size_t n);
int		ismapchar( int ch );

// utils
int		is_walkable( char ch );
int		is_in_wall( t_game *game, int x, int y );
double	get_center( int start, int end );
double	deg_to_rad( int angle );

#endif