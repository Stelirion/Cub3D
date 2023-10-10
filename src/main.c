/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:33:59 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/10 09:52:46 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	death_map(t_map *map);
t_map	define_map(t_map map);

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	*mlx;

	map.map = NULL;
	if (argc != 2)
		return ((void)printf("Error\nWrong number of argument\n"), 1);
	map = define_map(map);
	map = check_file(argv[1]);
	death_map(&map);
	mlx = malloc(sizeof(t_mlx));
	ft_mlx(&map, mlx);
	end_of_prog_mlx(mlx);
}

t_map	define_map(t_map map)
{
	map.map = NULL;
	map.north_file = NULL;
	map.south_file = NULL;
	map.east_file = NULL;
	map.west_file = NULL;
	return (map);
}

void	death_map(t_map *map)
{
	if (!map || map->error >= 1)
	{
		end_of_prog(*map);
		exit(printf("Error\nFail to create a map\n"));
	}
	if (map->east <= 0 || map->south <= 0 || map->north <= 0 || map->west <= 0)
	{
		(void)printf("Error\nCan't open file in map\n");
		end_of_prog(*map);
		exit(1);
	}
	if ((map->floor[0] < 0 || map->floor[1] < 0 || map->floor[2] < 0)
		|| (map->celing[0] < 0 || map->celing[1] < 0 || map->celing[2] < 0))
	{
		(void)printf("Error\nCan't find RGB\n");
		end_of_prog(*map);
		exit(1);
	}
	map->celing_color = (255 << 24) | (map->celing[0] << 16) | \
		(map->celing[1] << 8) | map->celing[2];
	map->floor_color = (255 << 24) | (map->floor[0] << 16) | \
		(map->floor[1] << 8) | map->floor[2];
}
