/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_testing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:50:17 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/09 10:04:34 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
