/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:22:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/06 11:33:58 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/time.h>
# include <X11/keysymdef.h>
# include <X11/Xlib.h>
# include <stdint.h>
# include <stdlib.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "stdbool.h"
// # include "crazypng.h"

# define KEY_MEMORY	10

# define WINDOW_WIDTH		1920
# define WINDOW_HEIGHT		1080

# define MAP_TILE_SIZE		16
# define MINIMAP_SIZE		249
# define MINIMAP_X_START	40
# define MINIMAP_Y_START	784
# define MINIMAP_BORDER		5
# define MINIMAP_P_SIZE		6

typedef enum e_keymap
{
	KEY_QUIT = XK_Escape,
	KEY_TEST = XK_e,
	KEY_UP = XK_w,
	KEY_DOWN = XK_s,
	KEY_LEFT = XK_a,
	KEY_RIGHT = XK_d
}	t_keymap;

typedef struct s_key
{
	uint64_t	time;
	int			keycode;
}	t_key;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_vect
{
	int	x;
	int	y;
}	t_vect;

typedef struct s_win_img
{
	void	*img_ptr;
	char	*data;
	int		endian;
	int		size_line;
	int		bpp;
}	t_win_img;

typedef struct s_game
{
	void		*mlx;
	char		*win;
	t_win_img	*img;
	int			width;
	int			height;
	double		pos_x;
	double		pos_y;
	int			end;
	char		**file_content;
	char		**map;
	char		**paths;
	char		**colors;
	int			steps;
	t_vect		direction;
	t_key		keys[KEY_MEMORY];
}	t_game;

void		run_game(t_game *game);
int			exit_game(t_game *game);
uint64_t	get_time_ms(void);

// ----- KEYS ----- //
int			key_hook(int key_pressed, void *param);
int			key_released(int key_pressed, void *param);
int			key_pressed(int key_pressed, void *param);
void		handle_keys(t_game *game);
void		handle_key(t_key key, t_game *game);

// ----- MAP_UTILS ----- //
int			check_file_extension(char *filename);
char		**read_map(char *map_file, t_game *game);
void		check_map_errors(t_game *game, char *map_file);
void		free_map(char **map);

// ----- PARSING ----- //
int			check_colors(t_game *game);
int			check_tiles_borders(t_game *game);
int			check_paths(t_game *game);
int			center_tile(char c);

// ----- MINIMAP ----- //
void		draw_minimap(t_game *game);

// ----- TILES ----- //
int			test_up_tiles(t_game *game, int key_pressed);
int			test_down_tiles(t_game *game, int key_pressed);
int			test_right_tiles(t_game *game, int key_pressed);
int			test_left_tiles(t_game *game, int key_pressed);

#endif