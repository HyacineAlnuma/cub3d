/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_testing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:50:17 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/06 14:45:20 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	test_up_tiles(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	(void)key_pressed;
	test_x = game->pos_x - ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2);
	test_y = game->pos_y - ((0.125 * game->direction.y) +(double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2);
	// printf("1 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
	if (game->map[(int)test_y][(int)test_x] == '1')
		return (0);
	test_x += (double)MINIMAP_P_SIZE / MAP_TILE_SIZE - 0.0001;
	// printf("2 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
	if (game->map[(int)test_y][(int)test_x] == '1')
		return (0);
	return (1);
}

int	test_down_tiles(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	(void)key_pressed;
	test_x = game->pos_x - ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2);
	test_y = game->pos_y + ((0.125 * game->direction.y) + (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2 - 0.0001);
	// printf("1 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
	if (game->map[(int)test_y][(int)test_x] == '1')
		return (0);
	test_x += (double)MINIMAP_P_SIZE / MAP_TILE_SIZE - 0.0001;
	// printf("2 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
	if (game->map[(int)test_y][(int)test_x] == '1')
		return (0);
	return (1);
}

int	test_right_tiles(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	(void)key_pressed;
	test_x = game->pos_x + ((0.125 * game->direction.x) + (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2 - 0.0001);
	test_y = game->pos_y - ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2);
	// printf("1 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
	if (game->map[(int)test_y][(int)test_x] == '1')
		return (0);
	test_y += (double)MINIMAP_P_SIZE / MAP_TILE_SIZE - 0.0001;
	// printf("2 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
	if (game->map[(int)test_y][(int)test_x] == '1')
		return (0);
	return (1);
}

int	test_left_tiles(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	(void)key_pressed;
	test_x = game->pos_x - ((0.125 * game->direction.x) + (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2);
	test_y = game->pos_y - ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2);
	// printf("1 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
	if (game->map[(int)test_y][(int)test_x] == '1')
		return (0);
	test_y += (double)MINIMAP_P_SIZE / MAP_TILE_SIZE - 0.0001;
	// printf("2 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
	if (game->map[(int)test_y][(int)test_x] == '1')
		return (0);
	return (1);
}

int	check_corners(t_game *game, double pos_x, double pos_y)
{
	double	test_x;
	double	test_y;
	int		corner;

	corner = 1;
	while (corner < 5)
	{
		if (corner == 1)
		{
			test_x = pos_x - ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2) + 0.001;
			test_y = pos_y - ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2) + 0.001;
		}
		if (corner == 2)
		{
			test_x = pos_x + ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2) - 0.001;
			test_y = pos_y - ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2) + 0.001;
		}
		if (corner == 3)
		{
			test_x = pos_x - ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2) + 0.001;
			test_y = pos_y + ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2) - 0.001;
		}
		if (corner == 4)
		{
			test_x = pos_x + ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2) - 0.001;
			test_y = pos_y + ((double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2) - 0.001;
		}
		// printf("%f %f %d\n", pos_y, test_y, (int)test_y);
		// printf("corner:%d nx:%f ny:%f rnx:%d rny:%d next:%c\n", corner, test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
		corner++;
	}
	return (1);
}
