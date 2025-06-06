/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/06 15:07:03 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_win_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_game *game, int pos_x, int pos_y, int off_x, int off_y, long color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < MAP_TILE_SIZE)
	{
		j = 0;
		while (j < MAP_TILE_SIZE)
		{
			x = (pos_x * MAP_TILE_SIZE + i - off_x + MINIMAP_X_START + MINIMAP_BORDER);
			y = (pos_y * MAP_TILE_SIZE + j - off_y + MINIMAP_Y_START + MINIMAP_BORDER);
			if (x >= MINIMAP_X_START + MINIMAP_BORDER && \
				x < MINIMAP_X_START + MINIMAP_SIZE && \
				y >= MINIMAP_Y_START + MINIMAP_BORDER && \
				y < MINIMAP_Y_START + MINIMAP_SIZE)
				put_pixel_to_image(
					game->img,
					x,
					y,
					color
					);
			j++;
		}
		i++;
	}
}

int	calculate_offset(double g_pos)
{
	int		offset;
	double	diff;

	diff = g_pos - (int)g_pos;
	offset = (int)(MAP_TILE_SIZE * diff);
	return (offset);
}

void	draw_line(char *line, t_game *game, double pos_y)
{
	int		tile;
	int		pos_x;
	int		off_x;
	int		off_y;

	off_x = calculate_offset(game->pos_x);
	off_y = calculate_offset(game->pos_y);
	tile = (int)game->pos_x - 7;
	pos_x = 0;
	while (tile < 0)
	{
		draw_tile(game, pos_x, pos_y, off_x, off_y, 0x00000000);
		tile++;
		pos_x++;
	}
	if (!line)
	{
		while (tile < (int)game->pos_x + 9)
		{
			draw_tile(game, pos_x, pos_y, off_x, off_y, 0x00000000);
			tile++;
			pos_x++;
		}
		return ;
	}
	while (line[tile] && tile < (int)game->pos_x + 9)
	{
		if (center_tile(line[tile]))
			draw_tile(game, pos_x, pos_y, off_x, off_y, 0x000075255);
		if (line[tile] == '1')
			draw_tile(game, pos_x, pos_y, off_x, off_y, 0x00175250250);
		if (line[tile] == ' ' || line[tile] == '\n')
			draw_tile(game, pos_x, pos_y, off_x, off_y, 0x00000000);
		tile++;
		pos_x++;
	}
	while (tile < (int)game->pos_x + 9)
	{
		draw_tile(game, pos_x, pos_y, off_x, off_y, 0x00000000);
		tile++;
		pos_x++;
	}
}

void	draw_border(t_game *game)
{
	int		i;
	int		j;
	long	color;

	color = 0x00252525;
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			if (j < MINIMAP_BORDER || \
				j > MINIMAP_SIZE - MINIMAP_BORDER || \
				i < MINIMAP_BORDER || \
				i > MINIMAP_SIZE - MINIMAP_BORDER)
			{
				put_pixel_to_image(
					game->img,
					i + MINIMAP_X_START,
					j + MINIMAP_Y_START,
					color
					);
			}
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_P_SIZE)
	{
		j = 0;
		while (j < MINIMAP_P_SIZE)
		{
			put_pixel_to_image(
				game->img,
				((7 * MAP_TILE_SIZE) + i + MINIMAP_X_START + MINIMAP_BORDER - (MINIMAP_P_SIZE / 2)),
				((7 * MAP_TILE_SIZE) + j + MINIMAP_Y_START + MINIMAP_BORDER - (MINIMAP_P_SIZE / 2)),
				0x00FF0000
				);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		line;

	printf("x:%f y:%f\n", game->pos_x, game->pos_y);
	i = 0;
	line = (int)game->pos_y - 7;
	while (line < 0)
	{
		draw_line(NULL, game, i);
		line++;
		i++;
	}
	while (game->map[line] && line < (int)game->pos_y + 9)
	{
		draw_line(game->map[line], game, i);
		line++;
		i++;
	}
	while (line < (int)game->pos_y + 9)
	{
		draw_line(NULL, game, i);
		line++;
		i++;
	}
	draw_border(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
}
