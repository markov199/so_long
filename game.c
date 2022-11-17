/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:54:26 by mkovoor           #+#    #+#             */
/*   Updated: 2022/11/16 16:20:59 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"solong.h"

int	ft_move(t_data *data, t_map *map, int new_pos)
{
	if (map->map_str[new_pos] == '0' || map->map_str[new_pos] == 'C')
	{
		if (map->map_str[new_pos] == 'C')
			map->collected_C++;
		ft_write_moves(++map->player_moves);
		map->map_str[new_pos] = 'P';
		map->map_str[map->plyr_pos] = '0';
		map->plyr_pos = new_pos;
	}
	else if (map->map_str[new_pos] == 'E')
	{
		if ((map->collected_C - map->count_C) == 0)
		{
			ft_write_moves(++map->player_moves);
			ft_endgame(data);
		}	
	}
	ft_load_map_to_window(*data, *map);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (keycode == 13 || keycode == 126)
		ft_move(data, data->map, (data->map->plyr_pos - data->map->width - 1));
	if (keycode == 1 || keycode == 125)
		ft_move(data, data->map, (data->map->plyr_pos + data->map->width + 1));
	if (keycode == 0 || keycode == 123)
	{
		data->move = LEFT;
		ft_move(data, data->map, (data->map->plyr_pos - 1));
	}
	if (keycode == 2 || keycode == 124)
	{	
		data->move = RIGHT;
		ft_move(data, data->map, (data->map->plyr_pos + 1));
	}
	if (keycode == 53)
		ft_endgame(data);
	return (0);
}

void	ft_load_images(t_data *data, int size, t_map map)
{
	data->window_height = map.height * size;
	data->window_width = map.width * size;
	data->player_img = mlx_xpm_file_to_image(data->mlx_ptr, \
		PLAYER, &size, &size);
	data->player2_img = mlx_xpm_file_to_image(data->mlx_ptr, \
		PLAYER2, &size, &size);
	data->player_l_img = mlx_xpm_file_to_image(data->mlx_ptr, \
		PLAYERFLIP, &size, &size);
	data->player_l2_img = mlx_xpm_file_to_image(data->mlx_ptr, \
		PLAYER2FLIP, &size, &size);
	data->coin_img = mlx_xpm_file_to_image(data->mlx_ptr, COIN, &size, &size);
	data->door_img = mlx_xpm_file_to_image(data->mlx_ptr, DOOR, &size, &size);
	data->wall_img = mlx_xpm_file_to_image(data->mlx_ptr, WALL, &size, &size);
	data->grass_img = mlx_xpm_file_to_image(data->mlx_ptr, GRASS, &size, &size);
	data->move = RIGHT;
	data->i = -1;
}

void	ft_load_map_to_window(t_data data, t_map map)
{
	int		x;
	int		y;

	while (map.map_str[++data.i])
	{
		x = (data.i % (map.width + 1)) * 50;
		y = (data.i / (map.width + 1)) * 50;
		if (map.map_str[data.i] == 'P')
			ft_put_player_img(data, map, x, y);
		else if (map.map_str[data.i] == '1')
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, \
				data.wall_img, x, y);
		else if (map.map_str[data.i] == 'E')
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, \
				data.door_img, x, y);
		else if (map.map_str[data.i] == 'C')
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, \
				data.coin_img, x, y);
		else if (map.map_str[data.i] == '0')
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, \
				data.grass_img, x, y);
	}
	ft_string_to_window (&data, &map);
}

void	ft_put_player_img(t_data data, t_map map, int x, int y)
{
	if (data.move == LEFT)
	{
		if (map.player_moves % 2)
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, \
				data.player_l_img, x, y);
		else
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, \
				data.player_l2_img, x, y);
	}
	if (data.move == RIGHT)
	{
		if (map.player_moves % 2)
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, \
				data.player_img, x, y);
		else
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, \
				data.player2_img, x, y);
	}
}
