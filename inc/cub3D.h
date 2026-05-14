/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:18:13 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/17 10:35:29 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */

/*-------------------------\\\\\___LIBRARIES___/////--------------------------*/
//_Libft
# include "../libft/inc/libft.h"

//_Whitelisted
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <math.h>
# include "stdbool.h"
//mlx
# include "../minilibx-linux/mlx.h"

/*---------------------------\\\\\___MACROS___/////---------------------------*/
//_Errors
# define ERR_MALLOC "Memory allocation failed"
# define ERR_ARG "Invalid number of arguments\nExpected 1 argument"
# define ERR_FILE "Invalid file\nExpected <filename.cub>"
# define ERR_ACC "CubFile: No file access"
# define ERR_CDUP "CubFile: Duplicate element"
# define ERR_MISS "CubFile: Missing element"
# define ERR_INV_ELEM "CubFile: Invalid identifier"
# define TILE_SIZE 10
# define FOV 1.047197551 //MY_Py / 3.0
# define WIN_W 1280
# define WIN_H 720
# define ERR_TEX_ACC "TextureFile: No file access\nExpected ./path_to_texture"
# define ERR_TEX_EXT "TextureFile: Wrong Extension\nExpected filename.xpm"
# define ERR_COL "Cubfile: Invalid Color Element\nExpected RGB format \
ranging from 0 to 255"
# define ERR_MAP_INV "Invalid map character(s) detected\nExpected only 1, 0, N,\
	S, W, E"
# define ERR_P_NB "Invalid number of player starting position\nExpected one"
# define ERR_P_POS "Invalid player starting position"
# define ERR_MAP_CLO "Map is not closed"
//keyboard keys
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
//maths angle calcul
# define MY_PI 3.14159265358979323846
# define MY_HALF_PI 1.570796327
/*--------------------------\\\\\___STRUCTS___/////---------------------------*/
typedef struct s_data	t_data;
typedef struct s_cub	t_cub;
typedef struct s_file	t_file;
typedef struct s_pars	t_pars;
typedef struct s_img	t_img;
typedef struct s_map	t_map;
typedef struct s_keys	t_keys;
typedef struct s_player	t_player;
typedef struct s_pars	t_pars;
typedef struct s_bbox	t_bbox;
typedef struct s_point	t_point;
typedef struct s_cone	t_cone;
typedef struct s_gc		t_gc;
typedef struct s_ray	t_ray;
typedef struct s_hit	t_hit;
typedef struct s_cast	t_cast;
typedef struct s_column	t_column;

struct s_column
{
	int		x;
	int		wall_top;
	int		wall_bottom;
	int		wall_height;
	double	wall_pos;
	double	corrected;
	int		flip_tex;
	t_img	*tex;	
};

struct s_cast
{
	double	px;
	double	py;
	double	dir_x;
	double	dir_y;
	double	x;
	double	y;
	double	step_x;
	double	step_y;
	int		depth;
	int		max_depth;
};

struct s_hit
{
	double	x;
	double	y;
	double	dist;
	int		hit;
	int		side; // 0 vertical. 1 horizontal
	double	wall;
};

//ray in frame
struct s_ray
{
	double	angle;
	double	distance;
	double	hit_x;
	double	hit_y;
	int		hide_side;
};
struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
};

struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian; //byte order
	int		width;
	int		height;
};

struct s_point
{
	int	x;
	int	y;
	int	ox;
	int	oy;
};

struct s_cub
{
	// TEXTURES
	char				*w_tex;
	char				*n_tex;
	char				*s_tex;
	char				*e_tex;
	// COLORS
	int					f_col[4];
	int					c_col[4];
	unsigned int		f_int_col;
	unsigned int		c_int_col;
	// MAP
	char				**m_pat;
	int					m_width;
	int					m_height;
	// PLAYER
	char				p_or;
	double				p_x;
	double				p_y;

	t_data				*data;
};

struct s_pars
{
	// NB ELEM
	size_t	nb_n;
	size_t	nb_s;
	size_t	nb_w;
	size_t	nb_e;
	size_t	nb_f;
	size_t	nb_c;
	size_t	nb_map;

	t_data	*data;
};

struct s_file
{
	int		fd;
	size_t	lcount;
	char	**pattern;
	char	**content;
	int		width;
	int		height;
	t_data	*data;
};

