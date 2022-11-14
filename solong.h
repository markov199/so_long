/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:52:29 by mkovoor           #+#    #+#             */
/*   Updated: 2022/09/13 16:08:09 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
#include<unistd.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include<string.h>
#include"solong.h"

// #include"queue_utils.c"
// #include"valid_path.c"

typedef struct s_map
{
	char	*filename;
	int 	height;
	int 	width;
	int 	count_1;
	int		count_0;
	int 	count_P;
	int		count_C;
	int 	count_E;
	int		plyr_pos;
	int		collected_C;
	int		valid_exit;
	char	*map_str;
	int		player_moves;
} t_map;

typedef struct s_queue
{
	int	index;
	struct s_queue *next;	
} t_queue;

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void ft_queue_print(t_queue *queue);
void ft_queue_delete(t_queue **queue);
t_queue	*ft_queue_new(int index);
void ft_queue_add_back(t_queue **lst, t_queue *new);

int ft_read_map(t_map *map);
void ft_valid_map(t_map *map);
int ft_valid_chars(t_map *map);
int ft_valid_file_type(t_map *map);
int ft_valid_boundaries(t_map map);
int ft_isrectangle(char *map_str);
int ft_init_map(t_map *map);
t_map *ft_load_map(t_map *map);

#endif