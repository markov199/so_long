/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:04:02 by mkovoor           #+#    #+#             */
/*   Updated: 2022/09/13 16:08:54 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include"solong.h"
# include <fcntl.h>
#define FILETYPE ".ber"

// char	*ft_strdup(const char *s1);

// typedef struct s_node
// {
// 	int		index;
// 	int		in_queue;
// } t_node;

int ft_init_map(t_map *map);
t_map *ft_load_map(t_map *map);
int ft_read_map(t_map *map);
int ft_valid_chars(t_map *map);
int ft_valid_file_type(t_map *map);
void ft_valid_map(t_map *map);
int pop_queue (t_queue **queue);
void ft_visit(char *str, int position, t_map *map, t_queue **queue);
void ft_print_index(char *str);

int ft_valid_path(t_map *map)
{
	int	node;
	t_queue *queue;
	char	*str;
		
	queue = NULL;
	ft_queue_add_back(&queue, ft_queue_new(map->plyr_pos));
	str = ft_strdup(map->map_str);
	while (queue != NULL && (map->valid_exit < 1 || map->collected_C < map->count_C ))
	{
		node = pop_queue(&queue);
		ft_visit(str, (node - 1), map, &queue);
		ft_visit(str, (node + 1), map, &queue);
		ft_visit(str, (node - map->width -1), map, &queue);
		ft_visit(str, (node + map->width + 1), map, &queue);
	}
	free(str);
	ft_queue_delete(&queue);
	if (map->valid_exit == 1  && map->collected_C == map->count_C)
		return (0);
	else 
		return (-1);	
}


int ft_init_map(t_map *map)
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

t_map *ft_load_map(t_map *map)
{
	int	fd;
	int i;
	char	buff;

	i = 0;
	map->map_str = malloc(sizeof(char)* ((map->width + 1)* map->height) + 1);
	if (!map->map_str)
		exit(1);
	fd = open(map->filename, O_RDONLY);
	while (read(fd, &buff, 1))
	{
		map->map_str[i++] = buff;
		if (buff == 'P')
			map->plyr_pos = i - 1;
	}	
	map->map_str[i] = '\0';
 	close(fd);
 	return (map);
}

int ft_read_map(t_map *map)
{
	char	buff;
	int 	fd;
	
	fd = open(map->filename, O_RDONLY);
	while(read(fd, &buff, 1))
	{	
		if (!(buff == '1' || buff =='0' || buff == 'C' || buff == 'P'
			|| buff == 'E' || buff == '\n'))
		{
			write(1, "Error\nCheck map elements\n", 26);
			exit(1);
		}	
		if(buff != '\n' && map->height == 1)
			map->width++;
		if (buff == '\n')
			map->height++;
		if (buff == 'C')
			map->count_C++;
		else if (buff == 'P')
			map->count_P++;
		else if (buff == 'E')
			map->count_E++;
	}
	close (fd);
	return(0);
}

int ft_valid_chars(t_map *map)
{
	if ((map->count_P == 1 && map->count_E == 1 && map->count_C > 0))
 		return (0);
	else
		return (-1);
}

int ft_valid_file_type(t_map *map)
{
	int i;
	int	j;
	
	j = 0;
	i = ft_strlen(map->filename);
	i = i - 4;
	if(strcmp(&map->filename[i], FILETYPE) == 0)	
		return (0);
	else
	{
		printf("Error\nInvalid  file_type\n");
		exit(1);
	}
}		

void ft_valid_map(t_map *map)
{
	if (ft_valid_chars(map) == -1)
	{
		printf("Error\nInvalid  number of element\n");
		free(map->map_str);
		exit(1);
	}
	ft_load_map(map);
	if (ft_valid_path(map) == -1)
	{
		free(map->map_str);
		printf("Error\n No valid path in map");
		exit(1);
	}
	map->valid_exit = 0;
	map->collected_C = 0;
}

int pop_queue (t_queue **queue)
{
	if (queue != NULL)
	{
		
		int temp;
		t_queue	*ptr;

		ptr = *queue;
		temp = ptr ->index;
		*queue = ptr->next;
		// free(ptr);
		return (temp);
	}
	return (-1);
}

void ft_visit(char *str, int position, t_map *map, t_queue **queue)
{
	if (str[position] == '0' || str[position] == 'C') 
	{
		if(str[position] == 'C')
			map->collected_C++;
		ft_queue_add_back(queue, ft_queue_new(position));
		str[position] = 'V';
	}
	else if (str[position] == 'E')
	{
		map->valid_exit++;
		str[position] = '1';
	}	
}

void ft_print_index(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		printf("str[%d] = %c ", i,str[i]);
		if (str[i] == '\n' || str[i]== '\0')
			printf("\n");
		i++;
	}
}
