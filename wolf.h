/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 18:53:05 by qmuntada          #+#    #+#             */
/*   Updated: 2015/10/30 16:32:44 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <time.h>

# define WIDTH 1280  // width of the screen
# define HEIGHT 720 // height of the screen
# define FOV 60 // field of view of the player
# define MSPEED 8 // movement speed of the player
# define RSPEED 1 // speed of the mouse
# define BLOC 64 // size of block
# define GRAVITY 12 // change if you want the player to fall faster
# define SCALE 2
# define ESC 53
# define Q 113
# define W 13
# define E 101
# define A 0
# define S 1
# define D 2
# define SPACE 49
# define C 8
# define Z 122
# define X 120

typedef struct			s_vector
{
	float				x;
	float				y;
	int					uvx;
	int					uvy;
	float				dist;
}						t_vector;

typedef struct			s_vectlst
{
	t_vector			vector;
	char				side;
	int					floorsv;
	int					floorev;
	int					floorbot;
	int					floortop;
	int					ceilsv;
	int					ceilev;
	int					ceilbot;
	int					ceiltop;
	int					wfloorbot;
	int					wfloorsv;
	int					wfloortop;
	int					wfloorev;
	int					wceilbot;
	int					wceilsv;
	int					wceiltop;
	int					wceilev;
	int					wallc;
	int					wallf;
	int					hc;
	int					hf;
	struct s_vectlst	*next;
}						t_vectlst;

typedef struct			s_line
{
	t_vectlst			*list;
	float				angle;
	int					iter;
}						t_line;

typedef struct			s_player
{
	float				x;
	float				y;
	float				eyes;
	float				foot;
	float				angle;
	float				bob;
	float				life;
	int					forward;
	int					straff;
	int					jump;
	int					jump2;
	int					crouch;
	int					shoot;
	int					wpstate;
}						t_player;

typedef struct			s_map
{
	char				*name;
	int					width;
	int					height;
	int					**floor;
	int					**ceiling;
	int					**texture;
	t_player			firstpos;
}						t_map;

typedef struct			s_img
{
	void				*img_ptr;
	unsigned char		*img;
	int					bpp;
	int					sl;
	int					endian;
	int					width;
	int					height;
	float				angle_w;
	int					dist;
	int					center;
}						t_img;

typedef struct			s_sprite
{
	float				life;
	int					attitude;
	int					size;
	int					state;
	int					attack;
	float				x;
	float				y;
	float				z;
	float				dist;
	int					texture;
	float				rel_angle;
	int					botx;
	int					topx;
	int					boty;
	int					topy;
	float				uvx;
	float				uvy;
}						t_sprite;

typedef struct			s_sprite_list
{
	int					n;
	t_sprite			*s;
}						t_sprite_list;

typedef struct			s_precomp
{
	float				angle;
	float				d_angle;
	float				td_angle;
	int					mwidth;
	int					mheight;
	float				playx;
	float				playy;
	float				playangle;
	float				fisheye;
}						t_precomp;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_player			p;
	t_map				map;
	t_img				img;
	t_img				*tex;
	t_line				*line;
	t_precomp			precomp;
	t_sprite_list		slist;
	char				**file;
	int					hc;
	int					hf;
	float				x;
	float				y;
	float				dist;
	float				distt;
	int					vx;
	int					vy;
	int					px;
	float				ax;
	float				ay;
	float				distf;
	float				distc;
	int					ntouch;
	int					delay;
	int					delay2;
	int					floorx;
	int					floory;
	int					color;
	int					wallf;
	int					wallc;
	int					botf;
	int					botc;
	int					t;
	int					bot;
	int					top;
	int					mouseX;
	int					mouseY;
}						t_env;

typedef struct			s_event_list
{
	int					mask;
	int					(*hook)();
	void				*param;
}						t_event_list;

void					err_map(void);
void					err_texture(void);
void					init_env(t_env *e, int fd);
void					init_texture(t_env *e);
int						key_press(int key, t_env *e);
int						key_release(int key, t_env *e);
void					fps(t_env *e);
void					calc_img(t_env *e);
void					init_vector_hori(t_precomp *prec, t_vector *h);
void					init_vector_vert(t_precomp *prec, t_vector *v);
void					vect_addsort(t_vectlst **blst, t_vector *content, \
							char side);
void					line_cleaner(t_env *e, t_vectlst *blist, int num);
void					vect_clear(t_vectlst **blst);
void					movement(t_env *e);
void					movefront(t_env *e);
void					moveback(t_env *e);
void					moveleft(t_env *e);
void					moveright(t_env *e);
void					pre_comput(t_env *e, float ray_angle);
int						jump(t_env *e);
int						mouse(int x, int y, t_env *e);
int						mouse2(int button, int x, int y, t_env *e);
void					cursor_move(void *mlx, int x, int y);
void					get_sprite_list(t_env *e, char **data, int *i);
void					sprite_display(t_env *e);
void					pixel_put(t_env *e, int x, int y);
float					get_sprite_coord(t_env *e, int n);
void					display_sprite(t_env *e, int n, float pas);
void					display_line(t_env *e, t_vectlst *list, int num);
void					render_pointwv(t_env *e, int num, int tex);
void					render_pointwh(t_env *e, int num, int tex);
void					render_pointfc(t_env *e, int num, int tex);
void					render_points(t_env *e, int x, int y, int n);
void					weapon_handling(t_env *e);
void					sprite_handling(t_env *e);
void					init_value(t_env *e, float dist);

#endif
