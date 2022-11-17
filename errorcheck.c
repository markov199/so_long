/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:54:56 by mkovoor           #+#    #+#             */
/*   Updated: 2022/11/16 15:37:33 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"solong.h"

int	ft_valid_path(t_map *map)
{
	int		node;
	t_queue	*queue;
	char	*str;

	queue = NULL;
	ft_queue_add_back(&queue, ft_queue_new(map->plyr_pos));
	str = ft_strdup(map->map_str);
	while (queue != NULL && (map->valid_exit < 1
			|| map->collected_C < map->count_C))
	{
		node = pop_queue(&queue);
		ft_visit(str, (node - 1), map, &queue);
		ft_visit(str, (node + 1), map, &queue);
		ft_visit(str, (node - map->width -1), map, &queue);
		ft_visit(str, (node + map->width + 1), map, &queue);
	}
	free(str);
	ft_queue_delete(&queue);
	if (map->valid_exit == 1 && map->collected_C == map->count_C)
		return (0);
	else
		return (-1);
}

int	ft_valid_chars(t_map *map)
{
	if (!(map->count_P == 1 && map->count_E == 1 && map->count_C > 0))
	{
		write (2, "Error\nInvalid  number of element\n", 34);
		free(map->map_str);
		exit(1);
	}
	return (0);
}

int	ft_valid_file_type(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(map->filename);
	i = i - 4;
	if (strcmp(&map->filename[i], FILETYPE) == 0)
		return (0);
	else
	{
		write (2, "Error\nInvalid  file_type\n", 25);
		exit(1);
	}
}

int	ft_isrectangle(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map_str[j] != '\0')
	{
		if (map->map_str[j] != '\n')
			i++;
		if (map->map_str[j] == '\n' )
		{
			if (i != map->width)
				return (-1);
			i = 0;
		}
		j++;
	}
	if (map->map_str[j] == '\0' && i != map->width)
		return (-1);
	return (0);
}

int	ft_valid_boundaries(t_map *map)
{
	int	i;
	int	height;

	i = 0;
	height = 1;
	while (map->map_str[i])
	{
		if (map->map_str[i] == '\n')
		{
			if (map->map_str[i - 1] != '1' || map->map_str[i + 1] != '1')
				return (-1);
			height++;
		}			
		else if (height == 1 || height == map->height)
		{
			if (map->map_str[i] != '1')
				return (-1);
		}	
		i++;
	}
	return (0);
}
