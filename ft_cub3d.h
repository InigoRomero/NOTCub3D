/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 18:15:27 by iromero-          #+#    #+#             */
/*   Updated: 2021/04/19 17:01:01 by iromero-         ###   ########.fr       */
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
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_ZERO 29
# define KEY_BRACE_R 30
# define KEY_O 31
# define KEY_U 32
# define KEY_BRACE_L 33
# define KEY_I 34
# define KEY_P 35
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_SEMI 41
# define KEY_N 45
# define KEY_M 46
# define KEY_TAB 48
# define KEY_PLUS 69
# define KEY_MINUS 78
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
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct		s_vars
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			*img;
	char			*img_ptr;
	char			*img_ptr2;
	char			*img_psr;
	char			*img_psrda;
	char			*wlone[8];
	char			*wdata[8];
	int				*data_spr;
	int				bpp;
	int				sl;
	int				endian;
	int				wbpp[8];
	int				wsl[8];
	int				wendian[8];
	int				h[8];
	int				w[8];
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
}					t_mapinfo;

void				getinfo(t_mapinfo *s, char *buffer);
void				maptoarray(t_mapinfo *s);
int					noflines(t_mapinfo *s);
int					noffiles(t_mapinfo *s);
int					checkrules(t_mapinfo *s);
int					deal_key(t_mapinfo *s);
void				ft_verline(t_mapinfo *s);
void				raycasting(t_mapinfo *s);
void				ft_gun(t_mapinfo *s);
void				put_pxl_to_img(t_mapinfo *s, int x, int y);
void				calcularobj(t_mapinfo *s);
void				to_img(t_mapinfo *s);
void				openall(t_mapinfo *s);
void				startvars(t_mapinfo *s);
void				readmap(t_mapinfo *s, char **argv, int argc);
int					nopulsed(int key, t_mapinfo *s);
int					pulsed(int eky, t_mapinfo *s);
void				fp(t_mapinfo *s);
int					checkname(char **argv);
void				dofreesray(t_mapinfo *s);
int					write_bmp_header(int fd, int filesize, t_mapinfo *s);
int					write_bmp_data(int file, t_mapinfo *s, int pad);
void				set_int_in_char(unsigned char *start, int value);
int					get_color(t_mapinfo *s, int x, int y);
#endif
