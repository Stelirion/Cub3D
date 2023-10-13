/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:32:57 by ngennaro          #+#    #+#             */
/*   Updated: 2023/10/13 11:33:47 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	what_is_it(char *str, t_map *map)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\n')
			;
		else if (str[i] == 'N' && str[i + 1] && str[i + 1] == 'O')
		{
			map->north_found += 1;
			if (map->north_found != 1)
			{
				printf("2 of the same parameter in map\n");
				return (-1);
			}
			return (1);
		}
		else if (str[i] == 'S' && str[i + 1] && str[i + 1] == 'O')
		{
			map->south_found += 1;
			if (map->south_found != 1)
			{
				printf("2 of the same parameter in map\n");
				return (-1);
			}
			return (2);
		}
		else if (str[i] == 'W' && str[i + 1] && str[i + 1] == 'E')
		{
			map->west_found += 1;
			if (map->west_found != 1)
			{
				printf("2 of the same parameter in map\n");
				return (-1);
			}
			return (3);
		}
		else if (str[i] == 'E' && str[i + 1] && str[i + 1] == 'A')
		{
			map->east_found += 1;
			if (map->east_found != 1)
			{
				printf("2 of the same parameter in map\n");
				return (-1);
			}
			return (4);
		}
		else if (str[i] == 'C')
		{
			map->celing_found += 1;
			if (map->celing_found != 1)
			{
				printf("2 of the same parameter in map\n");
				return (-1);
			}
			return (5);
		}
		else if (str[i] == 'F')
		{
			map->floor_found += 1;
			if (map->floor_found != 1)
			{
				printf("2 of the same parameter in map\n");
				return (-1);
			}
			return (6);
		}
		else
			return (-1);
		i++;
	}
	return (0);
}