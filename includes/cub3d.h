/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:37:23 by hwong             #+#    #+#             */
/*   Updated: 2023/04/13 15:59:34 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>

# define BUFFER_SIZE 1024
# define WHITE 0XFFFFFF
# define GREY 0XA6A6A6
# define BLACK 0X000000
# define PLAYER 0XF9A3FF
# define CELL_SIZE 100

typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;

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
}	t_img;

typedef struct s_texture
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_player
{
	int		found;
	int		x;
	int		y;
	char	dir;
	int		size;

	int		cell_x; //cell pixel position
	int		cell_y; 
	int		pix_x; //top left player pixel
	int		pix_y;
	t_img	img;
}	t_player;

typedef struct s_game
{
	char		**map;
	void		*mlx;
	void		*win;
	t_vec		winsize;
	t_img		img;
	t_vec		msize;
	int			leak;
	char		**paths;
	int			*foundtex;
	t_texture	*tex;
	t_player	p;
}				t_game;

/* CHECKS AND PARSE */
int		checks( char *file, t_game *game );
int		parse_mapfile( char *file, t_game *game );
void	check_map( t_game *g );
/* ITERATIVE FLOOD */
t_queue	*init_queue( void );
int		is_q_empty( t_queue *q );
void	enqueue( t_queue *q, t_vec val );
t_vec	dequeue( t_queue *q );
void	free_queue( t_queue *q );

/* RENDER */
// void	load_textures( t_game *game );
void	my_pp( t_img img, int x, int y, int colour );
void	render_cell( t_img img, int color, int h_pixel, int w_pixel );
int		render( t_game *game );

/* UTILS */
// free
void	ft_free( char *var );
void	free_tab( char **tab );
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
char	*ft_strtok( char *s, char sep );
void	ft_bzero( void *str, size_t n );
void	*ft_calloc( size_t nitems, size_t size );
void	*ft_memset( void *s, int c, size_t n );
int		ismapchar( int ch );

// utils
int		get_center( int start, int end );

#endif