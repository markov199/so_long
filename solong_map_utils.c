/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:04:02 by mkovoor           #+#    #+#             */
/*   Updated: 2022/11/17 09:47:28 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"solong.h"

int	ft_init_map(t_map *map)
{
	map->height = 1;
	map->width = 0;
	map->count_1 = 0;
	map->count_0 = 0;
	map->count_P = 0;
	map->count_C = 0;
	map->count_E = 0;
	map->plyr_pos = 0;
	map->collected_C = 0;
	map->valid_exit = 0;
	map->player_moves = 0;
	return (0);
}

t_map	*ft_load_map(t_map *map)
{
	int		fd;
	int		i;
	char	buff;

	i = 0;
	map->map_str = malloc(sizeof(char) * ((map->width + 1) * map->height) + 1);
	if (!map->map_str)
		exit(1);
	fd = open(map->filename, O_RDONLY);
	while (read(fd, &buff, 1))
	{
		map->map_str[i++] = buff;
		if (buff == 'P')
		{
			map->count_P++;
			map->plyr_pos = i - 1;
		}
		else if (buff == 'C')
			map->count_C++;
		else if (buff == 'E')
			map->count_E++;
	}	
	map->map_str[i] = '\0';
	close(fd);
	return (map);
}

int	ft_read_map(t_map *map)
{
	char	buff;
	int		fd;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
	{
		write (2, "Error\nCannot open/find the file\n", 32);
		exit(1);
	}
	while (read(fd, &buff, 1))
	{	
		if (!(buff == '1' || buff == '0' || buff == 'C' || buff == 'P' \
			|| buff == 'E' || buff == '\n'))
		{
			write(2, "Error\nCheck map elements\n", 26);
			exit(1);
		}
		if (buff != '\n' && map->height == 1)
			map->width++;
		if (buff == '\n')
			map->height++;
	}
	close (fd);
	return (0);
}

void	ft_valid_map(t_map *map)
{
	ft_load_map(map);
	ft_valid_chars(map);
	if (ft_valid_path(map) == -1)
	{
		free(map->map_str);
		write (2, "Error\n No valid path in map\n", 28);
		exit(1);
	}
	if (ft_isrectangle(map) == -1)
	{
		write (2, "Error:map has to be a rectangular\n", 34);
		free (map->map_str);
		exit (1);
	}
	if (ft_valid_boundaries(map) == -1)
	{
		write (2, "Error:map not surrounded by walls\n", 34);
		free (map->map_str);
		exit (1);
	}
	map->valid_exit = 0;
	map->collected_C = 0;
}

int	get_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}
