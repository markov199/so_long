/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:52:04 by mkovoor           #+#    #+#             */
/*   Updated: 2022/09/12 14:50:10 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"


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
		printf("pop er\n");
	}
	return (-1);
}

void ft_visit(char *str, int position, t_map *map, t_queue *queue)
{
	if (str[position] == '0')
		ft_queue_add_back(&queue, ft_queue_new(position));
	if(str[position] == 'C')
	{
		ft_queue_add_back(&queue, ft_queue_new(position));
		map->collected_C ++;
	}
	if (str[position] == 'E')
	{
		ft_queue_add_back(&queue, ft_queue_new(position));
		map->valid_exit ++;
	}		
}

int ft_valid_path(t_map *map)
{
	int	node;
	t_queue *queue;
	char	*str;
	
	queue = NULL;
	node = map->plyr_pos;
	str = strdup(map->map_str);
	printf("%s map\n", str);
	while (queue != NULL || (map->valid_exit != 1  && map->collected_C < map->count_C ))
	{
		
		ft_visit(str, node -1, map, queue);
		ft_visit(str, node +1, map, queue);
		ft_visit(str, node - (map->width -1), map, queue);
		ft_visit(str, node + (map->width + 1), map, queue);
		ft_queue_print(queue);
		str[node] = -1;		
		node = pop_queue(&queue);
	}
	if (map->valid_exit == 1  && map->collected_C == map->count_C)
		return (0);
	else 
		return (-1);
	
}