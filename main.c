/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:48:27 by mkovoor           #+#    #+#             */
/*   Updated: 2022/11/17 10:07:23 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	ft_string_to_window(t_data *data, t_map *map)
{
	char	*str;
	int		red;
	int		green;
	int		blue;
	int		get_rgb;

	red = 100;
	green = 25;
	blue = 25;
	get_rgb = red << 16 | green << 8 | blue;
	str = ft_itoa(map->player_moves);
	mlx_string_put(data->mlx_ptr, data->mlx_window, \
		100, 100, get_rgb, "Moves");
	mlx_string_put(data->mlx_ptr, data->mlx_window, \
		150, 100, get_rgb, str);
	free (str);
}

int	ft_endgame(t_data *data)
{
	free(data->map->map_str);
	mlx_destroy_window(data->mlx_ptr, data->mlx_window);
	exit(0);
}

void	ft_write_moves(int x)
{
	char	*str;

	str = ft_itoa(x);
	write (1, "moves:", 6);
	write (1, str, ft_strlen(str));
	write (1, "\n", 1);
	free (str);
}

void	ft_map_loader(t_map *map)
{
	ft_valid_file_type(map);
	ft_init_map(map);
	ft_read_map(map);
	ft_valid_map(map);
}

int	main(int ac, char *av[])
{
	t_data	data;
	t_map	map;
	int		size;

	if (ac != 2)
	{
		write (2, "Error\ncheck input\n", 19);
		exit (1);
	}
	size = 50;
	data.map = &map;
	map.filename = av[1];
	ft_map_loader(&map);
	data.mlx_ptr = mlx_init();
	ft_load_images(&data, size, map);
	data.mlx_window = mlx_new_window(data.mlx_ptr, data.window_width, \
	data.window_height, "SoLong");
	ft_load_map_to_window(data, map);
	mlx_hook(data.mlx_window, 17, 0, &ft_endgame, &data);
	mlx_hook(data.mlx_window, 2, 0, &key_hook, &data);
	mlx_loop(data.mlx_ptr);
}
