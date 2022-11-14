/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:23:38 by mkovoor           #+#    #+#             */
/*   Updated: 2022/09/12 08:50:12 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"solong.h"
#include "./minilibx/mlx.h"
#include "solong.h"
#define ME "images/player.xpm"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*img;
} t_data;


int main(int ac, char *av[])
{
	t_map	map;

	map.filename = av[1];
	if (ft_valid_file_type(&map) == -1)
	{
		printf("Error\nInvalid  file_type\n");
		exit(1);
	}
	ft_init_map(&map);
	if (ft_read_map(&map) == -1)
		write(1, "Error\n. Check map elements\n", 28);
	ft_valid_map(&map);
	write(1, "Valid Map\n", 10);
	return (0);
}


// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }
