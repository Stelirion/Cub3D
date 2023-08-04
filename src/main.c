/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:33:59 by mbrement          #+#    #+#             */
/*   Updated: 2023/08/04 03:45:06 by ngennaro         ###   ########.fr       */
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
		return ((void)printf("Wrong number of argument\n"), 1);
	map = define_map(map);
	map = check_file(argv[1]);
	death_map(&map);
	//debug
	printf("floor : %i|%i|%i|%i\nceling : %i|%i|%i|%i|\n", map.floor[0], map.floor[1], map.floor[2], map.floor_color, map.celing[0], map.celing[1], map.celing[2], map.celing_color);
	printf("north %i| south %i| east %i| west%i\n", map.north, map.south, map.east, map.west);
	printf("map:\n");
	ft_print_tab(map.map);
	printf("sucess\n");
	//end of debug
	// nfree((void **)&map.north_file);
	// nfree((void **)&map.south_file);
	// nfree((void **)&map.east_file);
	// nfree((void **)&map.west_file);
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
		exit(printf("Fail to create a map\n"));
	}
	if (map->east <= 0 || map->south <= 0 || map->north <= 0 || map->west <= 0)
	{
		(void)printf("Can't open file in map\n");
		end_of_prog(*map);
		exit(1);
	}
	if (map->floor[0] < 0 || map->floor[1] < 0 || map->floor[2] < 0)
	{
		(void)printf("Can't find RGB\n");
		end_of_prog(*map);
		exit(1);
	}
	if (map->celing[0] < 0 || map->celing[1] < 0 || map->celing[2] < 0)
	{
		(void)printf("Can't find RGB\n");
		end_of_prog(*map);
		exit(1);
	}
	map->celing_color = (255 << 24) | (map->celing[0] << 16) | \
		(map->celing[1] << 8) | map->celing[2];
	map->floor_color = (255 << 24) | (map->floor[0] << 16) | \
		(map->floor[1] << 8) | map->floor[2];
}
