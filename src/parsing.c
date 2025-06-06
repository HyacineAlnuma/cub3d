/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:03:39 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/06 14:39:48 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_tile_validity(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'E' && \
		c != 'S' && c != 'W' && c != ' ' && c != '\n')
		return (0);
	return (1);
}


int	check_borders(char *line, int row, int line_nb)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (row == 8 || row == line_nb - 1)
		{
			if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
				return (0);
		}
	}
	return (1);
}

int	player_tile(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	center_tile(char c)
{
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	wrapping_tile(char c)
{
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '1')
		return (0);
	return (1);
}

int	borders_around(char **map, int i, int j)
{
	if (!wrapping_tile(map[i + 1][j]) || !wrapping_tile(map[i - 1][j]))
		return (0);
	if (!wrapping_tile(map[i][j + 1]) || !wrapping_tile(map[i][j - 1]))
		return (0);
	return (1);
}

int	check_tiles_borders(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	player;

	i = 8;
	j = 0;
	k = 0;
	player = 0;
	game->map = (char **)malloc(sizeof(char *) * ((game->height - 8) + 1));
	if (!game->map)
		return (0);
	while (game->file_content[i])
	{
		j = 0;
		game->map[k] = game->file_content[i];
		while (game->file_content[i][j])
		{
			if (player_tile(game->file_content[i][j]))
			{
				if (player)
					return (0);
				game->pos_x = (double)j + 0.5;
				game->pos_y = (double)(i - 8) + 0.5;
				if (game->file_content[i][j] == 'N')
				{
					game->rad_direction = PI / 2;
					rad_to_vect(&game->direction, game->rad_direction);
				}
				else if (game->file_content[i][j] == 'S')
				{
					game->rad_direction = 3 * PI / 2;
					rad_to_vect(&game->direction, game->rad_direction);	
				}
				else if (game->file_content[i][j] == 'E')
				{
					game->rad_direction = PI;
					rad_to_vect(&game->direction, game->rad_direction);
				}
				else if (game->file_content[i][j] == 'W')
				{
					game->rad_direction = 0;
					rad_to_vect(&game->direction, game->rad_direction);
				}
				printf("x:%f y:%f\n", game->direction.x, game->direction.y);
				player = 1;
			}
			if (!check_tile_validity(game->file_content[i][j]))
				return (0);
			if (center_tile(game->file_content[i][j]) && \
			!borders_around(game->file_content, i, j))
				return (0);
			j++;
		}
		i++;
		k++;
	}
	game->map[k] = NULL;
	if (!player)
		return (0);
	return (1);
}

int	check_paths(t_game *game)
{
	char	*line;
	int		fd;
	int		i;
	char	*identifiers[4];

	i = 0;
	identifiers[0] = "NO ";
	identifiers[1] = "SO ";
	identifiers[2] = "WE ";
	identifiers[3] = "EA ";
	game->paths = (char **)malloc(sizeof(char *) * 5);
	if (!game->paths)
		return (0);
	while (i < 4)
	{
		line = game->file_content[i];
		game->paths[i] = game->file_content[i];
		if (ft_strncmp(line, identifiers[i], 3))
			return (0);
		line += (sizeof(char) * 3);
		if (line)
			line[ft_strlen(line) - 1] = '\0';
		else
			return (0);
		fd = open(line, O_RDONLY);
		if (!fd || fd == -1)
			return (0);
		close(fd);
		i++;
	}
	game->paths[i] = NULL;
	return (1);
}

int	check_colors(t_game *game)
{
	char	*line;
	int		i;
	int		j;
	int		k;
	char	*identifiers[2];
	char	**rgb;

	i = 5;
	k = 0;
	identifiers[0] = "F ";
	identifiers[1] = "C ";
	game->colors = (char **)malloc(sizeof(char *) * 3);
	if (!game->colors)
		return (0);
	while (i < 7)
	{
		line = game->file_content[i];
		game->colors[k] = game->file_content[i];
		if (ft_strncmp(line, identifiers[i - 5], 2))
			return (0);
		line += (sizeof(char) * 2);
		rgb = ft_split(line, ',');
		if (!rgb)
			return (0);
		j = 0;
		while (rgb[j])
		{
			if (ft_atoi(rgb[j]) < 0 || ft_atoi(rgb[j]) > 255)
			{
				free_map(rgb);
				return (0);
			}
			j++;
		}
		free_map(rgb);
		i++;
		k++;
	}
	game->colors[k] = NULL;
	return (1);
}
