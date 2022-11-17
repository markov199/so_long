/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:52:29 by mkovoor           #+#    #+#             */
/*   Updated: 2022/11/17 09:57:40 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
#include<unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include<string.h>
# include <fcntl.h>
#include "./minilibx/mlx.h"

#define FILETYPE ".ber"
#define PLAYER "images/player_r.xpm"
#define PLAYERFLIP "images/player_l.xpm"
#define PLAYER2 "images/player_r2.xpm"
#define PLAYER2FLIP "images/player_l2.xpm"
#define COIN "images/old_coin.xpm"
#define DOOR "images/door.xpm"
#define WALL "images/wall.xpm"
#define GRASS "images/old_grass.xpm"
#define LEFT -1
#define RIGHT 1

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

/* ibft func*/
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);

/* to get colour vaue*/

int	get_rgb(int red, int green, int blue);

/*Function to check valid path*/

void ft_queue_delete(t_queue **queue);
t_queue	*ft_queue_new(int index);
int pop_queue (t_queue **queue);
void ft_queue_add_back(t_queue **lst, t_queue *new);
void ft_visit(char *str, int position, t_map *map, t_queue **queue);

/*Functions to read the map file*/
int ft_read_map(t_map *map);
void ft_valid_map(t_map *map);
int ft_valid_chars(t_map *map);
int ft_valid_file_type(t_map *map);
int ft_valid_boundaries(t_map *map);
int ft_isrectangle(t_map *map);
int ft_init_map(t_map *map);
int ft_valid_path(t_map *map);
t_map *ft_load_map(t_map *map);

/* window functions*/

void	ft_put_player_img(t_data data, t_map map, int x, int y);
void	ft_load_map_to_window(t_data data, t_map map);
void	ft_load_images(t_data *data, int size, t_map map);
int		key_hook(int keycode, t_data *data);
int		ft_move(t_data *data, t_map *map, int new_pos);
void	ft_write_moves(int x);
int		ft_endgame(t_data *data);
void	ft_string_to_window (t_data *data, t_map *map);

#endif