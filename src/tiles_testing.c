/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_testing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:50:17 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/06 10:50:40 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	test_up_tiles(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	test_y = game->pos_y;
	test_x = game->pos_x;
	if (key_pressed == KEY_UP)
	{
		test_x -= (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2;
		test_y -= 0.125 +(double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2;
		// printf("1 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
		test_x += (double)MINIMAP_P_SIZE / MAP_TILE_SIZE - 0.0001;
		// printf("2 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
	}
	return (1);
}

int	test_down_tiles(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	test_y = game->pos_y;
	test_x = game->pos_x;
	if (key_pressed == KEY_DOWN)
	{
		test_x -= (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2;
		test_y += 0.125 + (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2 - 0.0001;
		// printf("1 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
		test_x += (double)MINIMAP_P_SIZE / MAP_TILE_SIZE - 0.0001;
		// printf("2 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
	}
	return (1);
}

int	test_right_tiles(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	test_y = game->pos_y;
	test_x = game->pos_x;
	if (key_pressed == KEY_RIGHT)
	{
		test_x += 0.125 + (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2 - 0.0001;
		test_y -= (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2;
		// printf("1 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
		test_y += (double)MINIMAP_P_SIZE / MAP_TILE_SIZE - 0.0001;
		// printf("2 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
	}
	return (1);
}

int	test_left_tiles(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	test_y = game->pos_y;
	test_x = game->pos_x;
	if (key_pressed == KEY_LEFT)
	{
		test_x -= 0.125 + (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2;
		test_y -= (double)MINIMAP_P_SIZE / MAP_TILE_SIZE / 2;
		// printf("1 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
		test_y += (double)MINIMAP_P_SIZE / MAP_TILE_SIZE - 0.0001;
		// printf("2 nx:%f ny:%f rnx:%d rny:%d next:%c\n", test_x, test_y, (int)test_x, (int)test_y, game->map[(int)test_y][(int)test_x]);
		if (game->map[(int)test_y][(int)test_x] == '1')
			return (0);
	}
	return (1);
}