NAME = libft.a
SRC = ft_atoi.c ft_bzero.c  ft_calloc.c ft_isalnum.c    \
ft_isalpha.c    ft_isascii.c    ft_isdigit.c    ft_isprint.c    \
ft_itoa.c   ft_memccpy.c    ft_memchr.c ft_memcmp.c \
ft_memcpy.c ft_memmove.c    ft_memset.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c  ft_putstr_fd.c  ft_split.c  \
ft_strchr.c ft_strdup.c ft_strjoin.c    ft_strlcat.c    \
ft_strlcpy.c    ft_strlen.c ft_strmapi.c    ft_strncmp.c    \
ft_strnstr.c    ft_strrchr.c    ft_strtrim.c    ft_substr.c \
ft_tolower.c    ft_toupper.c
SRCBONUS =  ft_lstadd_back_bonus.c  ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
ft_lstdelone_bonus.c    ft_lstiter_bonus.c  ft_lstlast_bonus.c  \
ft_lstmap_bonus.c   ft_lstnew_bonus.c   ft_lstsize_bonus.c
SRCGNL = get_next_line.c gnl/get_next_line_utils.c
SRCCUB = ft_conversor.c ft_cub3d.c ft_draw.c ft_getinfo.c ft_init.c ft_keys.c \
ft_raycasting.c ft_rules.c ft_toimg_andimg.c ft_frees.c sprites.c
SRCMINI= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRCMINI+= mlx_png.c mlx_mouse.m
CC = gcc -Wall -Wextra -Werror -O3
RM = rm -f
all: $(NAME)
$(NAME): 
	${CC} libft/libft.a gnl/${SRCGNL} minilibx/libmlx.a ${SRCCUB} -framework OpenGL -framework AppKit -o CUB3D
bonus:
	${CC} libft/libft.a gnl/${SRCGNL} minilibx/libmlx.a ${SRCCUB} -framework OpenGL -framework AppKit -o CUB3D
fclean:
	${RM} ${OBJ} ${OBJBONUS}
	${RM} ${NAME} ${OBJBONUS}
clean:
	${RM} ${OBJ} ${OBJBONUS}
re: fclean all
.PHONY: all clean fclean re bonus
