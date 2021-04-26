/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 115:15:27 by iromero-          #+#    #+#             */
/*   Updated: 2021/04/19 19:26:15 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 15
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_ONE 115
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 215
# define KEY_ZERO 29
# define KEY_BRACE_R 30
# define KEY_O 31
# define KEY_U 32
# define KEY_BRACE_L 33
# define KEY_I 34
# define KEY_P 35
# define KEY_L 37
# define KEY_J 315
# define KEY_K 40
# define KEY_SEMI 41
# define KEY_N 45
# define KEY_M 46
# define KEY_TAB 415
# define KEY_PLUS 69
# define KEY_MINUS 715
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define BUFFER_SIZE 1
# define KEY_ESQ 53
# define KEY_SHIFT 257
# define DIRN 30
# define DIRW 39
# define DIRE 21
# define DIRS 35
# define MAXX 2560
# define MAXY 1400
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
#include <time.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# define BLACK 0x00000000

typedef struct		s_vars
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			*img;
	char			*img_ptr;
	char			*img_ptr2;
	char			*img_psr;
	char			*img_psrda;
	char			*wlone[15];
	char			*wdata[15];
	int				*data_spr[15];
	int				bpp;
	int				sl;
	int				endian;
	int				wbpp[15];
	int				wsl[15];
	int				wendian[15];
	int				h[15];
	int				w[15];
	char			*map;
	int				x;
	int				y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	char			*f;
	char			*c;
	int				**mapn;
	int				width;
	int				height;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			time;
	double			oldtime;
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				obstart;
	int				obend;
	int				color;
	double			movespeed;
	double			frametime;
	double			rotspeed;
	double			olddirx;
	double			olddiry;
	double			oldplanex;
	double			oldplaney;
	int				initialdir;
	int				preseda;
	int				presedw;
	int				presedl;
	int				presedr;
	int				preseds;
	int				presedd;
	int				presedesq;
	int				presshift;
	int				x_text;
	double			x_wall;
	int				id;
	int				fpposx;
	int				fpposy;
	int				count;
	int				alturalinea;
	int				obx;
	int				oby;
	int				score;
	int				color2;
	int				j;
	int				cox;
	double			hp;
	int				screenshot;
	int				max_row;
	int				max_col;
	int				coin_counter;
	//SPRITES
	double		sprite_x;
	double		sprite_y;
	double		*sprite_pos_x;
	double		*sprite_pos_y;
	double		*s_distance;
	int			drawstart_x;
	int			drawend_x;
	int			drawstart_y;
	int			drawend_y;
	int			sprite_w;
	int			sprite_h;
	int			sprite_screen_x;
	int			tex_width;
	int			tex_height;
	double		transform_x;
	double		transform_y;
	float		*s_buff;
	double		invdet;
	int			count_sprite;
	int			stripe;
	int			tex_x;
	int			tex_y;
}					t_s;

void				getinfo(t_s *s, char *buffer);
void				maptoarray(t_s *s);
int					noflines(t_s *s);
int					noffiles(t_s *s);
int					checkrules(t_s *s);
int					deal_key(t_s *s);
void				ft_verline(t_s *s);
void				raycasting(t_s *s);
void				ft_gun(t_s *s);
void				put_pxl_to_img(t_s *s, int x, int y);
void				calcularobj(t_s *s);
void				to_img(t_s *s);
void				openall(t_s *s);
void				startvars(t_s *s);
void				readmap(t_s *s, char **argv, int argc);
int					nopulsed(int key, t_s *s);
int					pulsed(int eky, t_s *s);
void				fp(t_s *s);
int					checkname(char **argv);
void				dofreesray(t_s *s);
int					write_bmp_header(int fd, int filesize, t_s *s);
int					write_bmp_data(int file, t_s *s, int pad);
void				set_int_in_char(unsigned char *start, int value);
int					get_color(t_s *s, int x, int y);
void				get_sprite(t_s *s);
void				sprites(t_s *s);
#endif
