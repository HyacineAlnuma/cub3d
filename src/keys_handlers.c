/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:29:22 by val               #+#    #+#             */
/*   Updated: 2025/06/09 10:04:12 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_keys(t_game *game)
{
	size_t	index;

	index = 0;
	while (index < KEY_MEMORY)
	{
		handle_key(game->keys[index], game);
		index++;
	}
}

void	handle_dir_input(t_game *game, double pos_x, double pos_y, int key_pressed)
{
	(void)key_pressed;
	if (!check_corners(game, pos_x, pos_y))
		return ;
	game->pos_x = pos_x;
	game->pos_y = pos_y;
	draw_minimap(game);
}

int	key_hook(int key_pressed, void *param)
{
	t_game	*game;

	game = param;
	if (key_pressed == KEY_QUIT)
		exit_game(game);
	// if (key_pressed == KEY_TEST && get_time_ms() - key.time > 50000)
	// 	ft_putstr_fd("TEST\n", 2);
	if (key_pressed == KEY_UP)
		handle_dir_input(game, game->pos_x + (0.125 * game->direction.x), game->pos_y - (0.125 * game->direction.y), key_pressed);
	if (key_pressed == KEY_RIGHT)
		handle_dir_input(game, game->pos_x + (0.125 * game->direction.y), game->pos_y + (0.125 * game->direction.x), key_pressed);
	if (key_pressed == KEY_DOWN)
		handle_dir_input(game, game->pos_x - (0.125 * game->direction.x), + game->pos_y + (0.125 * game->direction.y), key_pressed);
	if (key_pressed == KEY_LEFT)
		handle_dir_input(game, game->pos_x - (0.125 * game->direction.y), game->pos_y - (0.125 * game->direction.x), key_pressed);
	return (1);
}

void	handle_key(t_key key, t_game *game)
{
	if (key.keycode == KEY_QUIT)
		exit_game(game);
	if (key.keycode == KEY_TEST && get_time_ms() - key.time > 50000)
		ft_putstr_fd("TEST\n", 2);
	if (key.keycode == KEY_UP)
		handle_dir_input(game, game->pos_x, (game->pos_y - 0.125), key.keycode);
	if (key.keycode == KEY_RIGHT)
		handle_dir_input(game, (game->pos_x + 0.125), game->pos_y, key.keycode);
	if (key.keycode == KEY_DOWN)
		handle_dir_input(game, game->pos_x, (game->pos_y + 0.125), key.keycode);
	if (key.keycode == KEY_LEFT)
		handle_dir_input(game, (game->pos_x - 0.125), game->pos_y, key.keycode);
}