struct s_map
{
	char	**pattern;
	t_data	*data;
};

struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
};

struct	s_bbox
{
	int	row_min;
	int	row_max;
	int	col_min;
	int	col_max;
};

struct s_player
{
	double	x;
	double	y;
	double	dir; //in radiant
	double	speed;
	double	radius;
	double	rot_speed;
};

struct s_cone
{
	double			dir;
	double			perp_x;
	double			perp_y;
	double			len;
	double			base;
	double			t;
	unsigned int	color;
};

struct s_data
{
	t_pars		*pars;
	t_cub		*cub;
	t_file		*file;
	t_img		img;
	t_map		*map;
	t_keys		keys;
	t_player	player;
	t_gc		*gc;
	t_ray		*rays;
	void		*mlx;
	void		*win;
	int			num_rays;
	int			win_w;
	int			win_h;
	t_img		tex[4];
};

/*-------------------------\\\\\___FUNCTIONS___/////--------------------------*/
//_MAIN-----------------------------------------------------------------------

/* CB_ERRORHUB 
* prints <Error - message> and executes exithub if code != 0
*/
void	cb_errorhub(char *message, int code, t_data *d);

//CB_EXITHUB execute cb_free and exit with the right status
void	cb_exithub(int code, t_data *d);

/*CB_SECUMALLOC
* allocate a memspace of <size>. if the allocation fails cb_errorhub 
* is executed for a malloc error with code 1, the program exits
*/
void	*cb_secumalloc(size_t size, t_data *d);

void	cb_free(t_data *d);
void	cb_initialization(t_data *d);
char	*cb_strdup(const char *s, t_data *d);
char	*cb_strtrim(const char *s1, const char *set, t_data *d);

//_PARSING--------------------------------------------------------------------
void	cb_parser(int ac, char **av, t_data *d);
void	cb_pars_storefile(char *file, t_file *f, t_data *d);
void	cb_pars_pc_checkduplicate(char **content, t_pars *p);
char	*cb_pars_pc_dsp_extracttex(char *line, int *i, t_cub *c);
void	cb_pars_pc_dsp_extractcol(char *line, int code, t_cub *c);
void	cb_pars_pc_extractmap(char **content, t_cub *c);
void	cb_pars_map(t_cub *c);
void	initialization_player(t_data *d);

//graphics
void	init_graphics(t_data *data);
void	draw_minimap(t_data *d);

//void	draw_tile(t_img *img, int px, int py, unsigned int color);
int		close_window(t_data *d);
void	mm_setup(t_data *d, int *ox, int *oy, int *t);
void	draw_tile_mm(t_img *img, t_point pos, int size, unsigned int color);
void	my_pixel_put(t_img *img, int x, int y, unsigned int color);
int		handle_keypress(int keycode, t_data *d);
int		update(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		render_frame(t_data *d);
void	key_init(t_data *d);
int		point_hits(t_data *d, double x, double y);
void	draw_player(t_data *d, int ox, int oy, int tile);

//raycasting
void	init_rays(t_data *d);
void	compute_rays(t_data *d);
int		is_wall(t_data *d, int row, int col);
int		is_wall_at(t_data *d, double wx, double wy);
void	init_cast_vertical(t_data *d, double angle, t_cast *cast);
t_hit	cast_vertical(t_data *d, double angle);
t_hit	cast_horizontal(t_data *d, double angle);
t_hit	cast_one_ray(t_data *d, double angle);
void	init_cast_horizontal(t_data *d, double angle, t_cast *cast);
double	normalize_angle(double a);
void	render_3d_view(t_data *d);
void	load_all_textures(t_data *d);
void	step_cast(t_cast *cast);
double	apply_fisheye(double raw_dist, double ray_angle, double player_dir);
double	get_ray_angle(t_data *d, int col);
void	draw_wall_column(t_data *d, t_column *c);

//garbage collector
void	gc_init(t_data *d);
void	gc_add(t_data *d, void *ptr);
void	*gc_malloc(t_data *d, ssize_t size);
void	gc_remove(t_data *d, void *ptr);
void	gc_free_one(t_data *d, void *ptr);
void	gc_free_all(t_data *d);
/* ************************************************************************** */

#endif
