/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:30 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/09 10:01:42 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rad_to_vect(t_vect *direction, float rad)
{
	direction->x = cos(rad);
	direction->y = sin(rad);
}

int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x < WINDOW_WIDTH / 2)
	{
		game->rad_direction += MOUSE_SENS * PI;
		if (game->rad_direction > 2 * PI)
			game->rad_direction -= 2 * PI;
		rad_to_vect(&game->direction, game->rad_direction);
		draw_player(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
		// printf("x:%f y:%f\n", game->direction.x, game->direction.y);

	}
	if (x > WINDOW_WIDTH / 2)
	{
		game->rad_direction -= MOUSE_SENS * PI;
		if (game->rad_direction < -2 * PI)
			game->rad_direction += 2 * PI;
		rad_to_vect(&game->direction, game->rad_direction);
		draw_player(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
		// printf("x:%f y:%f\n", game->direction.x, game->direction.y);
	}
	mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	return (0);
}
