/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:48:27 by mkovoor           #+#    #+#             */
/*   Updated: 2022/11/14 13:08:59 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "solong.h"
#define PLAYER "images/player_r.xpm"
#define PLAYERFLIP "images/player_l.xpm"
#define PLAYER2 "images/player_r2.xpm"
#define PLAYER2FLIP "images/player_l2.xpm"
#define COIN "images/coin.xpm"
#define DOOR "images/door.xpm"
#define WALL "images/wall.xpm"
#define GRASS "images/grass.xpm"
#define LEFT -1
#define RIGHT 1

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*player_img;
	void	*player2_img;
	void	*player_l_img;
	void	*player_l2_img;
	void	*coin_img;
	void	*door_img;
	void	*wall_img;
	void	*grass_img;
	int		window_width;
	int		window_height;
	int 	i;
	int		move;
	t_map	*map;
} t_data;

void ft_load_map_to_window(t_data data, t_map map);

int get_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 |blue);
}

int ft_endgame(t_data *data)
{
	free(data->map->map_str);
	mlx_destroy_window(data->mlx_ptr, data->mlx_window);
	exit(0);
}

int ft_move(t_data *data, t_map *map, int new_pos)
{
	if(map->map_str[new_pos] == '0' || map->map_str[new_pos] == 'C' )
	{
		if (map->map_str[new_pos] == 'C')
			map->collected_C++;
		map->player_moves++;
		map->map_str[new_pos] = 'P';
		map->map_str[map->plyr_pos] = '0';
		map->plyr_pos = new_pos;			
	}
	else if(map->map_str[new_pos] == 'E')
	{
		if ((map->collected_C - map->count_C) == 0)
		{
			map->player_moves++;
			ft_endgame(data);
		}	
	}
	// write (1, "Player moves ", 13);
	
	ft_load_map_to_window(*data, *map);
	return (0);
}

int key_hook(int keycode, t_data *data)
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
	{	data->move = RIGHT;	
		ft_move(data, data->map, (data->map->plyr_pos + 1));
	}
	if (keycode == 53)
	{
		ft_endgame(data);
		
		
	}
	return (0);
}

void ft_load_images(t_data *data, int size, t_map map)
{
	data->window_height = map.height * 50;
	data->window_width = map.width * 50;
	data->player_img = mlx_xpm_file_to_image(data->mlx_ptr, PLAYER, &size, &size);
	data->player2_img = mlx_xpm_file_to_image(data->mlx_ptr, PLAYER2, &size, &size);
	data->player_l_img = mlx_xpm_file_to_image(data->mlx_ptr, PLAYERFLIP, &size, &size);
	data->player_l2_img = mlx_xpm_file_to_image(data->mlx_ptr, PLAYER2FLIP, &size, &size);
	data->coin_img = mlx_xpm_file_to_image(data->mlx_ptr, COIN, &size, &size); 
	data->door_img = mlx_xpm_file_to_image(data->mlx_ptr, DOOR, &size, &size); 
	data->wall_img = mlx_xpm_file_to_image(data->mlx_ptr, WALL, &size, &size);
	data->grass_img = mlx_xpm_file_to_image(data->mlx_ptr, GRASS, &size, &size);
	data->move = RIGHT;
	data->i = -1;
}

void ft_load_map_to_window(t_data data, t_map map)
{
	int	x;
	int	y;
 
	while (map.map_str[++data.i])
	{
		x = (data.i % (map.width + 1)) * 50;
		y = (data.i / (map.width + 1)) * 50;
		if (map.map_str[data.i] == 'P')
		{
			if (data.move == RIGHT)
			{
				if(map.player_moves % 2)
				mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.player_img, x, y);
				else 
				mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.player2_img, x, y);
			}
			if (data.move == LEFT)
			{
				if(map.player_moves % 2)
				mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.player_l_img, x, y);
				else 
				mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.player_l2_img, x, y);
			}
		}
		// else if(map.map_str[data.i] == '\n')
		// 	mlx_string_put(data.mlx_ptr, data.mlx_window, x, y, 0, "\n");
		else if (map.map_str[data.i] == '1')
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.wall_img, x, y);
		else if (map.map_str[data.i] == 'E')
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.door_img, x, y);
		else if (map.map_str[data.i] == 'C')
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.coin_img, x, y);
		else if (map.map_str[data.i] == '0')
			mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.grass_img, x, y);
	}
}

void ft_map_loader(t_map *map)
{
	ft_valid_file_type(map);
	ft_init_map(map);
	ft_read_map(map);
	ft_valid_map(map);
}

int	main(void)
{
	t_data	data;
	t_map	map;
	int		size;

	size = 50;
	data.map = &map;
	map.filename = "map.ber";
	ft_map_loader(&map);
	data.mlx_ptr = mlx_init();
	ft_load_images(&data, size, map);
	data.mlx_window = mlx_new_window(data.mlx_ptr, data.window_width, \
	data.window_height, "SoLong");
	ft_load_map_to_window(data, map);
	mlx_hook(data.mlx_window, 17, 0, &ft_endgame, &data);
	mlx_hook(data.mlx_window, 2, 0, &key_hook, &data);
	// mlx_key_hook(data.mlx_window, &key_hook, &data);
	mlx_loop(data.mlx_ptr);
}
