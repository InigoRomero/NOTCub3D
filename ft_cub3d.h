/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 18:15:27 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/09 12:36:09 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

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
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

typedef struct		s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*map;
	int		x;
	int		y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	*f;
	char	*c;
	int		**mapn;
	int		width;
	int		height;
	double	posX;
	double	posY;
	double	dirX; 
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldtime;
}					t_mapinfo;

void	getinfo(t_mapinfo *stru, char *buffer);
void	maptoarray(t_mapinfo *stru);
int		noflines(t_mapinfo *stru);
int		noffiles(t_mapinfo *stru);
int checkrules(t_mapinfo *stru);
#endif